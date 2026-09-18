/*
 *
 *      IL2CPP RESOLVER FOR THEOS
 *           by Batchh
 *          Version 0.3
 *
 */

#ifndef IL2CPP_H
#define IL2CPP_H

#include <string>

#if defined(UNITY)
    #include <dlfcn.h>
    #include <mach-o/dyld.h>

    // Credit KittyMemory
    class MemoryInfo
    {
    public:
        uint32_t index;
        const mach_header *header;
        const char *name;
        intptr_t address;
    };

    // Credit KittyMemory
    MemoryInfo getBaseAddress(const std::string &fileName);

    namespace IL2CPP
    {
        extern const void *(*il2cpp_assembly_get_image)(const void *assembly);
        extern void *(*il2cpp_domain_get)();
        extern void **(*il2cpp_domain_get_assemblies)(const void *domain, size_t *size);
        extern const char *(*il2cpp_image_get_name)(void *image);
        extern void *(*il2cpp_class_from_name)(const void *image, const char *namespaze, const char *name);
        extern void *(*il2cpp_class_get_field_from_name)(void *klass, const char *name);
        extern void *(*il2cpp_class_get_method_from_name)(void *klass, const char *name, int argsCount);
        extern size_t (*il2cpp_field_get_offset)(void *field);
        extern void (*il2cpp_field_static_get_value)(void *field, void *value);
        extern void (*il2cpp_field_static_set_value)(void *field, void *value);

        extern void *(*il2cpp_string_new)(const char *str);
        extern void *(*il2cpp_string_new_utf16)(const wchar_t *str, int32_t length);
        extern uint16_t *(*il2cpp_string_chars)(void *str);
    }

    void Il2CppAttach();
    void *Il2CppGetImageByName(const char *image);

    class Il2CppString
    {
    private:
        void *str;

    public:
        // Constructors
        Il2CppString(const char *utf8Str);
        Il2CppString(const wchar_t *utf16Str, int32_t length);

        // Destructor
        ~Il2CppString();

        // Get characters from the IL2CPP string
        uint16_t *getChars();

        // Convert IL2CPP string to UTF-8
        std::string toUtf8String();

        // Convert IL2CPP string to UTF-16
        std::wstring toUtf16String();

        // Get internal IL2CPP string pointer (if needed)
        void *getInternalString();
    };

    class Il2CppField
    {
    private:
        void *image;
        void *klass;
        void *field;

    public:
        // Constructor initializes the image from assembly name
        Il2CppField(const char *assemblyName);

        // Get class by namespace and class name
        Il2CppField &getClass(const char *namespaze, const char *className);

        // Get field by field name
        Il2CppField &getField(const char *fieldName);

        // Get field offset
        size_t getOffset() const;

        // Get field value
        template <typename T>
        T getValue()
        {
            T value;
            IL2CPP::il2cpp_field_static_get_value(field, &value);
            return value;
        }

        // Set field value
        template <typename T>
        void setValue(T value)
        {
            IL2CPP::il2cpp_field_static_set_value(field, &value);
        }

        // Show field value using menu popup
        template <typename T>
        void showValue(const char *fieldName)
        {
            T value = getValue<T>();
            NSLog(@"%s Value = %d", fieldName, value);
        }
    };

    class Il2CppMethod
    {
    private:
        void *image;
        void *klass;
        void *method;

    public:
        // Constructor initializes the image from assembly name
        Il2CppMethod(const char *assemblyName);

        // Get class by namespace and class name
        Il2CppMethod &getClass(const char *namespaze, const char *className);

        // Get method by method name and number of arguments
        uint64_t getMethod(const char *methodName, int argsCount);

        // Invoke the method with given arguments
        template <typename Ret, typename... Args>
        Ret invoke(Args... args)
        {
            using MethodType = Ret (*)(Args...);
            MethodType methodFunc = reinterpret_cast<MethodType>(method);
            return methodFunc(args...);
        }
    };

#endif // End of #if defined(UNITY)

#endif // IL2CPP_H