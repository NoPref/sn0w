// dear imgui: Renderer Backend for modern OpenGL with shaders / programmatic pipeline
// - Desktop GL: 2.x 3.x 4.x
// - Embedded GL: ES 2.0 (WebGL 1.0), ES 3.0 (WebGL 2.0)
// This needs to be used along with a Platform Backend (e.g. GLFW, SDL, Win32, custom..)

// Implemented features:
//  [X] Renderer: User texture binding. Use 'uint32_t' OpenGL texture identifier as void*/ImTextureID. Read the FAQ about ImTextureID!
//  [x] Renderer: Desktop GL only: Support for large meshes (64k+ vertices) with 16-bit indices.

// You can use unmodified imgui_impl_* files in your project. See examples/ folder for examples of using this.
// Prefer including the entire imgui/ repository into your project (either as a copy or as a submodule), and only build the backends you need.
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

// CHANGELOG
// (minor and older changes stripped away, please see git history for details)
//  2022-11-09: OpenGL: Reverted use of g.hi->call<void,uint32_t,signed long int,signed long int,const void*>(hi_sym_gl_buffer_sub_data, ), too many corruptions issues + old issues seemingly can't be reproed with Intel drivers nowadays (revert 2021-12-15 and 2022-05-23 changes).
//  2022-10-11: Using 'nullptr' instead of 'NULL' as per our switch to C++11.
//  2022-09-27: OpenGL: Added ability to '#define IMGUI_IMPL_OPENGL_DEBUG'.
//  2022-05-23: OpenGL: Reworking 2021-12-15 "Using buffer orphaning" so it only happens on Intel GPU, seems to cause problems otherwise. (#4468, #4825, #4832, #5127).
//  2022-05-13: OpenGL: Fix state corruption on OpenGL ES 2.0 due to not preserving oxorany(0x8895) and vertex attribute states.
//  2021-12-15: OpenGL: Using buffer orphaning + g.hi->call<void,uint32_t,signed long int,signed long int,const void*>(hi_sym_gl_buffer_sub_data, ), seems to fix leaks with multi-viewports with some Intel HD drivers.
//  2021-08-23: OpenGL: Fixed ES 3.0 shader ("#version 300 es") use normal precision floats to avoid wobbly rendering at HD resolutions.
//  2021-08-19: OpenGL: Embed and use our own minimal GL loader (imgui_impl_opengl3_loader.h), removing requirement and support for third-party loader.
//  2021-06-29: Reorganized backend to pull data from a single structure to facilitate usage with multiple-contexts (all g_XXXX access changed to bd->XXXX).
//  2021-06-25: OpenGL: Use OES_vertex_array extension on Emscripten + backup/restore current state.
//  2021-06-21: OpenGL: Destroy individual vertex/fragment shader objects right after they are linked into the main shader.
//  2021-05-24: OpenGL: Access GL_CLIP_ORIGIN when "GL_ARB_clip_control" extension is detected, inside of just OpenGL 4.5 version.
//  2021-05-19: OpenGL: Replaced direct access to ImDrawCmd::TextureId with a call to ImDrawCmd::GetTexID(). (will become a requirement)
//  2021-04-06: OpenGL: Don't try to read GL_CLIP_ORIGIN unless we're OpenGL 4.5 or greater.
//  2021-02-18: OpenGL: Change blending equation to preserve alpha in output buffer.
//  2021-01-03: OpenGL: Backup, setup and restore oxorany(0x0B90) state.
//  2020-10-23: OpenGL: Backup, setup and restore GL_PRIMITIVE_RESTART state.
//  2020-10-15: OpenGL: Use glGetString(GL_VERSION) instead of g.hi->call<void,uint32_t,int32_t*>(hi_sym_gl_get_integerv, (GL_MAJOR_VERSION, ...) when the later returns zero (e.g. Desktop GL 2.x)
//  2020-09-17: OpenGL: Fix to avoid compiling/calling glBindSampler() on ES or pre 3.3 context which have the defines set by a loader.
//  2020-07-10: OpenGL: Added support for glad2 OpenGL loader.
//  2020-05-08: OpenGL: Made default GLSL version 150 (instead of 130) on OSX.
//  2020-04-21: OpenGL: Fixed handling of glClipControl(GL_UPPER_LEFT) by inverting projection matrix.
//  2020-04-12: OpenGL: Fixed context version check mistakenly testing for 4.0+ instead of 3.2+ to enable ImGuiBackendFlags_RendererHasVtxOffset.
//  2020-03-24: OpenGL: Added support for glbinding 2.x OpenGL loader.
//  2020-01-07: OpenGL: Added support for glbinding 3.x OpenGL loader.
//  2019-10-25: OpenGL: Using a combination of GL define and runtime GL version to decide whether to use glDrawElementsBaseVertex(). Fix building with pre-3.2 GL loaders.
//  2019-09-22: OpenGL: Detect default GL loader using __has_include compiler facility.
//  2019-09-16: OpenGL: Tweak initialization code to allow application calling ImGui_ImplOpenGL3_CreateFontsTexture() before the first NewFrame() call.
//  2019-05-29: OpenGL: Desktop GL only: Added support for large mesh (64K+ vertices), enable ImGuiBackendFlags_RendererHasVtxOffset flag.
//  2019-04-30: OpenGL: Added support for special ImDrawCallback_ResetRenderState callback to reset render state.
//  2019-03-29: OpenGL: Not calling glBindBuffer more than necessary in the render loop.
//  2019-03-15: OpenGL: Added a GL call + comments in ImGui_ImplOpenGL3_Init() to detect uninitialized GL function loaders early.
//  2019-03-03: OpenGL: Fix support for ES 2.0 (WebGL 1.0).
//  2019-02-20: OpenGL: Fix for OSX not supporting OpenGL 4.5, we don't try to read GL_CLIP_ORIGIN even if defined by the headers/loader.
//  2019-02-11: OpenGL: Projecting clipping rectangles correctly using draw_data->FramebufferScale to allow multi-viewports for retina display.
//  2019-02-01: OpenGL: Using GLSL 410 shaders for any version over 410 (e.g. 430, 450).
//  2018-11-30: Misc: Setting up io.BackendRendererName so it can be displayed in the About Window.
//  2018-11-13: OpenGL: Support for GL 4.5's glClipControl(GL_UPPER_LEFT) / GL_CLIP_ORIGIN.
//  2018-08-29: OpenGL: Added support for more OpenGL loaders: glew and glad, with comments indicative that any loader can be used.
//  2018-08-09: OpenGL: Default to OpenGL ES 3 on iOS and Android. GLSL version default to "#version 300 ES".
//  2018-07-30: OpenGL: Support for GLSL 300 ES and 410 core. Fixes for Emscripten compilation.
//  2018-07-10: OpenGL: Support for more GLSL versions (based on the GLSL version string). Added error output when shaders fail to compile/link.
//  2018-06-08: Misc: Extracted imgui_impl_opengl3.cpp/.h away from the old combined GLFW/SDL+OpenGL3 examples.
//  2018-06-08: OpenGL: Use draw_data->DisplayPos and draw_data->DisplaySize to setup projection matrix and clipping rectangle.
//  2018-05-25: OpenGL: Removed unnecessary backup/restore of oxorany(0x8895) since this is part of the VAO state.
//  2018-05-14: OpenGL: Making the call to glBindSampler() optional so 3.2 context won't fail if the function is a nullptr pointer.
//  2018-03-06: OpenGL: Added const char* glsl_version parameter to ImGui_ImplOpenGL3_Init() so user can override the GLSL version e.g. "#version 150".
//  2018-02-23: OpenGL: Create the VAO in the render function so the setup can more easily be used with multiple shared GL context.
//  2018-02-16: Misc: Obsoleted the io.RenderDrawListsFn callback and exposed ImGui_ImplSdlGL3_RenderDrawData() in the .h file so you can call it yourself.
//  2018-01-07: OpenGL: Changed GLSL shader version from 330 to 150.
//  2017-09-01: OpenGL: Save and restore current bound sampler. Save and restore current polygon mode.
//  2017-05-01: OpenGL: Fixed save and restore of current blend func state.
//  2017-05-01: OpenGL: Fixed save and restore of current GL_ACTIVE_TEXTURE.
//  2016-09-05: OpenGL: Fixed save and restore of current scissor rectangle.
//  2016-07-29: OpenGL: Explicitly setting GL_UNPACK_ROW_LENGTH to reduce issues because SDL changes it. (#752)

//----------------------------------------
// OpenGL    GLSL      GLSL
// version   version   string
//----------------------------------------
//  2.0       110       "#version 110"
//  2.1       120       "#version 120"
//  3.0       130       "#version 130"
//  3.1       140       "#version 140"
//  3.2       150       "#version 150"
//  3.3       330       "#version 330 core"
//  4.0       400       "#version 400 core"
//  4.1       410       "#version 410 core"
//  4.2       420       "#version 410 core"
//  4.3       430       "#version 430 core"
//  ES 2.0    100       "#version 100"      = WebGL 1.0
//  ES 3.0    300       "#version 300 es"   = WebGL 2.0
//----------------------------------------

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "../imgui.h"
#include "imgui_impl_opengl3.h"

#include "../src/globals.hpp"
#include "../oxorany/include.h"

#include <stdio.h>
#if defined(_MSC_VER) && _MSC_VER <= 1500 // MSVC 2008 or earlier
#include <stddef.h>     // intptr_t
#else
#include <stdint.h>     // intptr_t
#endif
#if defined(__APPLE__)
#include <TargetConditionals.h>
#endif

// Clang warnings with -Weverything
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wold-style-cast"     // warning: use of old-style cast
#pragma clang diagnostic ignored "-Wsign-conversion"    // warning: implicit conversion changes signedness
#endif
#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"   // warning: cast between incompatible function types
#endif

// GL includes
#if defined(IMGUI_IMPL_OPENGL_ES2)
#if (defined(__APPLE__) && (TARGET_OS_IOS || TARGET_OS_TV))
//#include <OpenGLES/ES2/gl.h>    // Use GL ES 2
#else
//#include <GLES2/gl2.h>          // Use GL ES 2
#endif
#if defined(__EMSCRIPTEN__)
#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES
#endif
//#include <GLES2/gl2ext.h>
#endif
#elif defined(IMGUI_IMPL_OPENGL_ES3)
#if (defined(__APPLE__) && (TARGET_OS_IOS || TARGET_OS_TV))
//#include <OpenGLES/ES3/gl.h>    // Use GL ES 3
#else
//#include <GLES3/gl3.h>          // Use GL ES 3
#endif
#elif !defined(IMGUI_IMPL_OPENGL_LOADER_CUSTOM)
// Modern desktop OpenGL doesn't have a standard portable header file to load OpenGL function pointers.
// Helper libraries are often used for this purpose! Here we are using our own minimal custom loader based on gl3w.
// In the rest of your app/engine, you can use another loader of your choice (gl3w, glew, glad, glbinding, glext, glLoadGen, etc.).
// If you happen to be developing a new feature for this backend (imgui_impl_opengl3.cpp):
// - You may need to regenerate imgui_impl_opengl3_loader.h to add new symbols. See https://github.com/dearimgui/gl3w_stripped
// - You can temporarily use an unstripped version. See https://github.com/dearimgui/gl3w_stripped/releases
// Changes to this backend using new APIs should be accompanied by a regenerated stripped loader version.
#define IMGL3W_IMPL
#include "imgui_impl_opengl3_loader.h"
#endif

// Vertex arrays are not supported on ES2/WebGL1 unless Emscripten which uses an extension
#ifndef IMGUI_IMPL_OPENGL_ES2
#define IMGUI_IMPL_OPENGL_USE_VERTEX_ARRAY
#elif defined(__EMSCRIPTEN__)
#define IMGUI_IMPL_OPENGL_USE_VERTEX_ARRAY
#define glBindVertexArray       glBindVertexArrayOES
#define glGenVertexArrays       glGenVertexArraysOES
#define glDeleteVertexArrays    glDeleteVertexArraysOES
#define GL_VERTEX_ARRAY_BINDING GL_VERTEX_ARRAY_BINDING_OES
#endif

// Desktop GL 2.0+ has glPolygonMode() which GL ES and WebGL don't have.
#ifdef GL_POLYGON_MODE
#define IMGUI_IMPL_HAS_POLYGON_MODE
#endif

// Desktop GL 3.2+ has glDrawElementsBaseVertex() which GL ES and WebGL don't have.
#if !defined(IMGUI_IMPL_OPENGL_ES2) && !defined(IMGUI_IMPL_OPENGL_ES3) && defined(GL_VERSION_3_2)
#define IMGUI_IMPL_OPENGL_MAY_HAVE_VTX_OFFSET
#endif

// Desktop GL 3.3+ has glBindSampler()
#if !defined(IMGUI_IMPL_OPENGL_ES2) && !defined(IMGUI_IMPL_OPENGL_ES3) && defined(GL_VERSION_3_3)
#define IMGUI_IMPL_OPENGL_MAY_HAVE_BIND_SAMPLER
#endif

// Desktop GL 3.1+ has GL_PRIMITIVE_RESTART state
#if !defined(IMGUI_IMPL_OPENGL_ES2) && !defined(IMGUI_IMPL_OPENGL_ES3) && defined(GL_VERSION_3_1)
#define IMGUI_IMPL_OPENGL_MAY_HAVE_PRIMITIVE_RESTART
#endif

// Desktop GL use extension detection
#if !defined(IMGUI_IMPL_OPENGL_ES2) && !defined(IMGUI_IMPL_OPENGL_ES3)
#define IMGUI_IMPL_OPENGL_MAY_HAVE_EXTENSIONS
#endif

// [Debugging]
//#define IMGUI_IMPL_OPENGL_DEBUG
#ifdef IMGUI_IMPL_OPENGL_DEBUG
#include <stdio.h>
#define GL_CALL(_CALL)      do { _CALL; uint32_t gl_err = glGetError(); if (gl_err != 0) fprintf(stderr, "GL error 0x%x returned from '%s'.\n", gl_err, #_CALL); } while (0)  // Call with error check
#else
#define GL_CALL(_CALL)      _CALL   // Call without error check
#endif

// OpenGL Data
struct ImGui_ImplOpenGL3_Data
{
    uint32_t          GlVersion;               // Extracted at runtime using GL_MAJOR_VERSION, GL_MINOR_VERSION queries (e.g. 320 for GL 3.2)
    char              GlslVersionString[32];   // Specified by user or detected based on compile time GL settings.
    uint32_t          FontTexture;
    uint32_t          ShaderHandle;
    int32_t           AttribLocationTex;       // Uniforms location
    int32_t           AttribLocationProjMtx;
    uint32_t          AttribLocationVtxPos;    // Vertex attributes location
    uint32_t          AttribLocationVtxUV;
    uint32_t          AttribLocationVtxColor;
    unsigned int      VboHandle, ElementsHandle;
    signed long int   VertexBufferSize;
    signed long int   IndexBufferSize;
    bool              HasClipOrigin;
    bool              UseBufferSubData;

    ImGui_ImplOpenGL3_Data() { memset((void*)this, 0, sizeof(*this)); }
};

// Backend data stored in io.BackendRendererUserData to allow support for multiple Dear ImGui contexts
// It is STRONGLY preferred that you use docking branch with multi-viewports (== single Dear ImGui context + multiple windows) instead of multiple Dear ImGui contexts.
static ImGui_ImplOpenGL3_Data* ImGui_ImplOpenGL3_GetBackendData()
{
    return ImGui::GetCurrentContext() ? (ImGui_ImplOpenGL3_Data*)ImGui::GetIO().BackendRendererUserData : nullptr;
}

// OpenGL vertex attribute state (for ES 1.0 and ES 2.0 only)
#ifndef IMGUI_IMPL_OPENGL_USE_VERTEX_ARRAY
struct ImGui_ImplOpenGL3_VtxAttribState
{
    int32_t   Enabled, Size, Type, Normalized, Stride;
    void* Ptr;

    void GetState(int32_t index)
    {
        g.hi->call<void,int32_t,int32_t,int32_t*>(hi_sym_gl_get_vertex_attribiv, index, oxorany(0x8622), &Enabled);
        g.hi->call<void,int32_t,int32_t,int32_t*>(hi_sym_gl_get_vertex_attribiv, index, oxorany(0x8623), &Size);
        g.hi->call<void,int32_t,int32_t,int32_t*>(hi_sym_gl_get_vertex_attribiv, index, oxorany(0x8625), &Type);
        g.hi->call<void,int32_t,int32_t,int32_t*>(hi_sym_gl_get_vertex_attribiv, index, oxorany(0x886A), &Normalized);
        g.hi->call<void,int32_t,int32_t,int32_t*>(hi_sym_gl_get_vertex_attribiv, index, oxorany(0x8624), &Stride);
        g.hi->call<void,uint32_t,uint32_t,void*>(hi_sym_gl_get_vertex_attrib_pointerv, index, oxorany(0x8645), &Ptr);
    }
    void SetState(int32_t index)
    {
        g.hi->call<void,int32_t,int32_t,int32_t,bool,int32_t,void*>(hi_sym_gl_vertex_attrib_pointer, index, Size, Type, (bool)Normalized, Stride, Ptr);
        if (Enabled) g.hi->call<void,uint32_t>(hi_sym_gl_enable_vertex_attrib_array, index); else g.hi->call<void,uint32_t>(hi_sym_gl_disable_vertex_attrib_array, index);
    }
};
#endif

// Functions
bool    ImGui_ImplOpenGL3_Init(const char* glsl_version)
{
    ImGuiIO& io = ImGui::GetIO();
    //IM_ASSERT(io.BackendRendererUserData == nullptr && oxorany("Already initialized a renderer backend!"));

    // Initialize our loader
#if !defined(IMGUI_IMPL_OPENGL_ES2) && !defined(IMGUI_IMPL_OPENGL_ES3) && !defined(IMGUI_IMPL_OPENGL_LOADER_CUSTOM)
    if (imgl3wInit() != 0)
    {
        //fprintf(stderr, oxorany("Failed to initialize OpenGL loader!\n"));
        return false;
    }
#endif

    // Setup backend capabilities flags
    ImGui_ImplOpenGL3_Data* bd = IM_NEW(ImGui_ImplOpenGL3_Data)();
    io.BackendRendererUserData = (void*)bd;
    io.BackendRendererName = oxorany("imgui_impl_opengl3");

    // Query for GL version (e.g. 320 for GL 3.2)
#if !defined(IMGUI_IMPL_OPENGL_ES2)
    int32_t major = 0;
    int32_t minor = 0;
    g.hi->call<void,uint32_t,int32_t*>(hi_sym_gl_get_integerv, (GL_MAJOR_VERSION, &major);
    g.hi->call<void,uint32_t,int32_t*>(hi_sym_gl_get_integerv, (GL_MINOR_VERSION, &minor);
    if (major == 0 && minor == 0)
    {
        // Query GL_VERSION in desktop GL 2.x, the string will start with "<major>.<minor>"
        const char* gl_version = (const char*)glGetString(GL_VERSION);
        sscanf(gl_version, "%d.%d", &major, &minor);
    }
    bd->GlVersion = (uint32_t)(major * 100 + minor * 10);

    bd->UseBufferSubData = false;
    /*
    // Query vendor to enable glBufferSubData kludge
#ifdef _WIN32
    if (const char* vendor = (const char*)glGetString(GL_VENDOR))
        if (strncmp(vendor, "Intel", 5) == 0)
            bd->UseBufferSubData = true;
#endif
    */
#else
    bd->GlVersion = 200; // GLES 2
#endif

#ifdef IMGUI_IMPL_OPENGL_DEBUG
    printf("GL_MAJOR_VERSION = %d\nGL_MINOR_VERSION = %d\nGL_VENDOR = '%s'\nGL_RENDERER = '%s'\n", major, minor, (const char*)glGetString(GL_VENDOR), (const char*)glGetString(GL_RENDERER)); // [DEBUG]
#endif

#ifdef IMGUI_IMPL_OPENGL_MAY_HAVE_VTX_OFFSET
    if (bd->GlVersion >= 320)
        io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;  // We can honor the ImDrawCmd::VtxOffset field, allowing for large meshes.
#endif

    // Store GLSL version string so we can refer to it later in case we recreate shaders.
    // Note: GLSL version is NOT the same as GL version. Leave this to nullptr if unsure.
    if (glsl_version == nullptr)
    {
#if defined(IMGUI_IMPL_OPENGL_ES2)
        glsl_version = "#version 100";
#elif defined(IMGUI_IMPL_OPENGL_ES3)
        glsl_version = "#version 300 es";
#elif defined(__APPLE__)
        glsl_version = "#version 150";
#else
        glsl_version = "#version 130";
#endif
    }
    IM_ASSERT((int)strlen(glsl_version) + 2 < IM_ARRAYSIZE(bd->GlslVersionString));
    strcpy(bd->GlslVersionString, glsl_version);
    strcat(bd->GlslVersionString, "\n");

    // Make an arbitrary GL call (we don't actually need the result)
    // IF YOU GET A CRASH HERE: it probably means the OpenGL function loader didn't do its job. Let us know!
    int32_t current_texture;
    g.hi->call<void,uint32_t,int32_t*>(hi_sym_gl_get_integerv, oxorany(0x8069), &current_texture);

    // Detect extensions we support
    bd->HasClipOrigin = (bd->GlVersion >= 450);
#ifdef IMGUI_IMPL_OPENGL_MAY_HAVE_EXTENSIONS
    int32_t num_extensions = 0;
    g.hi->call<void,uint32_t,int32_t*>(hi_sym_gl_get_integerv, (GL_NUM_EXTENSIONS, &num_extensions);
    for (int32_t i = 0; i < num_extensions; i++)
    {
        const char* extension = (const char*)glGetStringi(GL_EXTENSIONS, i);
        if (extension != nullptr && strcmp(extension, oxorany("GL_ARB_clip_control")) == 0)
            bd->HasClipOrigin = true;
    }
#endif

    return true;
}

void    ImGui_ImplOpenGL3_Shutdown()
{
    ImGui_ImplOpenGL3_Data* bd = ImGui_ImplOpenGL3_GetBackendData();
    //IM_ASSERT(bd != nullptr && oxorany("No renderer backend to shutdown, or already shutdown?"));
    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplOpenGL3_DestroyDeviceObjects();
    io.BackendRendererName = nullptr;
    io.BackendRendererUserData = nullptr;
    IM_DELETE(bd);
}

void    ImGui_ImplOpenGL3_NewFrame()
{
    ImGui_ImplOpenGL3_Data* bd = ImGui_ImplOpenGL3_GetBackendData();
    //IM_ASSERT(bd != nullptr && oxorany("Did you call ImGui_ImplOpenGL3_Init()?"));

    if (!bd->ShaderHandle)
        ImGui_ImplOpenGL3_CreateDeviceObjects();
}

static void ImGui_ImplOpenGL3_SetupRenderState(ImDrawData* draw_data, int fb_width, int fb_height, uint32_t vertex_array_object)
{
    ImGui_ImplOpenGL3_Data* bd = ImGui_ImplOpenGL3_GetBackendData();

    // Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled, polygon fill
    g.hi->call<void,uint32_t>(hi_sym_gl_enable, oxorany(0x0BE2));
    g.hi->call<void,uint32_t>(hi_sym_gl_blend_equation, oxorany(0x8006));
    g.hi->call<void,uint32_t,uint32_t,uint32_t,uint32_t>(hi_sym_gl_blend_func_separate, oxorany(0x0302), oxorany(0x0303), 1, oxorany(0x0303));
    g.hi->call<void,uint32_t>(hi_sym_gl_disable, oxorany(0x0B44));
    g.hi->call<void,uint32_t>(hi_sym_gl_disable, oxorany(0x0B71));
    g.hi->call<void,uint32_t>(hi_sym_gl_disable, oxorany(0x0B90));
    g.hi->call<void,uint32_t>(hi_sym_gl_enable, oxorany(0x0C11));
#ifdef IMGUI_IMPL_OPENGL_MAY_HAVE_PRIMITIVE_RESTART
    if (bd->GlVersion >= 310)
        g.hi->call<void,uint32_t>(hi_sym_gl_disable, GL_PRIMITIVE_RESTART);
#endif
#ifdef IMGUI_IMPL_HAS_POLYGON_MODE
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif

    // Support for GL 4.5 rarely used glClipControl(GL_UPPER_LEFT)
#if defined(GL_CLIP_ORIGIN)
    bool clip_origin_lower_left = true;
    if (bd->HasClipOrigin)
    {
        uint32_t current_clip_origin = 0; g.hi->call<void,uint32_t,int32_t*>(hi_sym_gl_get_integerv, (GL_CLIP_ORIGIN, (int32_t*)&current_clip_origin);
        if (current_clip_origin == GL_UPPER_LEFT)
            clip_origin_lower_left = false;
    }
#endif

    // Setup viewport, orthographic projection matrix
    // Our visible imgui space lies from draw_data->DisplayPos (top left) to draw_data->DisplayPos+data_data->DisplaySize (bottom right). DisplayPos is (0,0) for single viewport apps.
    g.hi->call<void,int32_t,int32_t,int32_t,int32_t>(hi_sym_gl_viewport, 0, 0, fb_width, fb_height);
    float L = draw_data->DisplayPos.x;
    float R = draw_data->DisplayPos.x + draw_data->DisplaySize.x;
    float T = draw_data->DisplayPos.y;
    float B = draw_data->DisplayPos.y + draw_data->DisplaySize.y;
#if defined(GL_CLIP_ORIGIN)
    if (!clip_origin_lower_left) { float tmp = T; T = B; B = tmp; } // Swap top and bottom if origin is upper left
#endif
    const float ortho_projection[4][4] =
    {
        { 2.0f/(R-L),   0.0f,         0.0f,   0.0f },
        { 0.0f,         2.0f/(T-B),   0.0f,   0.0f },
        { 0.0f,         0.0f,        -1.0f,   0.0f },
        { (R+L)/(L-R),  (T+B)/(B-T),  0.0f,   1.0f },
    };
    g.hi->call<void,uint32_t>(hi_sym_gl_use_program, bd->ShaderHandle);
    g.hi->call<void,int32_t,int32_t>(hi_sym_gl_uniform1i, bd->AttribLocationTex, 0);
    g.hi->call<void,int32_t,int32_t,bool,const float*>(hi_sym_gl_uniform_matrix4fv, bd->AttribLocationProjMtx, 1, 0, &ortho_projection[0][0]);

#ifdef IMGUI_IMPL_OPENGL_MAY_HAVE_BIND_SAMPLER
    if (bd->GlVersion >= 330)
        glBindSampler(0, 0); // We use combined texture/sampler state. Applications using GL 3.3 may set that otherwise.
#endif

    (void)vertex_array_object;
#ifdef IMGUI_IMPL_OPENGL_USE_VERTEX_ARRAY
    glBindVertexArray(vertex_array_object);
#endif

    // Bind vertex/index buffers and setup attributes for ImDrawVert
    g.hi->call<void,uint32_t,uint32_t>(hi_sym_gl_bind_buffer, oxorany(0x8892), bd->VboHandle);
    g.hi->call<void,uint32_t,uint32_t>(hi_sym_gl_bind_buffer, oxorany(0x8893), bd->ElementsHandle);
    g.hi->call<void,uint32_t>(hi_sym_gl_enable_vertex_attrib_array, bd->AttribLocationVtxPos);
    g.hi->call<void,uint32_t>(hi_sym_gl_enable_vertex_attrib_array, bd->AttribLocationVtxUV);
    g.hi->call<void,uint32_t>(hi_sym_gl_enable_vertex_attrib_array, bd->AttribLocationVtxColor);
    g.hi->call<void,uint32_t,int32_t,uint32_t,bool,int32_t,const void*>(hi_sym_gl_vertex_attrib_pointer, bd->AttribLocationVtxPos, 2, oxorany(0x1406), 0, sizeof(ImDrawVert), (void*)IM_OFFSETOF(ImDrawVert, pos));
    g.hi->call<void,uint32_t,int32_t,uint32_t,bool,int32_t,const void*>(hi_sym_gl_vertex_attrib_pointer, bd->AttribLocationVtxUV, 2, oxorany(0x1406), 0, sizeof(ImDrawVert), (void*)IM_OFFSETOF(ImDrawVert, uv));
    g.hi->call<void,uint32_t,int32_t,uint32_t,bool,int32_t,const void*>(hi_sym_gl_vertex_attrib_pointer, bd->AttribLocationVtxColor, 4, oxorany(0x1401), 1, sizeof(ImDrawVert), (void*)IM_OFFSETOF(ImDrawVert, col));
}

// OpenGL3 Render function.
// Note that this implementation is little overcomplicated because we are saving/setting up/restoring every OpenGL state explicitly.
// This is in order to be able to run within an OpenGL engine that doesn't do so.
void    ImGui_ImplOpenGL3_RenderDrawData(ImDrawData* draw_data)
{
    // Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer coordinates)
    int fb_width = (int)(draw_data->DisplaySize.x * draw_data->FramebufferScale.x);
    int fb_height = (int)(draw_data->DisplaySize.y * draw_data->FramebufferScale.y);
    if (fb_width <= 0 || fb_height <= 0)
        return;

    ImGui_ImplOpenGL3_Data* bd = ImGui_ImplOpenGL3_GetBackendData();

    // Backup GL state
    uint32_t last_active_texture; g.hi->call<void,uint32_t,int32_t*>(hi_sym_gl_get_integerv, oxorany(0x84E0), (int32_t*)&last_active_texture);
    g.hi->call<void,uint32_t>(hi_sym_gl_active_texture, oxorany(0x84C0));
    uint32_t last_program; g.hi->call<void,uint32_t,int32_t*>(hi_sym_gl_get_integerv, oxorany(0x8B8D), (int32_t*)&last_program);
    uint32_t last_texture; g.hi->call<void,uint32_t,int32_t*>(hi_sym_gl_get_integerv, oxorany(0x8069), (int32_t*)&last_texture);
#ifdef IMGUI_IMPL_OPENGL_MAY_HAVE_BIND_SAMPLER
    uint32_t last_sampler; if (bd->GlVersion >= 330) { g.hi->call<void,uint32_t,int32_t*>(hi_sym_gl_get_integerv, (GL_SAMPLER_BINDING, (int32_t*)&last_sampler); } else { last_sampler = 0; }
#endif
    uint32_t last_array_buffer; g.hi->call<void,uint32_t,int32_t*>(hi_sym_gl_get_integerv, oxorany(0x8894), (int32_t*)&last_array_buffer);
#ifndef IMGUI_IMPL_OPENGL_USE_VERTEX_ARRAY
    // This is part of VAO on OpenGL 3.0+ and OpenGL ES 3.0+.
    int32_t last_element_array_buffer; g.hi->call<void,uint32_t,int32_t*>(hi_sym_gl_get_integerv, oxorany(0x8895), &last_element_array_buffer);
    ImGui_ImplOpenGL3_VtxAttribState last_vtx_attrib_state_pos; last_vtx_attrib_state_pos.GetState(bd->AttribLocationVtxPos);
    ImGui_ImplOpenGL3_VtxAttribState last_vtx_attrib_state_uv; last_vtx_attrib_state_uv.GetState(bd->AttribLocationVtxUV);
    ImGui_ImplOpenGL3_VtxAttribState last_vtx_attrib_state_color; last_vtx_attrib_state_color.GetState(bd->AttribLocationVtxColor);
#endif
#ifdef IMGUI_IMPL_OPENGL_USE_VERTEX_ARRAY
    uint32_t last_vertex_array_object; g.hi->call<void,uint32_t,int32_t*>(hi_sym_gl_get_integerv, (GL_VERTEX_ARRAY_BINDING, (int32_t*)&last_vertex_array_object);
#endif
#ifdef IMGUI_IMPL_HAS_POLYGON_MODE
    int32_t last_polygon_mode[2]; g.hi->call<void,uint32_t,int32_t*>(hi_sym_gl_get_integerv, (GL_POLYGON_MODE, last_polygon_mode);
#endif
    int32_t last_viewport[4]; g.hi->call<void,uint32_t,int32_t*>(hi_sym_gl_get_integerv, oxorany(0x0BA2), last_viewport);
    int32_t last_scissor_box[4]; g.hi->call<void,uint32_t,int32_t*>(hi_sym_gl_get_integerv, oxorany(0x0C10), last_scissor_box);
    uint32_t last_blend_src_rgb; g.hi->call<void,uint32_t,int32_t*>(hi_sym_gl_get_integerv, oxorany(0x80C9), (int32_t*)&last_blend_src_rgb);
    uint32_t last_blend_dst_rgb; g.hi->call<void,uint32_t,int32_t*>(hi_sym_gl_get_integerv, oxorany(0x80C8), (int32_t*)&last_blend_dst_rgb);
    uint32_t last_blend_src_alpha; g.hi->call<void,uint32_t,int32_t*>(hi_sym_gl_get_integerv, oxorany(0x80CB), (int32_t*)&last_blend_src_alpha);
    uint32_t last_blend_dst_alpha; g.hi->call<void,uint32_t,int32_t*>(hi_sym_gl_get_integerv, oxorany(0x80CA), (int32_t*)&last_blend_dst_alpha);
    uint32_t last_blend_equation_rgb; g.hi->call<void,uint32_t,int32_t*>(hi_sym_gl_get_integerv, oxorany(0x8009), (int32_t*)&last_blend_equation_rgb);
    uint32_t last_blend_equation_alpha; g.hi->call<void,uint32_t,int32_t*>(hi_sym_gl_get_integerv, oxorany(0x883D), (int32_t*)&last_blend_equation_alpha);
    bool last_enable_blend = g.hi->call<bool,uint32_t>(hi_sym_gl_is_enabled, oxorany(0x0BE2));
    bool last_enable_cull_face = g.hi->call<bool,uint32_t>(hi_sym_gl_is_enabled, oxorany(0x0B44));
    bool last_enable_depth_test = g.hi->call<bool,uint32_t>(hi_sym_gl_is_enabled, oxorany(0x0B71));
    bool last_enable_stencil_test = g.hi->call<bool,uint32_t>(hi_sym_gl_is_enabled, oxorany(0x0B90));
    bool last_enable_scissor_test = g.hi->call<bool,uint32_t>(hi_sym_gl_is_enabled, oxorany(0x0C11));
#ifdef IMGUI_IMPL_OPENGL_MAY_HAVE_PRIMITIVE_RESTART
    bool last_enable_primitive_restart = (bd->GlVersion >= 310) ? g.hi->call<bool,uint32_t>(hi_sym_gl_is_enabled, GL_PRIMITIVE_RESTART) : 0;
#endif

    // Setup desired GL state
    // Recreate the VAO every time (this is to easily allow multiple GL contexts to be rendered to. VAO are not shared among GL contexts)
    // The renderer would actually work without any VAO bound, but then our VertexAttrib calls would overwrite the default one currently bound.
    uint32_t vertex_array_object = 0;
#ifdef IMGUI_IMPL_OPENGL_USE_VERTEX_ARRAY
    GL_CALL(glGenVertexArrays(1, &vertex_array_object));
#endif
    ImGui_ImplOpenGL3_SetupRenderState(draw_data, fb_width, fb_height, vertex_array_object);

    // Will project scissor/clipping rectangles into framebuffer space
    ImVec2 clip_off = draw_data->DisplayPos;         // (0,0) unless using multi-viewports
    ImVec2 clip_scale = draw_data->FramebufferScale; // (1,1) unless using retina display which are often (2,2)

    // Render command lists
    for (int n = 0; n < draw_data->CmdListsCount; n++)
    {
        const ImDrawList* cmd_list = draw_data->CmdLists[n];

        // Upload vertex/index buffers
        // - OpenGL drivers are in a very sorry state nowadays....
        //   During 2021 we attempted to switch from g.hi->call<void,uint32_t,signed long int,const void*,uint32_t>(hi_sym_gl_buffer_data, () to orphaning+g.hi->call<void,uint32_t,signed long int,signed long int,const void*>(hi_sym_gl_buffer_sub_data, ) following reports
        //   of leaks on Intel GPU when using multi-viewports on Windows.
        // - After this we kept hearing of various display corruptions issues. We started disabling on non-Intel GPU, but issues still got reported on Intel.
        // - We are now back to using exclusively g.hi->call<void,uint32_t,signed long int,const void*,uint32_t>(hi_sym_gl_buffer_data, (). So bd->UseBufferSubData IS ALWAYS FALSE in this code.
        //   We are keeping the old code path for a while in case people finding new issues may want to test the bd->UseBufferSubData path.
        // - See https://github.com/ocornut/imgui/issues/4468 and please report any corruption issues.
        const signed long int vtx_buffer_size = (signed long int)cmd_list->VtxBuffer.Size * (int)sizeof(ImDrawVert);
        const signed long int idx_buffer_size = (signed long int)cmd_list->IdxBuffer.Size * (int)sizeof(ImDrawIdx);
        if (bd->UseBufferSubData)
        {
            if (bd->VertexBufferSize < vtx_buffer_size)
            {
                bd->VertexBufferSize = vtx_buffer_size;
                g.hi->call<void,uint32_t,signed long int,const void*,uint32_t>(hi_sym_gl_buffer_data, oxorany(0x8892), bd->VertexBufferSize, 0, oxorany(0x88E0));
            }
            if (bd->IndexBufferSize < idx_buffer_size)
            {
                bd->IndexBufferSize = idx_buffer_size;
                g.hi->call<void,uint32_t,signed long int,const void*,uint32_t>(hi_sym_gl_buffer_data, oxorany(0x8893), bd->IndexBufferSize, 0, oxorany(0x88E0));
            }

            g.hi->call<void,uint32_t,signed long int,signed long int,const void*>(hi_sym_gl_buffer_sub_data, oxorany(0x8892), 0, vtx_buffer_size, (const void*)cmd_list->VtxBuffer.Data);
            g.hi->call<void,uint32_t,signed long int,signed long int,const void*>(hi_sym_gl_buffer_sub_data, oxorany(0x8893), 0, idx_buffer_size, (const void*)cmd_list->IdxBuffer.Data);
        }
        else
        {
            g.hi->call<void,uint32_t,signed long int,const void*,uint32_t>(hi_sym_gl_buffer_data, oxorany(0x8892), vtx_buffer_size, (const void*)cmd_list->VtxBuffer.Data, oxorany(0x88E0));
            g.hi->call<void,uint32_t,signed long int,const void*,uint32_t>(hi_sym_gl_buffer_data, oxorany(0x8893), idx_buffer_size, (const void*)cmd_list->IdxBuffer.Data, oxorany(0x88E0));
        }

        for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
        {
            const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
            if (pcmd->UserCallback != nullptr)
            {
                // User callback, registered via ImDrawList::AddCallback()
                // (ImDrawCallback_ResetRenderState is a special callback value used by the user to request the renderer to reset render state.)
                if (pcmd->UserCallback == ImDrawCallback_ResetRenderState)
                    ImGui_ImplOpenGL3_SetupRenderState(draw_data, fb_width, fb_height, vertex_array_object);
                else
                    pcmd->UserCallback(cmd_list, pcmd);
            }
            else
            {
                // Project scissor/clipping rectangles into framebuffer space
                ImVec2 clip_min((pcmd->ClipRect.x - clip_off.x) * clip_scale.x, (pcmd->ClipRect.y - clip_off.y) * clip_scale.y);
                ImVec2 clip_max((pcmd->ClipRect.z - clip_off.x) * clip_scale.x, (pcmd->ClipRect.w - clip_off.y) * clip_scale.y);
                if (clip_max.x <= clip_min.x || clip_max.y <= clip_min.y)
                    continue;

                // Apply scissor/clipping rectangle (Y is inverted in OpenGL)
                g.hi->call<void,int32_t,int32_t,int32_t,int32_t>(hi_sym_gl_scissor, (int)clip_min.x, (int)((float)fb_height - clip_max.y), (int)(clip_max.x - clip_min.x), (int)(clip_max.y - clip_min.y));

                // Bind texture, Draw
                g.hi->call<void,uint32_t,uint32_t>(hi_sym_gl_bind_texture, oxorany(0x0DE1), (uint32_t)(intptr_t)pcmd->GetTexID());
#ifdef IMGUI_IMPL_OPENGL_MAY_HAVE_VTX_OFFSET
                if (bd->GlVersion >= 320)
                    GL_CALL(glDrawElementsBaseVertex(oxorany(0x004), (GLsizei)pcmd->ElemCount, sizeof(ImDrawIdx) == 2 ? oxorany(0x1403) : oxorany(0x1405), (void*)(intptr_t)(pcmd->IdxOffset * sizeof(ImDrawIdx)), (int32_t)pcmd->VtxOffset));
                else
#endif
                g.hi->call<void,uint32_t,int32_t,uint32_t,const void*>(hi_sym_gl_draw_elements, oxorany(0x004), pcmd->ElemCount, sizeof(ImDrawIdx) == 2 ? oxorany(0x1403) : oxorany(0x1405), (void*)(intptr_t)(pcmd->IdxOffset * sizeof(ImDrawIdx)));
            }
        }
    }

    // Destroy the temporary VAO
#ifdef IMGUI_IMPL_OPENGL_USE_VERTEX_ARRAY
    GL_CALL(glDeleteVertexArrays(1, &vertex_array_object));
#endif

    // Restore modified GL state
    g.hi->call<void,uint32_t>(hi_sym_gl_use_program, last_program);
    g.hi->call<void,uint32_t,uint32_t>(hi_sym_gl_bind_texture, oxorany(0x0DE1), last_texture);
#ifdef IMGUI_IMPL_OPENGL_MAY_HAVE_BIND_SAMPLER
    if (bd->GlVersion >= 330)
        glBindSampler(0, last_sampler);
#endif
    g.hi->call<void,uint32_t>(hi_sym_gl_active_texture, last_active_texture);
#ifdef IMGUI_IMPL_OPENGL_USE_VERTEX_ARRAY
    glBindVertexArray(last_vertex_array_object);
#endif
    g.hi->call<void,uint32_t,uint32_t>(hi_sym_gl_bind_buffer, oxorany(0x8892), last_array_buffer);
#ifndef IMGUI_IMPL_OPENGL_USE_VERTEX_ARRAY
    g.hi->call<void,uint32_t,uint32_t>(hi_sym_gl_bind_buffer, oxorany(0x8893), last_element_array_buffer);
    last_vtx_attrib_state_pos.SetState(bd->AttribLocationVtxPos);
    last_vtx_attrib_state_uv.SetState(bd->AttribLocationVtxUV);
    last_vtx_attrib_state_color.SetState(bd->AttribLocationVtxColor);
#endif
    g.hi->call<void,uint32_t,uint32_t>(hi_sym_gl_blend_equation_separate, last_blend_equation_rgb, last_blend_equation_alpha);
    g.hi->call<void,uint32_t,uint32_t,uint32_t,uint32_t>(hi_sym_gl_blend_func_separate, last_blend_src_rgb, last_blend_dst_rgb, last_blend_src_alpha, last_blend_dst_alpha);
    if (last_enable_blend) g.hi->call<void,uint32_t>(hi_sym_gl_enable, oxorany(0x0BE2)); else g.hi->call<void,uint32_t>(hi_sym_gl_disable, oxorany(0x0BE2));
    if (last_enable_cull_face) g.hi->call<void,uint32_t>(hi_sym_gl_enable, oxorany(0x0B44)); else g.hi->call<void,uint32_t>(hi_sym_gl_disable, oxorany(0x0B44));
    if (last_enable_depth_test) g.hi->call<void,uint32_t>(hi_sym_gl_enable, oxorany(0x0B71)); else g.hi->call<void,uint32_t>(hi_sym_gl_disable, oxorany(0x0B71));
    if (last_enable_stencil_test) g.hi->call<void,uint32_t>(hi_sym_gl_enable, oxorany(0x0B90)); else g.hi->call<void,uint32_t>(hi_sym_gl_disable, oxorany(0x0B90));
    if (last_enable_scissor_test) g.hi->call<void,uint32_t>(hi_sym_gl_enable, oxorany(0x0C11)); else g.hi->call<void,uint32_t>(hi_sym_gl_disable, oxorany(0x0C11));
#ifdef IMGUI_IMPL_OPENGL_MAY_HAVE_PRIMITIVE_RESTART
    if (bd->GlVersion >= 310) { if (last_enable_primitive_restart) g.hi->call<void,uint32_t>(hi_sym_gl_enable, (GL_PRIMITIVE_RESTART); else g.hi->call<void,uint32_t>(hi_sym_gl_disable, GL_PRIMITIVE_RESTART); }
#endif

#ifdef IMGUI_IMPL_HAS_POLYGON_MODE
    glPolygonMode(GL_FRONT_AND_BACK, (uint32_t)last_polygon_mode[0]);
#endif
    g.hi->call<void,int32_t,int32_t,int32_t,int32_t>(hi_sym_gl_viewport, last_viewport[0], last_viewport[1], last_viewport[2], last_viewport[3]);
    g.hi->call<void,int32_t,int32_t,int32_t,int32_t>(hi_sym_gl_scissor, last_scissor_box[0], last_scissor_box[1], last_scissor_box[2], last_scissor_box[3]);
    (void)bd; // Not all compilation paths use this
}

bool ImGui_ImplOpenGL3_CreateFontsTexture()
{
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplOpenGL3_Data* bd = ImGui_ImplOpenGL3_GetBackendData();

    // Build texture atlas
    unsigned char* pixels;
    int width, height;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);   // Load as RGBA 32-bit (75% of the memory is wasted, but default font is so small) because it is more likely to be compatible with user's existing shaders. If your ImTextureId represent a higher-level concept than just a GL texture id, consider calling GetTexDataAsAlpha8() instead to save on GPU memory.

    // Upload texture to graphics system
    // (Bilinear sampling is required by default. Set 'io.Fonts->Flags |= ImFontAtlasFlags_NoBakedLines' or 'style.AntiAliasedLinesUseTex = false' to allow point/nearest sampling)
    int32_t last_texture;
    g.hi->call<void,uint32_t,int32_t*>(hi_sym_gl_get_integerv, oxorany(0x8069), &last_texture);
    g.hi->call<void,int32_t,uint32_t*>(hi_sym_gl_gen_textures, 1, &bd->FontTexture);
    g.hi->call<void,uint32_t,uint32_t>(hi_sym_gl_bind_texture, oxorany(0x0DE1), bd->FontTexture);
    g.hi->call<void,uint32_t,uint32_t,int32_t>(hi_sym_gl_tex_parameteri, oxorany(0x0DE1), oxorany(0x2801), oxorany(0x2601));
    g.hi->call<void,uint32_t,uint32_t,int32_t>(hi_sym_gl_tex_parameteri, oxorany(0x0DE1), oxorany(0x2800), oxorany(0x2601));
#ifdef GL_UNPACK_ROW_LENGTH // Not on WebGL/ES
    GL_CALL(glPixelStorei(GL_UNPACK_ROW_LENGTH, 0));
#endif
    g.hi->call<void,uint32_t,int32_t,int32_t,int32_t,int32_t,int32_t,uint32_t,uint32_t,const void*>(hi_sym_gl_tex_image_2d, oxorany(0x0DE1), 0, oxorany(0x1908), width, height, 0, oxorany(0x1908), oxorany(0x1401), pixels);

    // Store our identifier
    io.Fonts->SetTexID((ImTextureID)(intptr_t)bd->FontTexture);

    // Restore state
    g.hi->call<void,uint32_t,uint32_t>(hi_sym_gl_bind_texture, oxorany(0x0DE1), last_texture);

    return true;
}

void ImGui_ImplOpenGL3_DestroyFontsTexture()
{
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplOpenGL3_Data* bd = ImGui_ImplOpenGL3_GetBackendData();
    if (bd->FontTexture)
    {
        g.hi->call<void,int32_t,uint32_t*>(hi_sym_gl_delete_textures, 1, &bd->FontTexture);
        io.Fonts->SetTexID(0);
        bd->FontTexture = 0;
    }
}

// If you get an error please report on github. You may try different GL context version or GLSL version. See GL<>GLSL version table at the top of this file.
static bool CheckShader(uint32_t handle, const char* desc)
{
    ImGui_ImplOpenGL3_Data* bd = ImGui_ImplOpenGL3_GetBackendData();
    int32_t status = 0, log_length = 0;
    g.hi->call<void,uint32_t,uint32_t,int32_t*>(hi_sym_gl_get_shaderiv, handle, oxorany(0x8B81), &status);
    g.hi->call<void,uint32_t,uint32_t,int32_t*>(hi_sym_gl_get_shaderiv, handle, oxorany(0x8B84), &log_length);
    return status == true;
}

// If you get an error please report on GitHub. You may try different GL context version or GLSL version.
static bool CheckProgram(uint32_t handle, const char* desc)
{
    ImGui_ImplOpenGL3_Data* bd = ImGui_ImplOpenGL3_GetBackendData();
    int32_t status = 0, log_length = 0;
    g.hi->call<void,uint32_t,uint32_t,int32_t*>(hi_sym_gl_get_programiv, handle, oxorany(0x8B82), &status);
    g.hi->call<void,uint32_t,uint32_t,int32_t*>(hi_sym_gl_get_programiv, handle, oxorany(0x8B84), &log_length);
    //if ((bool)status == 0)
        //fprintf(stderr, "ERROR: ImGui_ImplOpenGL3_CreateDeviceObjects: failed to link %s! With GLSL %s\n", desc, bd->GlslVersionString);
    return status == true;
}

bool    ImGui_ImplOpenGL3_CreateDeviceObjects()
{
    ImGui_ImplOpenGL3_Data* bd = ImGui_ImplOpenGL3_GetBackendData();

    // Backup GL state
    int32_t last_texture, last_array_buffer;
    g.hi->call<void,uint32_t,int32_t*>(hi_sym_gl_get_integerv, oxorany(0x8069), &last_texture);
    g.hi->call<void,uint32_t,int32_t*>(hi_sym_gl_get_integerv, oxorany(0x8894), &last_array_buffer);
#ifdef IMGUI_IMPL_OPENGL_USE_VERTEX_ARRAY
    int32_t last_vertex_array;
    g.hi->call<void,uint32_t,int32_t*>(hi_sym_gl_get_integerv, (GL_VERTEX_ARRAY_BINDING, &last_vertex_array);
#endif

    // Parse GLSL version string
    int glsl_version = 130;
    sscanf(bd->GlslVersionString, "#version %d", &glsl_version);

    const char* vertex_shader_glsl_120 =
        "uniform mat4 ProjMtx;\n"
        "attribute vec2 Position;\n"
        "attribute vec2 UV;\n"
        "attribute vec4 Color;\n"
        "varying vec2 Frag_UV;\n"
        "varying vec4 Frag_Color;\n"
        "void main()\n"
        "{\n"
        "    Frag_UV = UV;\n"
        "    Frag_Color = Color;\n"
        "    gl_Position = ProjMtx * vec4(Position.xy,0,1);\n"
        "}\n";

    const char* vertex_shader_glsl_130 =
        "uniform mat4 ProjMtx;\n"
        "in vec2 Position;\n"
        "in vec2 UV;\n"
        "in vec4 Color;\n"
        "out vec2 Frag_UV;\n"
        "out vec4 Frag_Color;\n"
        "void main()\n"
        "{\n"
        "    Frag_UV = UV;\n"
        "    Frag_Color = Color;\n"
        "    gl_Position = ProjMtx * vec4(Position.xy,0,1);\n"
        "}\n";

    const char* vertex_shader_glsl_300_es =
        "precision highp float;\n"
        "layout (location = 0) in vec2 Position;\n"
        "layout (location = 1) in vec2 UV;\n"
        "layout (location = 2) in vec4 Color;\n"
        "uniform mat4 ProjMtx;\n"
        "out vec2 Frag_UV;\n"
        "out vec4 Frag_Color;\n"
        "void main()\n"
        "{\n"
        "    Frag_UV = UV;\n"
        "    Frag_Color = Color;\n"
        "    gl_Position = ProjMtx * vec4(Position.xy,0,1);\n"
        "}\n";

    const char* vertex_shader_glsl_410_core =
        "layout (location = 0) in vec2 Position;\n"
        "layout (location = 1) in vec2 UV;\n"
        "layout (location = 2) in vec4 Color;\n"
        "uniform mat4 ProjMtx;\n"
        "out vec2 Frag_UV;\n"
        "out vec4 Frag_Color;\n"
        "void main()\n"
        "{\n"
        "    Frag_UV = UV;\n"
        "    Frag_Color = Color;\n"
        "    gl_Position = ProjMtx * vec4(Position.xy,0,1);\n"
        "}\n";

    const char* fragment_shader_glsl_120 =
        "#ifdef GL_ES\n"
        "    precision mediump float;\n"
        "#endif\n"
        "uniform sampler2D Texture;\n"
        "varying vec2 Frag_UV;\n"
        "varying vec4 Frag_Color;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = Frag_Color * texture2D(Texture, Frag_UV.st);\n"
        "}\n";

    const char* fragment_shader_glsl_130 =
        "uniform sampler2D Texture;\n"
        "in vec2 Frag_UV;\n"
        "in vec4 Frag_Color;\n"
        "out vec4 Out_Color;\n"
        "void main()\n"
        "{\n"
        "    Out_Color = Frag_Color * texture(Texture, Frag_UV.st);\n"
        "}\n";

    const char* fragment_shader_glsl_300_es =
        "precision mediump float;\n"
        "uniform sampler2D Texture;\n"
        "in vec2 Frag_UV;\n"
        "in vec4 Frag_Color;\n"
        "layout (location = 0) out vec4 Out_Color;\n"
        "void main()\n"
        "{\n"
        "    Out_Color = Frag_Color * texture(Texture, Frag_UV.st);\n"
        "}\n";

    const char* fragment_shader_glsl_410_core =
        "in vec2 Frag_UV;\n"
        "in vec4 Frag_Color;\n"
        "uniform sampler2D Texture;\n"
        "layout (location = 0) out vec4 Out_Color;\n"
        "void main()\n"
        "{\n"
        "    Out_Color = Frag_Color * texture(Texture, Frag_UV.st);\n"
        "}\n";

    // Select shaders matching our GLSL versions
    const char* vertex_shader = nullptr;
    const char* fragment_shader = nullptr;
    if (glsl_version < 130)
    {
        vertex_shader = vertex_shader_glsl_120;
        fragment_shader = fragment_shader_glsl_120;
    }
    else if (glsl_version >= 410)
    {
        vertex_shader = vertex_shader_glsl_410_core;
        fragment_shader = fragment_shader_glsl_410_core;
    }
    else if (glsl_version == 300)
    {
        vertex_shader = vertex_shader_glsl_300_es;
        fragment_shader = fragment_shader_glsl_300_es;
    }
    else
    {
        vertex_shader = vertex_shader_glsl_130;
        fragment_shader = fragment_shader_glsl_130;
    }

    // Create shaders
    const char* vertex_shader_with_version[2] = { bd->GlslVersionString, vertex_shader };
    uint32_t vert_handle = g.hi->call<uint32_t,uint32_t>(hi_sym_gl_create_shader, oxorany(0x8B31));
    g.hi->call<void,uint32_t,int32_t,const char**, const int32_t*>(hi_sym_gl_shader_source, vert_handle, 2, vertex_shader_with_version, NULL);
    g.hi->call<void,uint32_t>(hi_sym_gl_compile_shader, vert_handle);
    CheckShader(vert_handle, "vertex shader");

    const char* fragment_shader_with_version[2] = { bd->GlslVersionString, fragment_shader };
    uint32_t frag_handle = g.hi->call<uint32_t,uint32_t>(hi_sym_gl_create_shader, oxorany(0x8B30));
    g.hi->call<void,uint32_t,int32_t,const char**, const int32_t*>(hi_sym_gl_shader_source, frag_handle, 2, fragment_shader_with_version, NULL);
    g.hi->call<void,uint32_t>(hi_sym_gl_compile_shader, frag_handle);
    CheckShader(frag_handle, "fragment shader");

    // Link
    bd->ShaderHandle = g.hi->call<uint32_t>(hi_sym_gl_create_program);
    g.hi->call<void,uint32_t,uint32_t>(hi_sym_gl_attach_shader, bd->ShaderHandle, vert_handle);
    g.hi->call<void,uint32_t,uint32_t>(hi_sym_gl_attach_shader, bd->ShaderHandle, frag_handle);
    g.hi->call<void,uint32_t>(hi_sym_gl_link_program, bd->ShaderHandle);
    CheckProgram(bd->ShaderHandle, "shader program");

    g.hi->call<void,uint32_t,uint32_t>(hi_sym_gl_detach_shader, bd->ShaderHandle, vert_handle);
    g.hi->call<void,uint32_t,uint32_t>(hi_sym_gl_detach_shader, bd->ShaderHandle, frag_handle);
    g.hi->call<void,uint32_t>(hi_sym_gl_delete_shader, vert_handle);
    g.hi->call<void,uint32_t>(hi_sym_gl_delete_shader, frag_handle);

    bd->AttribLocationTex = g.hi->call<int32_t,uint32_t,const char*>(hi_sym_gl_get_uniform_location, bd->ShaderHandle, "Texture");
    bd->AttribLocationProjMtx = g.hi->call<int32_t,uint32_t,const char*>(hi_sym_gl_get_uniform_location, bd->ShaderHandle, "ProjMtx");
    bd->AttribLocationVtxPos = (uint32_t)g.hi->call<int32_t,uint32_t,const char*>(hi_sym_gl_get_attrib_location, bd->ShaderHandle, "Position");
    bd->AttribLocationVtxUV = (uint32_t)g.hi->call<int32_t,uint32_t,const char*>(hi_sym_gl_get_attrib_location, bd->ShaderHandle, "UV");
    bd->AttribLocationVtxColor = (uint32_t)g.hi->call<int32_t,uint32_t,const char*>(hi_sym_gl_get_attrib_location, bd->ShaderHandle, "Color");

    // Create buffers
    g.hi->call<void,int32_t,uint32_t*>(hi_sym_gl_gen_buffers, 1, &bd->VboHandle);
    g.hi->call<void,int32_t,uint32_t*>(hi_sym_gl_gen_buffers, 1, &bd->ElementsHandle);

    ImGui_ImplOpenGL3_CreateFontsTexture();

    // Restore modified GL state
    g.hi->call<void,uint32_t,uint32_t>(hi_sym_gl_bind_texture, oxorany(0x0DE1), last_texture);
    g.hi->call<void,uint32_t,uint32_t>(hi_sym_gl_bind_buffer, oxorany(0x8892), last_array_buffer);
#ifdef IMGUI_IMPL_OPENGL_USE_VERTEX_ARRAY
    glBindVertexArray(last_vertex_array);
#endif

    return true;
}

void    ImGui_ImplOpenGL3_DestroyDeviceObjects()
{
    ImGui_ImplOpenGL3_Data* bd = ImGui_ImplOpenGL3_GetBackendData();
    if (bd->VboHandle)      { g.hi->call<void,int32_t,uint32_t*>(hi_sym_gl_delete_buffers, 1, &bd->VboHandle); bd->VboHandle = 0; }
    if (bd->ElementsHandle) { g.hi->call<void,int32_t,uint32_t*>(hi_sym_gl_delete_buffers, 1, &bd->ElementsHandle); bd->ElementsHandle = 0; }
    if (bd->ShaderHandle)   { g.hi->call<void,uint32_t>(hi_sym_gl_delete_program, bd->ShaderHandle); bd->ShaderHandle = 0; }
    ImGui_ImplOpenGL3_DestroyFontsTexture();
}

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
