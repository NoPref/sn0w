#include <dlfcn.h>
#include <unistd.h>
#include <string.h>

#include "../oxorany/include.h"
#include "../xdl/include/xdl.h"
#include "il2cpp-api.h"
#include "globals.hpp"

void il2cpp_api_t::init() {

    static void* (*dlsym)(void*, const char*);
    if(dlsym == NULL)
        dlsym = (decltype(dlsym))g.hooks.orig.libc.dlsym;

    // array
    this->array_class_get                 = (decltype(this->array_class_get))                dlsym(g.hIl2Cpp, oxorany("il2cpp_array_class_get"));
    this->array_length                    = (decltype(this->array_length))                   dlsym(g.hIl2Cpp, oxorany("il2cpp_array_length"));
    this->array_get_byte_length           = (decltype(this->array_get_byte_length))          dlsym(g.hIl2Cpp, oxorany("il2cpp_array_get_byte_length"));
    this->array_new                       = (decltype(this->array_new))                      dlsym(g.hIl2Cpp, oxorany("il2cpp_array_new"));
    this->array_new_specific              = (decltype(this->array_new_specific))             dlsym(g.hIl2Cpp, oxorany("il2cpp_array_new_specific"));
    this->array_new_full                  = (decltype(this->array_new_full))                 dlsym(g.hIl2Cpp, oxorany("il2cpp_array_new_full"));
    this->bounded_array_class_get         = (decltype(this->bounded_array_class_get))        dlsym(g.hIl2Cpp, oxorany("il2cpp_bounded_array_class_get"));
    this->array_element_size              = (decltype(this->array_element_size))             dlsym(g.hIl2Cpp, oxorany("il2cpp_array_element_size"));

    // assembly
    this->assembly_get_image              = (decltype(this->assembly_get_image))             dlsym(g.hIl2Cpp, oxorany("il2cpp_assembly_get_image"));

    // class
    this->class_for_each                  = (decltype(this->class_for_each))                 dlsym(g.hIl2Cpp, oxorany("il2cpp_class_for_each"));
    this->class_enum_basetype             = (decltype(this->class_enum_basetype))            dlsym(g.hIl2Cpp, oxorany("il2cpp_class_enum_basetype"));
    this->class_is_generic                = (decltype(this->class_is_generic))               dlsym(g.hIl2Cpp, oxorany("il2cpp_class_is_generic"));
    this->class_is_inflated               = (decltype(this->class_is_inflated))              dlsym(g.hIl2Cpp, oxorany("il2cpp_class_is_inflated"));
    this->class_is_assignable_from        = (decltype(this->class_is_assignable_from))       dlsym(g.hIl2Cpp, oxorany("il2cpp_class_is_assignable_from"));
    this->class_is_subclass_of            = (decltype(this->class_is_subclass_of))           dlsym(g.hIl2Cpp, oxorany("il2cpp_class_is_subclass_of"));
    this->class_has_parent                = (decltype(this->class_has_parent))               dlsym(g.hIl2Cpp, oxorany("il2cpp_class_has_parent"));
    this->class_from_type                 = (decltype(this->class_from_type))                dlsym(g.hIl2Cpp, oxorany("il2cpp_class_from_type"));
    this->class_from_name                 = (decltype(this->class_from_name))                dlsym(g.hIl2Cpp, oxorany("il2cpp_class_from_name"));
    this->class_from_system_type          = (decltype(this->class_from_system_type))         dlsym(g.hIl2Cpp, oxorany("il2cpp_class_from_system_type"));
    this->class_get_element_class         = (decltype(this->class_get_element_class))        dlsym(g.hIl2Cpp, oxorany("il2cpp_class_get_element_class"));
    this->class_get_events                = (decltype(this->class_get_events))               dlsym(g.hIl2Cpp, oxorany("il2cpp_class_get_events"));
    this->class_get_fields                = (decltype(this->class_get_fields))               dlsym(g.hIl2Cpp, oxorany("il2cpp_class_get_fields"));
    this->class_get_nested_types          = (decltype(this->class_get_nested_types))         dlsym(g.hIl2Cpp, oxorany("il2cpp_class_get_nested_types"));
    this->class_get_interfaces            = (decltype(this->class_get_interfaces))           dlsym(g.hIl2Cpp, oxorany("il2cpp_class_get_interfaces"));
    this->class_get_properties            = (decltype(this->class_get_properties))           dlsym(g.hIl2Cpp, oxorany("il2cpp_class_get_properties"));
    this->class_get_property_from_name    = (decltype(this->class_get_property_from_name))   dlsym(g.hIl2Cpp, oxorany("il2cpp_class_get_property_from_name"));
    this->class_get_field_from_name       = (decltype(this->class_get_field_from_name))      dlsym(g.hIl2Cpp, oxorany("il2cpp_class_get_field_from_name"));
    this->class_get_methods               = (decltype(this->class_get_methods))              dlsym(g.hIl2Cpp, oxorany("il2cpp_class_get_methods"));
    this->class_get_method_from_name      = (decltype(this->class_get_method_from_name))     dlsym(g.hIl2Cpp, oxorany("il2cpp_class_get_method_from_name"));
    this->class_get_name                  = (decltype(this->class_get_name))                 dlsym(g.hIl2Cpp, oxorany("il2cpp_class_get_name"));
    this->class_get_namespace             = (decltype(this->class_get_namespace))            dlsym(g.hIl2Cpp, oxorany("il2cpp_class_get_namespace"));
    this->class_get_parent                = (decltype(this->class_get_parent))               dlsym(g.hIl2Cpp, oxorany("il2cpp_class_get_parent"));
    this->class_get_declaring_type        = (decltype(this->class_get_declaring_type))       dlsym(g.hIl2Cpp, oxorany("il2cpp_class_get_declaring_type"));
    this->class_instance_size             = (decltype(this->class_instance_size))            dlsym(g.hIl2Cpp, oxorany("il2cpp_class_instance_size"));
    this->class_num_fields                = (decltype(this->class_num_fields))               dlsym(g.hIl2Cpp, oxorany("il2cpp_class_num_fields"));
    this->class_is_valuetype              = (decltype(this->class_is_valuetype))             dlsym(g.hIl2Cpp, oxorany("il2cpp_class_is_valuetype"));
    this->class_value_size                = (decltype(this->class_value_size))               dlsym(g.hIl2Cpp, oxorany("il2cpp_class_value_size"));
    this->class_is_blittable              = (decltype(this->class_is_blittable))             dlsym(g.hIl2Cpp, oxorany("il2cpp_class_is_blittable"));
    this->class_get_flags                 = (decltype(this->class_get_flags))                dlsym(g.hIl2Cpp, oxorany("il2cpp_class_get_flags"));
    this->class_is_abstract               = (decltype(this->class_is_abstract))              dlsym(g.hIl2Cpp, oxorany("il2cpp_class_is_abstract"));
    this->class_is_interface              = (decltype(this->class_is_interface))             dlsym(g.hIl2Cpp, oxorany("il2cpp_class_is_interface"));
    this->class_array_element_size        = (decltype(this->class_array_element_size))       dlsym(g.hIl2Cpp, oxorany("il2cpp_class_array_element_size"));
    this->class_get_type                  = (decltype(this->class_get_type))                 dlsym(g.hIl2Cpp, oxorany("il2cpp_class_get_type"));
    this->class_get_type_token            = (decltype(this->class_get_type_token))           dlsym(g.hIl2Cpp, oxorany("il2cpp_class_get_type_token"));
    this->class_has_attribute             = (decltype(this->class_has_attribute))            dlsym(g.hIl2Cpp, oxorany("il2cpp_class_has_attribute"));
    this->class_has_references            = (decltype(this->class_has_references))           dlsym(g.hIl2Cpp, oxorany("il2cpp_class_has_references"));
    this->class_is_enum                   = (decltype(this->class_is_enum))                  dlsym(g.hIl2Cpp, oxorany("il2cpp_class_is_enum"));
    this->class_get_image                 = (decltype(this->class_get_image))                dlsym(g.hIl2Cpp, oxorany("il2cpp_class_get_image"));
    this->class_get_assemblyname          = (decltype(this->class_get_assemblyname))         dlsym(g.hIl2Cpp, oxorany("il2cpp_class_get_assemblyname"));
    this->class_get_rank                  = (decltype(this->class_get_rank))                 dlsym(g.hIl2Cpp, oxorany("il2cpp_class_get_rant"));
    this->class_get_data_size             = (decltype(this->class_get_data_size))            dlsym(g.hIl2Cpp, oxorany("il2cpp_class_get_data_size"));
    this->class_get_static_field_data     = (decltype(this->class_get_static_field_data))    dlsym(g.hIl2Cpp, oxorany("il2cpp_class_get_static_field_data"));

    // domain
    this->domain_get                      = (decltype(this->domain_get))                     dlsym(g.hIl2Cpp, oxorany("il2cpp_domain_get"));
    this->domain_assembly_open            = (decltype(this->domain_assembly_open))           dlsym(g.hIl2Cpp, oxorany("il2cpp_domain_assembly_open"));
    this->domain_get_assemblies           = (decltype(this->domain_get_assemblies))          dlsym(g.hIl2Cpp, oxorany("il2cpp_domain_get_assemblies"));

    // exception
    this->raise_exception                 = (decltype(this->raise_exception))                dlsym(g.hIl2Cpp, oxorany("il2cpp_raise_exception"));
    this->exception_from_name_msg         = (decltype(this->exception_from_name_msg))        dlsym(g.hIl2Cpp, oxorany("il2cpp_exception_from_name_msg"));
    this->get_exception_argument_null     = (decltype(this->get_exception_argument_null))    dlsym(g.hIl2Cpp, oxorany("il2cpp_get_exception_argument_null"));
    this->format_exception                = (decltype(this->format_exception))               dlsym(g.hIl2Cpp, oxorany("il2cpp_format_exception"));
    this->format_stack_trace              = (decltype(this->format_stack_trace))             dlsym(g.hIl2Cpp, oxorany("il2cpp_format_stack_trace"));
    this->unhandled_exception             = (decltype(this->unhandled_exception))            dlsym(g.hIl2Cpp, oxorany("il2cpp_unhandled_exception"));
    this->native_stack_trace              = (decltype(this->native_stack_trace))             dlsym(g.hIl2Cpp, oxorany("il2cpp_native_stack_trace"));

    // field
    this->field_get_flags                 = (decltype(this->field_get_flags))                dlsym(g.hIl2Cpp, oxorany("il2cpp_field_get_flags"));
    this->field_get_name                  = (decltype(this->field_get_name))                 dlsym(g.hIl2Cpp, oxorany("il2cpp_field_get_name"));
    this->field_get_parent                = (decltype(this->field_get_parent))               dlsym(g.hIl2Cpp, oxorany("il2cpp_field_get_parent"));
    this->field_get_offset                = (decltype(this->field_get_offset))               dlsym(g.hIl2Cpp, oxorany("il2cpp_field_get_offset"));
    this->field_get_type                  = (decltype(this->field_get_type))                 dlsym(g.hIl2Cpp, oxorany("il2cpp_field_get_type"));
    this->field_get_value                 = (decltype(this->field_get_value))                dlsym(g.hIl2Cpp, oxorany("il2cpp_field_get_value"));
    this->field_get_value_object          = (decltype(this->field_get_value_object))         dlsym(g.hIl2Cpp, oxorany("il2cpp_field_get_value_object"));
    this->field_has_attribute             = (decltype(this->field_has_attribute))            dlsym(g.hIl2Cpp, oxorany("il2cpp_field_has_attribute"));
    this->field_set_value                 = (decltype(this->field_set_value))                dlsym(g.hIl2Cpp, oxorany("il2cpp_field_set_value"));
    //this->field_static_get_value          = (decltype(this->field_static_get_value))         dlsym(g.hIl2Cpp, oxorany("il2cpp_field_static_get_value")); 
    //this->field_static_set_value          = (decltype(this->field_static_set_value))         dlsym(g.hIl2Cpp, oxorany("il2cpp_field_static_set_value"));
    this->field_set_value_object          = (decltype(this->field_set_value_object))         dlsym(g.hIl2Cpp, oxorany("il2cpp_field_set_value_object"));
    this->field_is_literal                = (decltype(this->field_is_literal))               dlsym(g.hIl2Cpp, oxorany("il2cpp_field_is_literal"));

    // method
    this->method_get_return_type          = (decltype(this->method_get_return_type))         dlsym(g.hIl2Cpp, oxorany("il2cpp_method_get_return_type"));
    this->method_get_declaring_type       = (decltype(this->method_get_declaring_type))      dlsym(g.hIl2Cpp, oxorany("il2cpp_method_get_declaring_type"));
    this->method_get_name                 = (decltype(this->method_get_name))                dlsym(g.hIl2Cpp, oxorany("il2cpp_method_get_name"));
    this->method_get_from_reflection      = (decltype(this->method_get_from_reflection))     dlsym(g.hIl2Cpp, oxorany("il2cpp_method_get_from_reflection"));
    this->method_get_object               = (decltype(this->method_get_object))              dlsym(g.hIl2Cpp, oxorany("il2cpp_method_get_object"));
    this->method_is_generic               = (decltype(this->method_is_generic))              dlsym(g.hIl2Cpp, oxorany("il2cpp_method_is_generic"));
    this->method_is_inflated              = (decltype(this->method_is_inflated))             dlsym(g.hIl2Cpp, oxorany("il2cpp_method_is_inflated"));
    this->method_is_instance              = (decltype(this->method_is_instance))             dlsym(g.hIl2Cpp, oxorany("il2cpp_method_is_instance"));
    this->method_get_param_count          = (decltype(this->method_get_param_count))         dlsym(g.hIl2Cpp, oxorany("il2cpp_method_get_param_count"));
    this->method_get_param                = (decltype(this->method_get_param))               dlsym(g.hIl2Cpp, oxorany("il2cpp_method_get_param"));
    this->method_get_class                = (decltype(this->method_get_class))               dlsym(g.hIl2Cpp, oxorany("il2cpp_method_get_class"));
    this->method_has_attribute            = (decltype(this->method_has_attribute))           dlsym(g.hIl2Cpp, oxorany("il2cpp_method_has_attribute"));
    this->method_get_flags                = (decltype(this->method_get_flags))               dlsym(g.hIl2Cpp, oxorany("il2cpp_method_get_flags"));
    this->method_get_token                = (decltype(this->method_get_token))               dlsym(g.hIl2Cpp, oxorany("il2cpp_method_get_token"));
    this->method_get_param_name           = (decltype(this->method_get_param_name))          dlsym(g.hIl2Cpp, oxorany("il2cpp_method_get_param_name"));

    // property
    this->property_get_flags              = (decltype(this->property_get_flags))             dlsym(g.hIl2Cpp, oxorany("il2cpp_property_get_flags"));
    this->property_get_get_method         = (decltype(this->property_get_get_method))        dlsym(g.hIl2Cpp, oxorany("il2cpp_property_get_get_method"));
    this->property_get_set_method         = (decltype(this->property_get_set_method))        dlsym(g.hIl2Cpp, oxorany("il2cpp_property_get_set_method"));
    this->property_get_name               = (decltype(this->property_get_name))              dlsym(g.hIl2Cpp, oxorany("il2cpp_property_get_name"));
    this->property_get_parent             = (decltype(this->property_get_parent))            dlsym(g.hIl2Cpp, oxorany("il2cpp_property_get_parent"));

    // object
    this->object_get_class                = (decltype(this->object_get_class))               dlsym(g.hIl2Cpp, oxorany("il2cpp_object_get_class"));
    this->object_get_size                 = (decltype(this->object_get_size))                dlsym(g.hIl2Cpp, oxorany("il2cpp_object_get_size"));
    this->object_get_virtual_method       = (decltype(this->object_get_virtual_method))      dlsym(g.hIl2Cpp, oxorany("il2cpp_object_get_virtual_method"));
    this->object_new                      = (decltype(this->object_new))                     dlsym(g.hIl2Cpp, oxorany("il2cpp_object_new"));
    this->object_unbox                    = (decltype(this->object_unbox))                   dlsym(g.hIl2Cpp, oxorany("il2cpp_object_unbox"));

    this->value_box                       = (decltype(this->value_box))                      dlsym(g.hIl2Cpp, oxorany("il2cpp_value_box"));

    // monitor
    this->monitor_enter                   = (decltype(this->monitor_enter))                  dlsym(g.hIl2Cpp, oxorany("il2cpp_monitor_enter"));
    this->monitor_try_enter               = (decltype(this->monitor_try_enter))              dlsym(g.hIl2Cpp, oxorany("il2cpp_monitor_try_enter"));
    this->monitor_exit                    = (decltype(this->monitor_exit))                   dlsym(g.hIl2Cpp, oxorany("il2cpp_monitor_exit"));
    this->monitor_pulse                   = (decltype(this->monitor_pulse))                  dlsym(g.hIl2Cpp, oxorany("il2cpp_monitor_pulse"));
    this->monitor_pulse_all               = (decltype(this->monitor_pulse_all))              dlsym(g.hIl2Cpp, oxorany("il2cpp_monitor_pulse_all"));
    this->monitor_wait                    = (decltype(this->monitor_wait))                   dlsym(g.hIl2Cpp, oxorany("il2cpp_monitor_wait"));
    this->monitor_try_wait                = (decltype(this->monitor_try_wait))               dlsym(g.hIl2Cpp, oxorany("il2cpp_monitor_try_wait"));

    // runtime
    this->runtime_invoke                  = (decltype(this->runtime_invoke))                 dlsym(g.hIl2Cpp, oxorany("il2cpp_runtime_invoke"));
    this->runtime_invoke_convert_args     = (decltype(this->runtime_invoke_convert_args))    dlsym(g.hIl2Cpp, oxorany("il2cpp_runtime_invoke_convert_args"));
    this->runtime_class_init              = (decltype(this->runtime_class_init))             dlsym(g.hIl2Cpp, oxorany("il2cpp_runtime_class_init"));
    this->runtime_object_init             = (decltype(this->runtime_object_init))            dlsym(g.hIl2Cpp, oxorany("il2cpp_runtime_object_init"));

    this->runtime_object_init_exception   = (decltype(this->runtime_object_init_exception))  dlsym(g.hIl2Cpp, oxorany("il2cpp_runtime_object_init_exception"));

    // string
    this->string_length                   = (decltype(this->string_length))                  dlsym(g.hIl2Cpp, oxorany("il2cpp_string_length"));
    this->string_chars                    = (decltype(this->string_chars))                   dlsym(g.hIl2Cpp, oxorany("il2cpp_string_chars"));
    this->string_new                      = (decltype(this->string_new))                     dlsym(g.hIl2Cpp, oxorany("il2cpp_string_new"));
    this->string_new_len                  = (decltype(this->string_new_len))                 dlsym(g.hIl2Cpp, oxorany("il2cpp_string_new_len"));
    this->string_new_utf16                = (decltype(this->string_new_utf16))               dlsym(g.hIl2Cpp, oxorany("il2cpp_string_new_utf16"));
    this->string_new_wrapper              = (decltype(this->string_new_wrapper))             dlsym(g.hIl2Cpp, oxorany("il2cpp_string_new_wrapper"));
    this->string_intern                   = (decltype(this->string_intern))                  dlsym(g.hIl2Cpp, oxorany("il2cpp_string_intern"));
    this->string_is_interned              = (decltype(this->string_is_interned))             dlsym(g.hIl2Cpp, oxorany("il2cpp_string_is_interned"));

    // thread
    this->thread_current                  = (decltype(this->thread_current))                 dlsym(g.hIl2Cpp, oxorany("il2cpp_thread_current"));
    this->thread_attach                   = (decltype(this->thread_attach))                  dlsym(g.hIl2Cpp, oxorany("il2cpp_thread_attach"));
    this->thread_detach                   = (decltype(this->thread_detach))                  dlsym(g.hIl2Cpp, oxorany("il2cpp_thread_detach"));

    this->thread_get_all_attached_threads = (decltype(this->thread_get_all_attached_threads))dlsym(g.hIl2Cpp, oxorany("il2cpp_thread_get_all_attached_threads"));
    this->is_vm_thread                    = (decltype(this->is_vm_thread))                   dlsym(g.hIl2Cpp, oxorany("il2cpp_is_vm_thread"));

    // type
    this->type_get_object                 = (decltype(this->type_get_object))                dlsym(g.hIl2Cpp, oxorany("il2cpp_type_get_object"));
    this->type_get_type                   = (decltype(this->type_get_type))                  dlsym(g.hIl2Cpp, oxorany("il2cpp_type_get_type"));
    this->type_get_class_or_element_class = (decltype(this->type_get_class_or_element_class))dlsym(g.hIl2Cpp, oxorany("il2cpp_type_get_class_or_element_class"));
    this->type_get_name                   = (decltype(this->type_get_name))                  dlsym(g.hIl2Cpp, oxorany("il2cpp_type_get_name"));
    this->type_is_byref                   = (decltype(this->type_is_byref))                  dlsym(g.hIl2Cpp, oxorany("il2cpp_type_is_byref"));
    this->type_get_attrs                  = (decltype(this->type_get_attrs))                 dlsym(g.hIl2Cpp, oxorany("il2cpp_type_get_attrs"));
    this->type_equals                     = (decltype(this->type_equals))                    dlsym(g.hIl2Cpp, oxorany("il2cpp_type_equals"));
    this->type_is_static                  = (decltype(this->type_is_static))                 dlsym(g.hIl2Cpp, oxorany("il2cpp_type_is_static"));
    this->type_is_pointer_type            = (decltype(this->type_is_pointer_type))           dlsym(g.hIl2Cpp, oxorany("il2cpp_type_is_pointer_type"));

    // image
    this->image_get_assembly              = (decltype(this->image_get_assembly))             dlsym(g.hIl2Cpp, oxorany("il2cpp_image_get_assembly"));
    this->image_get_name                  = (decltype(this->image_get_name))                 dlsym(g.hIl2Cpp, oxorany("il2cpp_image_get_name"));
    this->image_get_filename              = (decltype(this->image_get_filename))             dlsym(g.hIl2Cpp, oxorany("il2cpp_image_get_filename"));
    this->image_get_entry_point           = (decltype(this->image_get_entry_point))          dlsym(g.hIl2Cpp, oxorany("il2cpp_image_get_entry_point"));

    this->image_get_class_count           = (decltype(this->image_get_class_count))          dlsym(g.hIl2Cpp, oxorany("il2cpp_image_get_class_count"));
    this->image_get_class                 = (decltype(this->image_get_class))                dlsym(g.hIl2Cpp, oxorany("il2cpp_image_get_class"));

    // Il2CppClass user data for GetComponent optimization
    this->class_set_userdata              = (decltype(this->class_set_userdata))             dlsym(g.hIl2Cpp, oxorany("il2cpp_class_set_userdata"));
    this->class_get_userdata_offset       = (decltype(this->class_get_userdata_offset))      dlsym(g.hIl2Cpp, oxorany("il2cpp_class_get_userdata_offset"));

    this->set_default_thread_affinity     = (decltype(this->set_default_thread_affinity))    dlsym(g.hIl2Cpp, oxorany("il2cpp_set_default_thread_affinity"));
    this->gchandle_new                    = (decltype(this->gchandle_new))                   dlsym(g.hIl2Cpp, oxorany("il2cpp_gchandle_new"));
    this->gchandle_free                   = (decltype(this->gchandle_free))                  dlsym(g.hIl2Cpp, oxorany("il2cpp_gchandle_free"));

    //hidden
    this->import_from_engine              = (decltype(this->import_from_engine))(g.lpBase + oxorany(0x20F1878));
    this->field_static_get_value          = (decltype(this->field_static_get_value))(g.lpBase + oxorany(0x2102328)); //74 FA FF 97 E8 17 40 F9
};

Il2CppClass* il2cpp_api_t::getClass(const char* const& szClass, const char* const& szNamespase, const char* const& szAssembly) {
    const Il2CppAssembly* pAssembly = this->domain_assembly_open(NULL, szAssembly);
    if(pAssembly != NULL) {
        const Il2CppImage* pImg = this->assembly_get_image(pAssembly);
        Il2CppClass* ret = this->class_from_name(pImg, szNamespase, szClass);
        return ret;
    } 
    return NULL;
}

MethodInfo* il2cpp_api_t::getMethod(Il2CppClass* pClass, const char* const& szMethod, const uint8_t& nArgs) {
    if(pClass != NULL) {
        void* pIter{};
        while(const MethodInfo* ret = this->class_get_methods(pClass, &pIter)) {
            if(!strcmp(this->method_get_name(ret), szMethod) && this->method_get_param_count(ret) == nArgs) {
                return (MethodInfo*)ret;
            } 
        } 
    }
    return NULL;
}

FieldInfo* il2cpp_api_t::getSingletonField(Il2CppClass* pClass) {
    const char* const szClassName = g.il2cpp.class_get_name(pClass);
    void* iter{};
    while(FieldInfo* field = g.il2cpp.class_get_fields(g.il2cpp.class_get_parent(pClass), &iter)) {
        void* iter2{};
        Il2CppClass* pFieldClass = g.il2cpp.type_get_class_or_element_class(g.il2cpp.field_get_type(field));
        if(pFieldClass != NULL) {
            while(FieldInfo* field2 = g.il2cpp.class_get_fields(pFieldClass, &iter2)) {
                const char* const& szFieldClassName = g.il2cpp.class_get_name(g.il2cpp.type_get_class_or_element_class(g.il2cpp.field_get_type(field2)));
                if(!strcmp(szClassName, szFieldClassName)) {
                    return field;
                }
            }
        }
    }
    return NULL;
}