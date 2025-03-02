#include "hide_imports.hpp"
#include "../includes/oxorany/include.h"
#include "../includes/xdl/include/xdl.h"

#include <android/log.h> //temp

bool CHideImports::init() noexcept {
    if((this->m_libs[hi_lib_dl] = xdl_open(oxorany("libdl.so"), 0)) == NULL)
        return false;

    if((this->m_libs[hi_lib_c] = xdl_open(oxorany("libc.so"), 0)) == NULL)
        return false;

    if((this->m_libs[hi_lib_gles] = xdl_open(oxorany("/system/lib64/libGLESv2.so"), 0)) == NULL)
        return false;

    if((this->m_libs[hi_lib_egl] = xdl_open(oxorany("/system/lib64/libEGL.so"), 0)) == NULL)
        return false;

    return true;
}

bool CHideImports::loadSym() noexcept {
    this->m_syms[hi_sym_dlopen] = xdl_sym(this->m_libs[hi_lib_dl], oxorany("dlopen"), NULL);
    this->m_syms[hi_sym_dlsym] = xdl_sym(this->m_libs[hi_lib_dl], oxorany("dlsym"), NULL);
    this->m_syms[hi_sym_dladdr] = xdl_sym(this->m_libs[hi_lib_dl], oxorany("dladdr"), NULL);

    this->m_syms[hi_sym_mprotect] = xdl_sym(this->m_libs[hi_lib_c], oxorany("mprotect"), NULL);
    this->m_syms[hi_sym_malloc] = xdl_sym(this->m_libs[hi_lib_c], oxorany("malloc"), NULL);
    this->m_syms[hi_sym_free] = xdl_sym(this->m_libs[hi_lib_c], oxorany("free"), NULL);
    this->m_syms[hi_sym_abort] = xdl_sym(this->m_libs[hi_lib_c], oxorany("abort"), NULL);
    this->m_syms[hi_sym_exit] = xdl_sym(this->m_libs[hi_lib_c], oxorany("exit"), NULL);
    this->m_syms[hi_sym_sysconf] = xdl_sym(this->m_libs[hi_lib_c], oxorany("sysconf"), NULL);
    this->m_syms[hi_sym_fopen] = xdl_sym(this->m_libs[hi_lib_c], oxorany("fopen64"), NULL);
    this->m_syms[hi_sym_open] = xdl_sym(this->m_libs[hi_lib_c], oxorany("open64"), NULL);
    this->m_syms[hi_sym_fgets] = xdl_sym(this->m_libs[hi_lib_c], oxorany("fgets"), NULL);
    this->m_syms[hi_sym_strstr] = xdl_sym(this->m_libs[hi_lib_c], oxorany("strstr"), NULL);
    this->m_syms[hi_sym_strcmp] = xdl_sym(this->m_libs[hi_lib_c], oxorany("strcmp"), NULL);

    this->m_syms[hi_sym_gl_active_texture] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glActiveTexture"), NULL);
    this->m_syms[hi_sym_gl_attach_shader] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glAttachShader"), NULL);
    this->m_syms[hi_sym_gl_bind_attrib_location] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glBindAttribLocation"), NULL);
    this->m_syms[hi_sym_gl_bind_buffer] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glBindBuffer"), NULL);
    this->m_syms[hi_sym_gl_bind_frame_buffer] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glBindFrameBuffer"), NULL);
    this->m_syms[hi_sym_gl_bind_render_buffer] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glBindRenderBuffer"), NULL);
    this->m_syms[hi_sym_gl_bind_texture] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glBindTexture"), NULL);
    this->m_syms[hi_sym_gl_blend_color] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glBlendColor"), NULL);
    this->m_syms[hi_sym_gl_blend_equation] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glBlendEquation"), NULL);
    this->m_syms[hi_sym_gl_blend_equation_separate] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glBlendEquationSeparate"), NULL);
    this->m_syms[hi_sym_gl_blend_func] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glBlendFunc"), NULL);
    this->m_syms[hi_sym_gl_blend_func_separate] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glBlendFuncSeparate"), NULL);
    this->m_syms[hi_sym_gl_buffer_data] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glBufferData"), NULL);
    this->m_syms[hi_sym_gl_buffer_sub_data] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glBufferSubData"), NULL);
    this->m_syms[hi_sym_gl_clear] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glClear"), NULL);
    this->m_syms[hi_sym_gl_clear_color] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glClearColor"), NULL);
    this->m_syms[hi_sym_gl_clear_depthf] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glClearDepthf"), NULL);
    this->m_syms[hi_sym_gl_clear_stencil] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glClearStencil"), NULL);
    this->m_syms[hi_sym_gl_color_mask] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glColorMask"), NULL);
    this->m_syms[hi_sym_gl_compile_shader] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glCompileShader"), NULL);
    this->m_syms[hi_sym_gl_compressed_tex_image_2d] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glCompressedTexImage2D"), NULL);
    this->m_syms[hi_sym_gl_compressed_tex_sub_image_2d] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glCompressedTexSubImage2D"), NULL);
    this->m_syms[hi_sym_gl_copy_tex_image_2d] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glCopyTexImage2D"), NULL);
    this->m_syms[hi_sym_gl_copy_tex_sub_image_2d] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glCopyTexSubImage2D"), NULL);
    this->m_syms[hi_sym_gl_create_program] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glCreateProgram"), NULL);
    this->m_syms[hi_sym_gl_create_shader] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glCreateShader"), NULL);
    this->m_syms[hi_sym_gl_cull_face] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glCullFace"), NULL);
    this->m_syms[hi_sym_gl_delete_buffers] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glDeleteBuffers"), NULL);
    this->m_syms[hi_sym_gl_delete_frame_buffers] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glDeleteFrameBuffers"), NULL);
    this->m_syms[hi_sym_gl_delete_program] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glDeleteProgram"), NULL);
    this->m_syms[hi_sym_gl_delete_render_buffers] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glDeleteRenderBuffers"), NULL);
    this->m_syms[hi_sym_gl_delete_shader] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glDeleteShader"), NULL);
    this->m_syms[hi_sym_gl_delete_textures] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glDeleteTextures"), NULL);
    this->m_syms[hi_sym_gl_depth_func] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glDepthFunc"), NULL);
    this->m_syms[hi_sym_gl_depth_mask] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glDepthMask"), NULL);
    this->m_syms[hi_sym_gl_depth_rangef] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glDepthRangef"), NULL);
    this->m_syms[hi_sym_gl_detach_shader] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glDetachShader"), NULL);
    this->m_syms[hi_sym_gl_disable] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glDisable"), NULL);
    this->m_syms[hi_sym_gl_disable_vertex_attrib_array] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glDisableVertexAttribArray"), NULL);
    this->m_syms[hi_sym_gl_draw_arrays] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glDrawArrays"), NULL);
    this->m_syms[hi_sym_gl_draw_elements] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glDrawElements"), NULL);
    this->m_syms[hi_sym_gl_enable] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glEnable"), NULL);
    this->m_syms[hi_sym_gl_enable_vertex_attrib_array] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glEnableVertexAttribArray"), NULL);
    this->m_syms[hi_sym_gl_finish] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glFinish"), NULL);
    this->m_syms[hi_sym_gl_flush] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glFlush"), NULL);
    this->m_syms[hi_sym_gl_frame_buffer_render_buffer] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glFramebufferRenderbuffer"), NULL);
    this->m_syms[hi_sym_gl_frame_buffer_texture_2d] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glFramebufferTexture2D"), NULL);
    this->m_syms[hi_sym_gl_front_face] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glFrontFace"), NULL);
    this->m_syms[hi_sym_gl_gen_buffers] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGenBuffers"), NULL);
    this->m_syms[hi_sym_gl_generate_mipmap] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGenerateMipmap"), NULL);
    this->m_syms[hi_sym_gl_gen_frame_buffers] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGenFramebuffers"), NULL);
    this->m_syms[hi_sym_gl_gen_render_buffers] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGenRenderbuffers"), NULL);
    this->m_syms[hi_sym_gl_gen_textures] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGenTextures"), NULL);
    this->m_syms[hi_sym_gl_get_active_attrib] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGetActiveAttrib"), NULL);
    this->m_syms[hi_sym_gl_get_active_uniform] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGetActiveUniform"), NULL);
    this->m_syms[hi_sym_gl_get_attached_shaders] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGetAttachedShaders"), NULL);
    this->m_syms[hi_sym_gl_get_attrib_location] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGetAttribLocation"), NULL);
    this->m_syms[hi_sym_gl_get_booleanv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGetBooleanv"), NULL);
    this->m_syms[hi_sym_gl_get_buffer_parameteriv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGetBufferParameteriv"), NULL);
    this->m_syms[hi_sym_gl_get_error] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGetError"), NULL);
    this->m_syms[hi_sym_gl_get_floatv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGetFloatv"), NULL);
    this->m_syms[hi_sym_gl_get_frame_buffer_attachment_parameteriv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGetFramebufferAttachmentParameteriv"), NULL);
    this->m_syms[hi_sym_gl_get_integerv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGetIntegerv"), NULL);
    this->m_syms[hi_sym_gl_get_programiv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGetProgramiv"), NULL);
    this->m_syms[hi_sym_gl_get_program_info_log] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGetProgramInfoLog"), NULL);
    this->m_syms[hi_sym_gl_get_render_buffer_parameteriv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGetRenderbufferParameteriv"), NULL);
    this->m_syms[hi_sym_gl_get_shaderiv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGetShaderiv"), NULL);
    this->m_syms[hi_sym_gl_get_shader_info_log] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGetShaderInfoLog"), NULL);
    this->m_syms[hi_sym_gl_get_shader_precision_format] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGetShaderPrecisionFormat"), NULL);
    this->m_syms[hi_sym_gl_get_shader_source] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGetShaderSource"), NULL);
    this->m_syms[hi_sym_gl_get_string] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGetString"), NULL);
    this->m_syms[hi_sym_gl_get_text_parameterfv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGetTexParameterfv"), NULL);
    this->m_syms[hi_sym_gl_get_text_parameteriv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGetTexParameteriv"), NULL);
    this->m_syms[hi_sym_gl_get_uniformfv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGetUniformfv"), NULL);
    this->m_syms[hi_sym_gl_get_uniformiv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGetUniformiv"), NULL);
    this->m_syms[hi_sym_gl_get_uniform_location] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGetUniformLocation"), NULL);
    this->m_syms[hi_sym_gl_get_vertex_attribfv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGetVertexAttribfv"), NULL);
    this->m_syms[hi_sym_gl_get_vertex_attribiv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGetVertexAttribiv"), NULL);
    this->m_syms[hi_sym_gl_get_vertex_attrib_pointerv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glGetVertexAttribPointerv"), NULL);
    this->m_syms[hi_sym_gl_hint] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glHint"), NULL);
    this->m_syms[hi_sym_gl_is_buffer] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glIsBuffer"), NULL);
    this->m_syms[hi_sym_gl_is_enabled] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glIsEnabled"), NULL);
    this->m_syms[hi_sym_gl_is_frame_buffer] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glIsFramebuffer"), NULL);
    this->m_syms[hi_sym_gl_is_program] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glIsProgram"), NULL);
    this->m_syms[hi_sym_gl_is_render_buffer] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glIsRenderbuffer"), NULL);
    this->m_syms[hi_sym_gl_is_shader] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glIsShader"), NULL);
    this->m_syms[hi_sym_gl_is_texture] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glIsTexture"), NULL);
    this->m_syms[hi_sym_gl_line_width] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glLineWidth"), NULL);
    this->m_syms[hi_sym_gl_link_program] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glLinkProgram"), NULL);
    this->m_syms[hi_sym_gl_pixel_storei] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glPixelStorei"), NULL);
    this->m_syms[hi_sym_gl_polygon_offset] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glPolygonOffset"), NULL);
    this->m_syms[hi_sym_gl_read_pixels] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glReadPixels"), NULL);
    this->m_syms[hi_sym_gl_release_shader_compiler] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glReleaseShaderCompiler"), NULL);
    this->m_syms[hi_sym_gl_render_buffer_storage] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glRenderbufferStorage"), NULL);
    this->m_syms[hi_sym_gl_sample_coverage] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glSampleCoverage"), NULL);
    this->m_syms[hi_sym_gl_scissor] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glScissor"), NULL);
    this->m_syms[hi_sym_gl_shader_binary] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glShaderBinary"), NULL);
    this->m_syms[hi_sym_gl_shader_source] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glShaderSource"), NULL);
    this->m_syms[hi_sym_gl_stencil_func] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glStencilFunc"), NULL);
    this->m_syms[hi_sym_gl_stencil_func_separate] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glStencilFuncSeparate"), NULL);
    this->m_syms[hi_sym_gl_stencil_mask] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glStencilMask"), NULL);
    this->m_syms[hi_sym_gl_stencil_mask_separate] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glStencilMaskSeparate"), NULL);
    this->m_syms[hi_sym_gl_stencil_op] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glStencilOp"), NULL);
    this->m_syms[hi_sym_gl_stencil_op_separate] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glStencilOpSeparate"), NULL);
    this->m_syms[hi_sym_gl_tex_image_2d] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glTexImage2D"), NULL);
    this->m_syms[hi_sym_gl_tex_parameterfv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glTexParameterfv"), NULL);
    this->m_syms[hi_sym_gl_tex_parameteri] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glTexParameteri"), NULL);
    this->m_syms[hi_sym_gl_tex_parameteriv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glTexParameteriv"), NULL);
    this->m_syms[hi_sym_gl_tex_sub_image_2d] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glTexSubImage2D"), NULL);
    this->m_syms[hi_sym_gl_uniform1f] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glUniform1f"), NULL);
    this->m_syms[hi_sym_gl_uniform1fv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glUniform1fv"), NULL);
    this->m_syms[hi_sym_gl_uniform1i] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glUniform1i"), NULL);
    this->m_syms[hi_sym_gl_uniform1iv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glUniform1iv"), NULL);
    this->m_syms[hi_sym_gl_uniform2f] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glUniform2f"), NULL);
    this->m_syms[hi_sym_gl_uniform2fv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glUniform2fv"), NULL);
    this->m_syms[hi_sym_gl_uniform2i] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glUniform2i"), NULL);
    this->m_syms[hi_sym_gl_uniform3iv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glUniform2iv"), NULL);
    this->m_syms[hi_sym_gl_uniform3f] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glUniform3f"), NULL);
    this->m_syms[hi_sym_gl_uniform3fv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glUniform3fv"), NULL);
    this->m_syms[hi_sym_gl_uniform3i] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glUniform3i"), NULL);
    this->m_syms[hi_sym_gl_uniform3iv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glUniform3iv"), NULL);
    this->m_syms[hi_sym_gl_uniform4f] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glUniform4f"), NULL);
    this->m_syms[hi_sym_gl_uniform4fv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glUniform4fv"), NULL);
    this->m_syms[hi_sym_gl_uniform4i] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glUniform4i"), NULL);
    this->m_syms[hi_sym_gl_uniform4iv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glUniform4iv"), NULL);
    this->m_syms[hi_sym_gl_uniform_matrix2fv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glUniformMatrix2fv"), NULL);
    this->m_syms[hi_sym_gl_uniform_matrix3fv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glUniformMatrix3fv"), NULL);
    this->m_syms[hi_sym_gl_uniform_matrix4fv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glUniformMatrix4fv"), NULL);
    this->m_syms[hi_sym_gl_use_program] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glUseProgram"), NULL);
    this->m_syms[hi_sym_gl_validate_program] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glValidateProgram"), NULL);
    this->m_syms[hi_sym_gl_vertex_attrib1f] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glVertexAttrib1f"), NULL);
    this->m_syms[hi_sym_gl_vertex_attrib1fv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glVertexAttrib1fv"), NULL);
    this->m_syms[hi_sym_gl_vertex_attrib2f] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glVertexAttrib2f"), NULL);
    this->m_syms[hi_sym_gl_vertex_attrib2fv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glVertexAttrib2fv"), NULL);
    this->m_syms[hi_sym_gl_vertex_attrib3f] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glVertexAttrib3f"), NULL);
    this->m_syms[hi_sym_gl_vertex_attrib3fv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glVertexAttrib3fv"), NULL);
    this->m_syms[hi_sym_gl_vertex_attrib4f] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glVertexAttrib4f"), NULL);
    this->m_syms[hi_sym_gl_vertex_attrib4fv] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glVertexAttrib4fv"), NULL);
    this->m_syms[hi_sym_gl_vertex_attrib_pointer] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glVertexAttribPointer"), NULL);
    this->m_syms[hi_sym_gl_viewport] = xdl_sym(this->m_libs[hi_lib_gles], oxorany("glViewport"), NULL);

    this->m_bLoaded = true;
    return true;
}

void* CHideImports::dlopen(const char* __path, int __flags) const noexcept {
    return this->call<void*,const char*,int>(hi_sym_dlopen, __path, __flags);
}

void* CHideImports::dlsym(void* __handle, const char* __symbol) const noexcept {
    return this->call<void*,void*,const char*>(hi_sym_dlsym, __handle, __symbol);
}

int CHideImports::dladdr(void* __addr, Dl_info* __info) const noexcept {
    return this->call<int,void*,Dl_info*>(hi_sym_dladdr, __addr, __info);
}

int CHideImports::mprotect(void* __addr, size_t __size, int __prot) const noexcept {
    return this->call<int,void*,size_t,int>(hi_sym_mprotect, __addr, __size, __prot);
}

void* CHideImports::malloc(size_t __size) const noexcept {
    return this->call<void*,size_t>(hi_sym_malloc, __size);
}

void CHideImports::free(void* __mem) const noexcept {
    return this->call<void,void*>(hi_sym_free, __mem);
}

void CHideImports::abort() const noexcept {
    return this->call<void>(hi_sym_abort);
}

void CHideImports::exit(int exitcode) const noexcept {
    return this->call<void,int>(hi_sym_exit, exitcode);
}

long CHideImports::sysconf(int __name) const noexcept {
    return this->call<long,int>(hi_sym_sysconf, __name);
}

const char* CHideImports::strstr(const char* __str, const char* __substr) const noexcept {
    return this->call<const char*,const char*,const char*>(hi_sym_strstr, __str, __substr);
}

int CHideImports::strcmp(const char* __str, const char* __str2) const noexcept {
    return this->call<int,const char*,const char*>(hi_sym_strstr, __str, __str2);
}
