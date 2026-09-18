#include "il2cpp.h"

#if defined(UNITY)

#include <Foundation/Foundation.h>

    namespace IL2CPP
    {
        const void *(*il2cpp_assembly_get_image)(const void *assembly) = nullptr;
        void *(*il2cpp_domain_get)() = nullptr;
        void **(*il2cpp_domain_get_assemblies)(const void *domain, size_t *size) = nullptr;
        const char *(*il2cpp_image_get_name)(void *image) = nullptr;
        void *(*il2cpp_class_from_name)(const void *image, const char *namespaze, const char *name) = nullptr;
        void *(*il2cpp_class_get_field_from_name)(void *klass, const char *name) = nullptr;
        void *(*il2cpp_class_get_method_from_name)(void *klass, const char *name, int argsCount) = nullptr;
        size_t (*il2cpp_field_get_offset)(void *field) = nullptr;
        void (*il2cpp_field_static_get_value)(void *field, void *value) = nullptr;
        void (*il2cpp_field_static_set_value)(void *field, void *value) = nullptr;

        void *(*il2cpp_string_new)(const char *str) = nullptr;
        void *(*il2cpp_string_new_utf16)(const wchar_t *str, int32_t length) = nullptr;
        uint16_t *(*il2cpp_string_chars)(void *str) = nullptr;
    }

    // Credit KittyMemory
    MemoryInfo getBaseAddress(const std::string &fileName)
    {
        MemoryInfo _info;

        const uint32_t imageCount = _dyld_image_count();

        for (uint32_t i = 0; i < imageCount; i++)
        {
            const char *name = _dyld_get_image_name(i);
            if (!name)
                continue;

            std::string fullpath(name);

            if (fullpath.length() < fileName.length() || fullpath.compare(fullpath.length() - fileName.length(), fileName.length(), fileName) != 0)
                continue;

            _info.index = i;
            _info.header = _dyld_get_image_header(i);
            _info.name = _dyld_get_image_name(i);
            _info.address = _dyld_get_image_vmaddr_slide(i);

            break;
        }
        return _info;
    }

    void Il2CppAttach()
    {
        NSString *appPath = [[NSBundle mainBundle] bundlePath];
        NSString *unityFrameworkPath = [appPath stringByAppendingPathComponent:@"Frameworks/UnityFramework.framework/UnityFramework"]; // THIS NEED TO BE CHANGED IF Il2CPP ISN'T INIT IN "UnityFramework"
        void *handle = dlopen([unityFrameworkPath UTF8String], RTLD_LAZY);
        while (!handle)
        {
            //[menu showPopup:@"Error" description:@"Failed to load UnityFramework"];
            NSLog(@"Error: Failed to load UnityFramework");
            handle = dlopen([unityFrameworkPath UTF8String], RTLD_LAZY);
            sleep(1);
        }

        IL2CPP::il2cpp_assembly_get_image = reinterpret_cast<const void *(*)(const void *)>(dlsym(handle, "il2cpp_assembly_get_image"));
        IL2CPP::il2cpp_domain_get = reinterpret_cast<void *(*)()>(dlsym(handle, "il2cpp_domain_get"));
        IL2CPP::il2cpp_domain_get_assemblies = reinterpret_cast<void **(*)(const void *, size_t *)>(dlsym(handle, "il2cpp_domain_get_assemblies"));
        IL2CPP::il2cpp_image_get_name = reinterpret_cast<const char *(*)(void *)>(dlsym(handle, "il2cpp_image_get_name"));
        IL2CPP::il2cpp_class_from_name = reinterpret_cast<void *(*)(const void *, const char *, const char *)>(dlsym(handle, "il2cpp_class_from_name"));
        IL2CPP::il2cpp_class_get_method_from_name = reinterpret_cast<void *(*)(void *, const char *, int)>(dlsym(handle, "il2cpp_class_get_method_from_name"));
        IL2CPP::il2cpp_class_get_field_from_name = reinterpret_cast<void *(*)(void *, const char *)>(dlsym(handle, "il2cpp_class_get_field_from_name"));
        IL2CPP::il2cpp_field_get_offset = reinterpret_cast<size_t (*)(void *)>(dlsym(handle, "il2cpp_field_get_offset"));
        IL2CPP::il2cpp_field_static_get_value = reinterpret_cast<void (*)(void *, void *)>(dlsym(handle, "il2cpp_field_static_get_value"));
        IL2CPP::il2cpp_field_static_set_value = reinterpret_cast<void (*)(void *, void *)>(dlsym(handle, "il2cpp_field_static_set_value"));

        // Additional IL2CPP function assignments
        IL2CPP::il2cpp_string_new = reinterpret_cast<void *(*)(const char *)>(dlsym(handle, "il2cpp_string_new"));
        IL2CPP::il2cpp_string_new_utf16 = reinterpret_cast<void *(*)(const wchar_t *, int32_t)>(dlsym(handle, "il2cpp_string_new_utf16"));
        IL2CPP::il2cpp_string_chars = reinterpret_cast<uint16_t *(*)(void *)>(dlsym(handle, "il2cpp_string_chars"));

        dlclose(handle);
    }

    void *Il2CppGetImageByName(const char *image)
    {
        size_t size;
        void **assemblies = IL2CPP::il2cpp_domain_get_assemblies(IL2CPP::il2cpp_domain_get(), &size);
        for (int i = 0; i < size; ++i)
        {
            void *img = (void *)IL2CPP::il2cpp_assembly_get_image(assemblies[i]);
            const char *img_name = IL2CPP::il2cpp_image_get_name(img);
            if (strcmp(img_name, image) == 0)
            {
                return img;
            }
        }
        return 0;
    }

    // --- CLASS IMPLEMENTATIONS ---

    // Il2CppString Implementations
    Il2CppString::Il2CppString(const char *utf8Str)
    {
        str = IL2CPP::il2cpp_string_new(utf8Str);
    }

    Il2CppString::Il2CppString(const wchar_t *utf16Str, int32_t length)
    {
        str = IL2CPP::il2cpp_string_new_utf16(utf16Str, length);
    }

    Il2CppString::~Il2CppString()
    {
        // Release IL2CPP string if needed
    }

    uint16_t *Il2CppString::getChars()
    {
        return IL2CPP::il2cpp_string_chars(str);
    }

    std::string Il2CppString::toUtf8String()
    {
        uint16_t *chars = getChars();
        if (!chars)
        {
            return "";
        }

        std::string utf8Str;
        for (int i = 0; chars[i] != '\0'; ++i)
        {
            utf8Str += static_cast<char>(chars[i]);
        }
        return utf8Str;
    }

    std::wstring Il2CppString::toUtf16String()
    {
        uint16_t *chars = getChars();
        if (!chars)
        {
            return L"";
        }

        std::wstring utf16Str;
        for (int i = 0; chars[i] != '\0'; ++i)
        {
            utf16Str += static_cast<wchar_t>(chars[i]);
        }
        return utf16Str;
    }

    void *Il2CppString::getInternalString()
    {
        return str;
    }

    // Il2CppField Implementations
    Il2CppField::Il2CppField(const char *assemblyName)
    {
        image = Il2CppGetImageByName(assemblyName);
        if (!image)
        {
            //[menu showPopup:@"Error" description:@"Cannot find specified image."];
            NSLog(@"Error: Cannot find specified image.");
        }
    }

    Il2CppField &Il2CppField::getClass(const char *namespaze, const char *className)
    {
        klass = IL2CPP::il2cpp_class_from_name(image, namespaze, className);
        if (!klass)
        {
            //[menu showPopup:@"Error" description:[NSString stringWithFormat:@"Cannot find class %s in namespace %s.", className, namespaze]];
            NSLog(@"Error: Cannot find class %s in namespace %s.", className, namespaze);
        }
        return *this;
    }

    Il2CppField &Il2CppField::getField(const char *fieldName)
    {
        field = IL2CPP::il2cpp_class_get_field_from_name(klass, fieldName);
        if (!field)
        {
            //[menu showPopup:@"Error" description:[NSString stringWithFormat:@"Cannot find field %s in class.", fieldName]];
            NSLog(@"Error: Cannot find field %s in class.", fieldName);
        }
        return *this;
    }

    size_t Il2CppField::getOffset() const
    {
        return IL2CPP::il2cpp_field_get_offset(field);
    }

    // Il2CppMethod Implementations
    Il2CppMethod::Il2CppMethod(const char *assemblyName)
    {
        image = Il2CppGetImageByName(assemblyName);
        if (!image)
        {
            //[menu showPopup:@"Error" description:@"Cannot find specified image."];
            NSLog(@"Error: Cannot find specified image.");
        }
    }

    Il2CppMethod &Il2CppMethod::getClass(const char *namespaze, const char *className)
    {
        klass = IL2CPP::il2cpp_class_from_name(image, namespaze, className);
        if (!klass)
        {
            //[menu showPopup:@"Error" description:[NSString stringWithFormat:@"Cannot find class %s in namespace %s.", className, namespaze]];
            NSLog(@"Error: Cannot find class %s in namespace %s.", className, namespaze);
        }
        return *this;
    }

    uint64_t Il2CppMethod::getMethod(const char *methodName, int argsCount)
    {
        void **methodPointer = (void **)IL2CPP::il2cpp_class_get_method_from_name(klass, methodName, argsCount);
        if (!methodPointer || !*methodPointer)
        {
            //[menu showPopup:@"Error" description:[NSString stringWithFormat:@"Cannot find method %s with %d arguments.", methodName, argsCount]];
            NSLog(@"Error: Cannot find method %s with %d arguments.", methodName, argsCount);
            return 0;
        }
        method = *methodPointer;

        MemoryInfo info = getBaseAddress("UnityFramework");
        uint64_t rvaOffset = reinterpret_cast<uint64_t>(method) - info.address;

        return rvaOffset;
    }

#endif