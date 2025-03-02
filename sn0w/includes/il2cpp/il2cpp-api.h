#pragma once
#include "il2cpp-class.h"
#include "il2cpp-tabledefs.h"

struct il2cpp_api_t {
public:
    void init();

    // array
    Il2CppClass*            (*array_class_get)                  (Il2CppClass* element_class, uint32_t rank);
    uint32_t                (*array_length)                     (Il2CppArray* array);
    uint32_t                (*array_get_byte_length)            (Il2CppArray* array);
    Il2CppArray*            (*array_new)                        (Il2CppClass* elementTypeInfo, il2cpp_array_size_t length);
    Il2CppArray*            (*array_new_specific)               (Il2CppClass* arrayTypeInfo, il2cpp_array_size_t length);
    Il2CppArray*            (*array_new_full)                   (Il2CppClass* array_class, il2cpp_array_size_t* length, il2cpp_array_size_t* lower_bounds);
    Il2CppClass*            (*bounded_array_class_get)          (Il2CppClass* element_class, uint32_t rank, bool bounded);
    int                     (*array_element_size)               (const Il2CppClass* array_class);

    // assembly
    const Il2CppImage*      (*assembly_get_image)               (const Il2CppAssembly* assembly);

    // class
    void                    (*class_for_each)                   (void(*klassReportFunc)(Il2CppClass* klass, void* userData), void* userData);
    const Il2CppType*       (*class_enum_basetype)              (Il2CppClass* klass);
    bool                    (*class_is_generic)                 (const Il2CppClass* klass);
    bool                    (*class_is_inflated)                (const Il2CppClass* klass);
    bool                    (*class_is_assignable_from)         (Il2CppClass* klass, Il2CppClass* oklass);
    bool                    (*class_is_subclass_of)             (Il2CppClass* klass, Il2CppClass* klassc, bool check_interfaces);
    bool                    (*class_has_parent)                 (Il2CppClass* klass, Il2CppClass* klassc);
    Il2CppClass*            (*class_from_type)                  (const Il2CppType* type);
    Il2CppClass*            (*class_from_name)                  (const Il2CppImage* image, const char* namespaze, const char *name);
    Il2CppClass*            (*class_from_system_type)           (Il2CppReflectionType* type);
    Il2CppClass*            (*class_get_element_class)          (Il2CppClass* klass);
    const EventInfo*        (*class_get_events)                 (Il2CppClass* klass, void** iter);
    FieldInfo*              (*class_get_fields)                 (Il2CppClass* klass, void* *iter);
    Il2CppClass*            (*class_get_nested_types)           (Il2CppClass* klass, void* *iter);
    Il2CppClass*            (*class_get_interfaces)             (Il2CppClass* klass, void* *iter);
    const PropertyInfo*     (*class_get_properties)             (Il2CppClass* klass, void* *iter);
    const PropertyInfo*     (*class_get_property_from_name)     (Il2CppClass* klass, const char *name);
    FieldInfo*              (*class_get_field_from_name)        (Il2CppClass* klass, const char *name);
    const MethodInfo*       (*class_get_methods)                (Il2CppClass* klass, void* *iter);
    const MethodInfo*       (*class_get_method_from_name)       (Il2CppClass* klass, const char* name, int argsCount);
    const char*             (*class_get_name)                   (Il2CppClass* klass);
    const char*             (*class_get_namespace)              (Il2CppClass* klass);
    Il2CppClass*            (*class_get_parent)                 (Il2CppClass* klass);
    Il2CppClass*            (*class_get_declaring_type)         (Il2CppClass* klass);
    int32_t                 (*class_instance_size)              (Il2CppClass* klass);
    size_t                  (*class_num_fields)                 (const Il2CppClass* enumKlass);
    bool                    (*class_is_valuetype)               (const Il2CppClass* klass);
    int32_t                 (*class_value_size)                 (Il2CppClass* klass, uint32_t* align);
    bool                    (*class_is_blittable)               (const Il2CppClass* klass);
    int                     (*class_get_flags)                  (const Il2CppClass* klass);
    bool                    (*class_is_abstract)                (const Il2CppClass* klass);
    bool                    (*class_is_interface)               (const Il2CppClass* klass);
    int                     (*class_array_element_size)         (const Il2CppClass* klass);
    const Il2CppType*       (*class_get_type)                   (Il2CppClass* klass);
    uint32_t                (*class_get_type_token)             (Il2CppClass* klass);
    bool                    (*class_has_attribute)              (Il2CppClass* klass, Il2CppClass* attr_class);
    bool                    (*class_has_references)             (Il2CppClass* klass);
    bool                    (*class_is_enum)                    (const Il2CppClass* klass);
    const Il2CppImage*      (*class_get_image)                  (Il2CppClass* klass);
    const char*             (*class_get_assemblyname)           (const Il2CppClass* klass);
    int                     (*class_get_rank)                   (const Il2CppClass* klass);
    uint32_t                (*class_get_data_size)              (const Il2CppClass* klass);
    void*                   (*class_get_static_field_data)      (const Il2CppClass* klass);

    // domain
    Il2CppDomain*           (*domain_get) ();
    const Il2CppAssembly*   (*domain_assembly_open)             (Il2CppDomain* domain, const char* name);
    const Il2CppAssembly**  (*domain_get_assemblies)            (const Il2CppDomain* domain, size_t* size);

    // exception
    void                    (*raise_exception)                  (Il2CppException*);
    Il2CppException*        (*exception_from_name_msg)          (const Il2CppImage* image, const char* name_space, const char* name, const char* msg);
    Il2CppException*        (*get_exception_argument_null)      (const char* arg);
    void                    (*format_exception)                 (const Il2CppException* ex, char* message, int message_size);
    void                    (*format_stack_trace)               (const Il2CppException* ex, char* output, int output_size);
    void                    (*unhandled_exception)              (Il2CppException*);
    void                    (*native_stack_trace)               (const Il2CppException* ex, uintptr_t** addresses, int* numFrames, char** imageUUID, char** imageName);

    // field
    int                     (*field_get_flags)                  (FieldInfo* field);
    const char*             (*field_get_name)                   (FieldInfo* field);
    Il2CppClass*            (*field_get_parent)                 (FieldInfo* field);
    size_t                  (*field_get_offset)                 (FieldInfo* field);
    const Il2CppType*       (*field_get_type)                   (FieldInfo* field);
    void                    (*field_get_value)                  (Il2CppObject* obj, FieldInfo* field, void *value);
    Il2CppObject*           (*field_get_value_object)           (FieldInfo* field, Il2CppObject* obj);
    bool                    (*field_has_attribute)              (FieldInfo* field, Il2CppClass* attr_class);
    void                    (*field_set_value)                  (Il2CppObject* obj, FieldInfo* field, void *value);
    void                    (*field_static_get_value)           (FieldInfo* field, void *value);
    void                    (*field_static_set_value)           (FieldInfo* field, void *value);
    void                    (*field_set_value_object)           (Il2CppObject* instance, FieldInfo* field, Il2CppObject* value);
    bool                    (*field_is_literal)                 (FieldInfo* field);

    // method
    const Il2CppType*       (*method_get_return_type)           (const MethodInfo* method);
    Il2CppClass*            (*method_get_declaring_type)        (const MethodInfo* method);
    const char*             (*method_get_name)                  (const MethodInfo* method);
    const MethodInfo*       (*method_get_from_reflection)       (const Il2CppReflectionMethod* method);
    Il2CppReflectionMethod* (*method_get_object)                (const MethodInfo* method, Il2CppClass* refclass);
    bool                    (*method_is_generic)                (const MethodInfo* method);
    bool                    (*method_is_inflated)               (const MethodInfo* method);
    bool                    (*method_is_instance)               (const MethodInfo* method);
    uint32_t                (*method_get_param_count)           (const MethodInfo* method);
    const Il2CppType*       (*method_get_param)                 (const MethodInfo* method, uint32_t index);
    Il2CppClass*            (*method_get_class)                 (const MethodInfo* method);
    bool                    (*method_has_attribute)             (const MethodInfo* method, Il2CppClass* attr_class);
    uint32_t                (*method_get_flags)                 (const MethodInfo* method, uint32_t* iflags);
    uint32_t                (*method_get_token)                 (const MethodInfo* method);
    const char*             (*method_get_param_name)            (const MethodInfo* method, uint32_t index);

    // property
    uint32_t                (*property_get_flags)               (PropertyInfo* prop);
    const MethodInfo*       (*property_get_get_method)          (PropertyInfo* prop);
    const MethodInfo*       (*property_get_set_method)          (PropertyInfo* prop);
    const char*             (*property_get_name)                (PropertyInfo* prop);
    Il2CppClass*            (*property_get_parent)              (PropertyInfo* prop);

    // object
    Il2CppClass*            (*object_get_class)                 (Il2CppObject* obj);
    uint32_t                (*object_get_size)                  (Il2CppObject* obj);
    const MethodInfo*       (*object_get_virtual_method)        (Il2CppObject* obj, const MethodInfo* method);
    Il2CppObject*           (*object_new)                       (const Il2CppClass* klass);
    void*                   (*object_unbox)                     (Il2CppObject* obj);

    Il2CppObject*           (*value_box)                        (Il2CppClass* klass, void* data);

    // monitor
    void                    (*monitor_enter)                    (Il2CppObject* obj);
    bool                    (*monitor_try_enter)                (Il2CppObject* obj, uint32_t timeout);
    void                    (*monitor_exit)                     (Il2CppObject* obj);
    void                    (*monitor_pulse)                    (Il2CppObject* obj);
    void                    (*monitor_pulse_all)                (Il2CppObject* obj);
    void                    (*monitor_wait)                     (Il2CppObject* obj);
    bool                    (*monitor_try_wait)                 (Il2CppObject* obj, uint32_t timeout);

    // runtime
    Il2CppObject*           (*runtime_invoke)                   (const MethodInfo* method, void* obj, void** params, Il2CppException** exc);
    Il2CppObject*           (*runtime_invoke_convert_args)      (const MethodInfo* method, void* obj, Il2CppObject** params, int paramCount, Il2CppException **exc);
    void                    (*runtime_class_init)               (Il2CppClass* klass);
    void                    (*runtime_object_init)              (Il2CppObject* obj);

    void                    (*runtime_object_init_exception)    (Il2CppObject* obj, Il2CppException** exc);

    // string
    int32_t                 (*string_length)                    (Il2CppString* str);
    Il2CppChar*             (*string_chars)                     (Il2CppString* str);
    Il2CppString*           (*string_new)                       (const char* str);
    Il2CppString*           (*string_new_len)                   (const char* str, uint32_t length);
    Il2CppString*           (*string_new_utf16)                 (const Il2CppChar* text, int32_t len);
    Il2CppString*           (*string_new_wrapper)               (const char* str);
    Il2CppString*           (*string_intern)                    (Il2CppString* str);
    Il2CppString*           (*string_is_interned)               (Il2CppString* str);

    // thread
    Il2CppThread*           (*thread_current)                   ();
    Il2CppThread*           (*thread_attach)                    (Il2CppDomain* domain);
    void                    (*thread_detach)                    (Il2CppThread* thread);

    Il2CppThread**          (*thread_get_all_attached_threads)  (size_t* size);
    bool                    (*is_vm_thread)                     (Il2CppThread* thread);

    // type
    Il2CppObject*           (*type_get_object)                  (const Il2CppType* type);
    int                     (*type_get_type)                    (const Il2CppType* type);
    Il2CppClass*            (*type_get_class_or_element_class)  (const Il2CppType* type);
    char*                   (*type_get_name)                    (const Il2CppType* type);
    bool                    (*type_is_byref)                    (const Il2CppType* type);
    uint32_t                (*type_get_attrs)                   (const Il2CppType* type);
    bool                    (*type_equals)                      (const Il2CppType* type, const Il2CppType* otherType);
    bool                    (*type_is_static)                   (const Il2CppType* type);
    bool                    (*type_is_pointer_type)             (const Il2CppType* type);

    // image
    const Il2CppAssembly*   (*image_get_assembly)               (const Il2CppImage* image);
    const char*             (*image_get_name)                   (const Il2CppImage* image);
    const char*             (*image_get_filename)               (const Il2CppImage* image);
    const MethodInfo*       (*image_get_entry_point)            (const Il2CppImage* image);

    size_t                  (*image_get_class_count)            (const Il2CppImage* image);
    const Il2CppClass*      (*image_get_class)                  (const Il2CppImage* image, size_t index);

    // Il2CppClass user data for GetComponent optimization
    void                    (*class_set_userdata)               (Il2CppClass* klass, void* userdata);
    int                     (*class_get_userdata_offset)        ();

    void                    (*set_default_thread_affinity)      (int64_t affinity_mask);

    // gchandle
    uint32_t                (*gchandle_new)                     (Il2CppObject* obj, bool pinned);
    uint32_t                (*gchandle_free)                    (uint32_t handle);

    void*                   (*import_from_engine)               (const char* sig);

    Il2CppClass* getClass(const char* const& szClass, const char* const& szNamespace, const char* const& szAssembly);
    MethodInfo*  getMethod(Il2CppClass* pClass, const char* const& szMethod, const uint8_t& nArgs);
    FieldInfo*   getSingletonField(Il2CppClass* pClass);
};