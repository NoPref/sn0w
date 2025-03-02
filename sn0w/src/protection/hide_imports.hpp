#pragma once
#include <stdint.h>
#include <dlfcn.h>
#include "../singleton.hpp"

//get pointers via dlsym not via shared library, so import symbols wont show up in disassembly

enum hi_lib : uint8_t {
    hi_lib_dl,
    hi_lib_c,
    hi_lib_gles,
    hi_lib_egl,
    hi_lib_max,
};

enum hi_sym : uint8_t {
    hi_sym_dlopen,
    hi_sym_dlsym,
    hi_sym_dladdr,
    hi_sym_mprotect,
    hi_sym_malloc,
    hi_sym_free,
    hi_sym_abort,
    hi_sym_exit,
    hi_sym_sysconf,
    hi_sym_fopen,
    hi_sym_open,
    hi_sym_fgets,
    hi_sym_strstr,
    hi_sym_strcmp,

    hi_sym_gl_active_texture,
    hi_sym_gl_attach_shader,
    hi_sym_gl_bind_attrib_location,
    hi_sym_gl_bind_buffer,
    hi_sym_gl_bind_frame_buffer,
    hi_sym_gl_bind_render_buffer,
    hi_sym_gl_bind_texture,
    hi_sym_gl_blend_color,
    hi_sym_gl_blend_equation,
    hi_sym_gl_blend_equation_separate,
    hi_sym_gl_blend_func,
    hi_sym_gl_blend_func_separate,
    hi_sym_gl_buffer_data,
    hi_sym_gl_buffer_sub_data,
    hi_sym_gl_check_frame_buffer_status,
    hi_sym_gl_clear,
    hi_sym_gl_clear_color,
    hi_sym_gl_clear_depthf,
    hi_sym_gl_clear_stencil,
    hi_sym_gl_color_mask,
    hi_sym_gl_compile_shader,
    hi_sym_gl_compressed_tex_image_2d,
    hi_sym_gl_compressed_tex_sub_image_2d,
    hi_sym_gl_copy_tex_image_2d,
    hi_sym_gl_copy_tex_sub_image_2d,
    hi_sym_gl_create_program,
    hi_sym_gl_create_shader,
    hi_sym_gl_cull_face,
    hi_sym_gl_delete_buffers,
    hi_sym_gl_delete_frame_buffers,
    hi_sym_gl_delete_program,
    hi_sym_gl_delete_render_buffers,
    hi_sym_gl_delete_shader,
    hi_sym_gl_delete_textures,
    hi_sym_gl_depth_func,
    hi_sym_gl_depth_mask,
    hi_sym_gl_depth_rangef,
    hi_sym_gl_detach_shader,
    hi_sym_gl_disable,
    hi_sym_gl_disable_vertex_attrib_array,
    hi_sym_gl_draw_arrays,
    hi_sym_gl_draw_elements,
    hi_sym_gl_enable,
    hi_sym_gl_enable_vertex_attrib_array,
    hi_sym_gl_finish,
    hi_sym_gl_flush,
    hi_sym_gl_frame_buffer_render_buffer,
    hi_sym_gl_frame_buffer_texture_2d,
    hi_sym_gl_front_face,
    hi_sym_gl_gen_buffers,
    hi_sym_gl_generate_mipmap,
    hi_sym_gl_gen_frame_buffers,
    hi_sym_gl_gen_render_buffers,
    hi_sym_gl_gen_textures,
    hi_sym_gl_get_active_attrib,
    hi_sym_gl_get_active_uniform,
    hi_sym_gl_get_attached_shaders,
    hi_sym_gl_get_attrib_location,
    hi_sym_gl_get_booleanv,
    hi_sym_gl_get_buffer_parameteriv,
    hi_sym_gl_get_error,
    hi_sym_gl_get_floatv,
    hi_sym_gl_get_frame_buffer_attachment_parameteriv,
    hi_sym_gl_get_integerv,
    hi_sym_gl_get_programiv,
    hi_sym_gl_get_program_info_log,
    hi_sym_gl_get_render_buffer_parameteriv,
    hi_sym_gl_get_shaderiv,
    hi_sym_gl_get_shader_info_log,
    hi_sym_gl_get_shader_precision_format,
    hi_sym_gl_get_shader_source,
    hi_sym_gl_get_string,
    hi_sym_gl_get_text_parameterfv,
    hi_sym_gl_get_text_parameteriv,
    hi_sym_gl_get_uniformfv,
    hi_sym_gl_get_uniformiv,
    hi_sym_gl_get_uniform_location,
    hi_sym_gl_get_vertex_attribfv,
    hi_sym_gl_get_vertex_attribiv,
    hi_sym_gl_get_vertex_attrib_pointerv,
    hi_sym_gl_hint,
    hi_sym_gl_is_buffer,
    hi_sym_gl_is_enabled,
    hi_sym_gl_is_frame_buffer,
    hi_sym_gl_is_program,
    hi_sym_gl_is_render_buffer,
    hi_sym_gl_is_shader,
    hi_sym_gl_is_texture,
    hi_sym_gl_line_width,
    hi_sym_gl_link_program,
    hi_sym_gl_pixel_storei,
    hi_sym_gl_polygon_offset,
    hi_sym_gl_read_pixels,
    hi_sym_gl_release_shader_compiler,
    hi_sym_gl_render_buffer_storage,
    hi_sym_gl_sample_coverage,
    hi_sym_gl_scissor,
    hi_sym_gl_shader_binary,
    hi_sym_gl_shader_source,
    hi_sym_gl_stencil_func,
    hi_sym_gl_stencil_func_separate,
    hi_sym_gl_stencil_mask,
    hi_sym_gl_stencil_mask_separate,
    hi_sym_gl_stencil_op,
    hi_sym_gl_stencil_op_separate,
    hi_sym_gl_tex_image_2d,
    hi_sym_gl_tex_parameterf,
    hi_sym_gl_tex_parameterfv,
    hi_sym_gl_tex_parameteri,
    hi_sym_gl_tex_parameteriv,
    hi_sym_gl_tex_sub_image_2d,
    hi_sym_gl_uniform1f,
    hi_sym_gl_uniform1fv,
    hi_sym_gl_uniform1i,
    hi_sym_gl_uniform1iv,
    hi_sym_gl_uniform2f,
    hi_sym_gl_uniform2fv,
    hi_sym_gl_uniform2i,
    hi_sym_gl_uniform2iv,
    hi_sym_gl_uniform3f,
    hi_sym_gl_uniform3fv,
    hi_sym_gl_uniform3i,
    hi_sym_gl_uniform3iv,
    hi_sym_gl_uniform4f,
    hi_sym_gl_uniform4fv,
    hi_sym_gl_uniform4i,
    hi_sym_gl_uniform4iv,
    hi_sym_gl_uniform_matrix2fv,
    hi_sym_gl_uniform_matrix3fv,
    hi_sym_gl_uniform_matrix4fv,
    hi_sym_gl_use_program,
    hi_sym_gl_validate_program,
    hi_sym_gl_vertex_attrib1f,
    hi_sym_gl_vertex_attrib1fv,
    hi_sym_gl_vertex_attrib2f,
    hi_sym_gl_vertex_attrib2fv,
    hi_sym_gl_vertex_attrib3f,
    hi_sym_gl_vertex_attrib3fv,
    hi_sym_gl_vertex_attrib4f,
    hi_sym_gl_vertex_attrib4fv,
    hi_sym_gl_vertex_attrib_pointer,
    hi_sym_gl_viewport,

    hi_sym_max,
};

class CHideImports : public CSingleton<CHideImports> {
private:
    void* m_libs[hi_lib_max]{};
public:
    bool m_bLoaded{};
    void* m_syms[hi_sym_max]{};

    CHideImports() = default;
    ~CHideImports() = default;

    bool init() noexcept;
    bool loadSym() noexcept;

    void* dlopen(const char* __path, int __flags) const noexcept;
    void* dlsym(void* __handle, const char* __symbol) const noexcept;
    int dladdr(void* __addr, Dl_info* info) const noexcept;
    int mprotect(void* __addr, size_t __size, int __prot) const noexcept;
    void* malloc(size_t __size) const noexcept;
    void free(void* __mem) const noexcept;
    void abort() const noexcept;
    void exit(int exitcode) const noexcept;
    long sysconf(int __name) const noexcept;
    const char* strstr(const char* __str, const char* __substr) const noexcept;
    int strcmp(const char* __str, const char* __str2) const noexcept;

    template<typename T>
    T call(const hi_sym& sym) const noexcept {
        return ((T(*)())this->m_syms[sym])();
    }

    template<typename T, typename TArg>
    T call(const hi_sym& sym, TArg arg) const noexcept {
        return ((T(*)(TArg))this->m_syms[sym])(arg);
    }

    template<typename T, typename TArg, typename TArg2>
    T call(const hi_sym& sym, TArg arg, TArg2 arg2) const noexcept {
        return ((T(*)(TArg,TArg2))this->m_syms[sym])(arg, arg2);
    }

    template<typename T, typename TArg, typename TArg2, typename TArg3>
    T call(const hi_sym& sym, TArg arg, TArg2 arg2, TArg3 arg3) const noexcept {
        return ((T(*)(TArg,TArg2,TArg3))this->m_syms[sym])(arg, arg2, arg3);
    }

    template<typename T, typename TArg, typename TArg2, typename TArg3, typename TArg4>
    T call(const hi_sym& sym, TArg arg, TArg2 arg2, TArg3 arg3, TArg4 arg4) const noexcept {
        return ((T(*)(TArg,TArg2,TArg3,TArg4))this->m_syms[sym])(arg, arg2, arg3, arg4);
    }

    template<typename T, typename TArg, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
    T call(const hi_sym& sym, TArg arg, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5) const noexcept {
        return ((T(*)(TArg,TArg2,TArg3,TArg4,TArg5))this->m_syms[sym])(arg, arg2, arg3, arg4, arg5);
    }

    template<typename T, typename TArg, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6>
    T call(const hi_sym& sym, TArg arg, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6) const noexcept {
        return ((T(*)(TArg,TArg2,TArg3,TArg4,TArg5,TArg6))this->m_syms[sym])(arg, arg2, arg3, arg4, arg5, arg6);
    }

    template<typename T, typename TArg, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7>
    T call(const hi_sym& sym, TArg arg, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7) const noexcept {
        return ((T(*)(TArg,TArg2,TArg3,TArg4,TArg5,TArg6,TArg7))this->m_syms[sym])(arg, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    template<typename T, typename TArg, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8>
    T call(const hi_sym& sym, TArg arg, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8) const noexcept {
        return ((T(*)(TArg,TArg2,TArg3,TArg4,TArg5,TArg6,TArg7,TArg8))this->m_syms[sym])(arg, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    }

    template<typename T, typename TArg, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9>
    T call(const hi_sym& sym, TArg arg, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9) const noexcept {
        return ((T(*)(TArg,TArg2,TArg3,TArg4,TArg5,TArg6,TArg7,TArg8,TArg9))this->m_syms[sym])(arg, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
    }
};