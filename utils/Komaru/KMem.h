/**
 * 
 * @file KMem.h
 * @brief Mach memory utilities
 * @author Venerablecode
 * @version V1
 * @note this can probably be improved a lot.
 * 
 * --------- USAGE ---------
 * 
 * find the first base
 * uintptr_t base = KMEM::scanner::FindFirstBase();
 * 
 * reinterpret cast _dyld_get_image_header(0)
 * uintptr_base = KMEM::scanner::ReturnBase(); 
 * 
 * get base from name
 * uintptr_t base = KMEM::scanner::GetImageBase("UnityFramework");
 * 
 * get address from first base + offset (only works if FindFirstBase is successful)
 * uintptr_t address = KMEM::io::GetAddress(0x123);
 * 
 * get address from chosen base + offset 
 * uintptr_t address = KMEM::io::GetAddress("framework", 0x123);
 * 
 * validate ptr 
 * if (KMEM::io::IsValidPointer(address)) { }
 * 
 * read
 * int value = KMEM::io::ReadMem<int>(address);
 * 
 * write
 * KMEM::io::WriteMem<int>(address, 100);
 * 
 * read string
 * std::string text = KMEM::io::ReadString(address, 64);
 * 
 * raw read
 * uintptr_t rawValue = KMEM::io::ReadRaw(address);
 * 
 * raw write
 * KMEM::io::WriteRaw<int>(address, 100);
 * 
 * read bytes
 * uint8_t buffer[32]{}; 
 * KMEM::io::ReadBytes(address, buffer, sizeof(buffer));
 * 
 * write bytes
 * const uint8_t bytes[] = { 0x90, 0x90, 0x90 }; 
 * KMEM::io::WriteBytes(address, bytes, sizeof(bytes));
 * 
 * --------- USAGE END ---------
 * 
 */

#pragma once

#include <mach/mach.h>
#include <mach-o/loader.h>

#include <signal.h>
#include <setjmp.h>

#include <cstdint>
#include <mutex>
#include <string>
#include <string_view>
#include <vector>

#ifndef VM_PROT_RE
#define VM_PROT_RE (VM_PROT_READ | VM_PROT_EXECUTE)
#endif

namespace KMEM
{
    namespace io
    {
        //validptr credit: ragekill3377 (_.xprt)
        inline static std::mutex sigsegv_mutex; // Mutex to protect global sigaction from races
        inline static thread_local sigjmp_buf thread_jump_buffer; // Thread-local jump buffer (isolated per thread)

        // SIGSEGV handler - long jumps to thread-local buffer
        inline void sigsegv_handler(int) 
        { 
            siglongjmp(thread_jump_buffer, 1);
        }

        // Checks if an address is in a valid memory region
        // Uses a signal handler to catch segmentation faults
        // Returns true if the address is valid, false otherwise
        inline bool IsValidPointer(uintptr_t address) 
        {
            std::lock_guard<std::mutex> lock(sigsegv_mutex);

            struct sigaction sa{}, old_sa{};
            sa.sa_handler = sigsegv_handler;
            sigemptyset(&sa.sa_mask);
            sa.sa_flags = 0;

            if (sigaction(SIGSEGV, &sa, &old_sa) != 0)
                return false;

            bool result = false;

            if (sigsetjmp(thread_jump_buffer, 1) == 0) 
            {
                // only checking if access causes a fault
                *(volatile uintptr_t*)address;
                result = true;
            }

            sigaction(SIGSEGV, &old_sa, nullptr);
            return result;
        }

        /*
        kern_return_t vm_read_overwrite
        (
            vm_map_read_t target_task, 
            vm_address_t address, 
            vm_size_t size, 
            vm_address_t data, 
            vm_size_t *outsize
        );
        */
        template <typename T>
        inline T ReadMem(mach_vm_address_t address) 
        {
            T buffer = T();
            vm_size_t outSize = 0;

            kern_return_t kr = vm_read_overwrite //vm_read will cause leaks, so we can use vm_read_overwrite
            (
                mach_task_self(),
                (vm_address_t)address,
                sizeof(T),
                (vm_address_t)&buffer,
                &outSize
            );

            if(kr == KERN_SUCCESS && outSize == sizeof(T))
            {
                return buffer;
            }
            return T{};
        }

        template <typename T>
        inline bool WriteMem(mach_vm_address_t address, T value)
        {
            T buffer = value;

            mach_msg_type_number_t data_count = (mach_msg_type_number_t)sizeof(T);

            kern_return_t kr = vm_write
            (
                mach_task_self(),
                (vm_address_t)address,                        
                (vm_offset_t)&buffer,
                data_count
            );

            if(kr == KERN_SUCCESS)
            {
                return true;
            }

            return false;
        }

        inline std::string ReadString(mach_vm_address_t address, mach_vm_size_t maxSize) 
        {
            std::vector<char> buffer(maxSize);

            vm_size_t outSize = 0;

            kern_return_t ks = vm_read_overwrite(
                mach_task_self(),
                (vm_address_t)address,
                maxSize,
                (vm_address_t)buffer.data(),
                &outSize
            );

            if (ks != KERN_SUCCESS) return "";

            return std::string(buffer.begin(), buffer.begin() + outSize);
        }

        inline uintptr_t ReadRaw(mach_vm_address_t address) 
        {
            if (!IsValidPointer(address)) return 0;
            
            return *reinterpret_cast<uintptr_t*>(address);
        }

        template <typename T>
        inline void WriteRaw(mach_vm_address_t address, const T& value) 
        {
            //if (!IsValidPointer(address)) return;
            *reinterpret_cast<T*>(address) = value;
        }

        inline bool ReadBytes(mach_vm_address_t address, void* out, size_t len)
        {
            vm_size_t osize = 0;
            return vm_read_overwrite(mach_task_self(), (vm_address_t)address, (vm_size_t)len, (vm_address_t)out, &osize) == KERN_SUCCESS && osize == len;
        }

        inline bool WriteBytes(mach_vm_address_t address, const void* data, size_t len)
        {
            return vm_write(mach_task_self(), (vm_address_t)address, (vm_offset_t)data, (mach_msg_type_number_t)len) == KERN_SUCCESS;
        }
    }

    namespace scanner
    {
        /*
        kern_return_t vm_region_recurse_64(
        vm_task_t target_task,
        vm_address_t *address,        // INPUT: Start address. OUTPUT: Next region's address
        vm_size_t *size,              // OUTPUT: Size of this region
        natural_t *depth,             // OUTPUT: How deep in submaps we are
        vm_region_recurse_info_t info // OUTPUT: A massive struct containing permissions! //note: passing structs to c-api's, create empty struct var with type before func, and cast it in the args
    );
        */

        //using string_view to prevent memory allocation
        inline uintptr_t GetImageBase(std::string_view ImgName) noexcept
        {
            const uint32_t ImgCount = _dyld_image_count();

            for (uint32_t i = 0; i < ImgCount; i++) 
            {
                const char* path = _dyld_get_image_name(i); if (!path) continue;

                std::string_view ImgPath(path);

                if (ImgPath.find(ImgName) == std::string_view::npos) continue;

                const mach_header* header = _dyld_get_image_header(i);

                if (header) return reinterpret_cast<uintptr_t>(header);
            }
            return 0;
        }

        inline uintptr_t ReturnBase() { return reinterpret_cast<uintptr_t>(_dyld_get_image_header(0));}

        inline uintptr_t FindFirstBase() 
        {
            vm_address_t address = 0;
            vm_size_t size = 0;
            natural_t depth = 0;

            vm_region_submap_info_64 region_info{};
            mach_msg_type_number_t info_count = VM_REGION_SUBMAP_INFO_COUNT_64;

            while(true) 
            {
                info_count = VM_REGION_SUBMAP_INFO_COUNT_64;

                kern_return_t kr = vm_region_recurse_64
                (
                    mach_task_self(),
                    &address,
                    &size,
                    &depth,
                    (vm_region_recurse_info_t)&region_info, 
                    &info_count
                );

                // If != success -> reached the end of memory
                if (kr != KERN_SUCCESS) break; 
                                        //check bits and only show VM_PROT_READ | VM_PROT_EXECUTE, we verify bytes here (read = 1, execute = 4) 
                                        //mach macros: VM_PROT_READ = 0x1, VM_PROT_WRITE = 0x2, VM_PROT_EXECUTE = 0x4
                                        //if((region_info.protection & (0x5)) == (0x5)) /* https://github.com/apple-oss-distributions/xnu/blob/main/osfmk/mach/vm_prot.h */
                if((region_info.protection & (VM_PROT_RE)) == (VM_PROT_RE))
                {
                    uint32_t Chunk = KMEM::io::ReadMem<uint32_t>(address); //read first 4 bytes (chunk)

                                //MH_MAGIC_64 https://developer.apple.com/documentation/kernel/mach_header_64/1525718-magic
                    if(Chunk == 0xFEEDFACF) return address; //when Mach-O 64-bit magic number is found, addr of the first executable binary is returned
                } //note: the implementation for this isnt universal, you might need to update this depending on the target

                address += size;
            }
            return 0; //failed
        }

        
    }

    namespace editor
    {
        //TODO
        
    }

    namespace io
    {
        inline uintptr_t GetAddress(uintptr_t offset) noexcept
        {
            return KMEM::scanner::FindFirstBase() + offset;
        }

        inline uintptr_t GetAddress(std::string_view imageName, uintptr_t offset) noexcept
        {
            const uintptr_t base = KMEM::scanner::GetImageBase(imageName);
            return base ? base + offset : 0;
        }
        
    }
}