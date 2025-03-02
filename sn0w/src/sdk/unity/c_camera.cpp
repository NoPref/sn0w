#include "c_camera.h"
#include "../globals.hpp"
#include "../includes/il2cpp/il2cpp-api.h"

matrix4x4_t C_Camera::m_viewMatrix{};
matrix4x4_t C_Camera::m_projMatrix{};

float C_Camera::getFOV() const noexcept {
    static float(*func)(const C_Camera*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Camera"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_fieldOfView"), 0)->methodPointer);
    return func(this);
}

void C_Camera::setFOV(const float& fValue) noexcept {
    static void(*func)(const C_Camera*, float);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Camera"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("set_fieldOfView"), 1)->methodPointer);
    func(this, fValue);
}

C_Camera* C_Camera::getMain() noexcept {
    static C_Camera*(*func)();
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Camera"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_main"), 0)->methodPointer);
    return func();
}

C_Camera* C_Camera::getCurrent() noexcept {
    static C_Camera*(*func)();
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Camera"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_current"), 0)->methodPointer);
    return func();
}

matrix4x4_t C_Camera::getViewMatrix() const noexcept {
    matrix4x4_t ret{};
    static void(*func)(const C_Camera*, matrix4x4_t&);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Camera"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_worldToCameraMatrix_Injected"), 1)->methodPointer);
    func(this, ret);
    return ret;
}

matrix4x4_t C_Camera::getProjectionMatrix() const noexcept {
    matrix4x4_t ret{};
    static void(*func)(const C_Camera*, matrix4x4_t&);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Camera"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_projectionMatrix_Injected"), 1)->methodPointer);
    func(this, ret);
    return ret;
}

vec3_t C_Camera::w2s(const vec3_t& vecOrigin) noexcept {
    const matrix4x4_t vm = C_Camera::m_projMatrix * C_Camera::m_viewMatrix;

    const quaternion_t qClip {
        vecOrigin.x * vm.m00 + vecOrigin.y * vm.m01 + vecOrigin.z * vm.m02 + vm.m03, 
        vecOrigin.x * vm.m10 + vecOrigin.y * vm.m11 + vecOrigin.z * vm.m12 + vm.m13, 
        vecOrigin.x * vm.m20 + vecOrigin.y * vm.m21 + vecOrigin.z * vm.m22 + vm.m23, 
        vecOrigin.x * vm.m30 + vecOrigin.y * vm.m31 + vecOrigin.z * vm.m32 + vm.m33, 
    };

    const vec3_t vecNormalized {
        qClip.x / (qClip.w > 0 ? qClip.w : 1),
        qClip.y / (qClip.w > 0 ? qClip.w : 1),
        qClip.z / (qClip.w > 0 ? qClip.w : 1)
    };

    return vec3_t {
        (g.window.m_iWidth / 2 * vecNormalized.x) + (vecNormalized.x + g.window.m_iWidth / 2),
        -(g.window.m_iHeight / 2 * vecNormalized.y) + (vecNormalized.y + g.window.m_iHeight / 2),
        vecNormalized.z
    };
}

vec3_t C_Camera::w2s_clamped(const vec3_t& vecOrigin) noexcept {
    vec3_t ret{};
    if(g.vars.mainCamera != NULL) {
        const vec3_t vecCamera = g.vars.mainCamera->getTransform()->getPosition();
        const vec3_t vecForward = g.vars.mainCamera->getTransform()->getForward();
        const vec3_t vecDelta = vecOrigin - vecCamera;
        const float fDot = vecForward.dot(vecDelta);
        const vec3_t vecClamped = fDot <= 0 ? vecCamera + (vecDelta - (vecForward * fDot * 1.01f)) : vecOrigin;
        ret = g.vars.mainCamera->w2s(vecClamped);
    }
    return ret;
}

camera_clear_flags C_Camera::getFlags() const noexcept {
    static camera_clear_flags(*func)(const C_Camera*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Camera"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_clearFlags"), 0)->methodPointer);
    return func(this);
}

void C_Camera::setFlags(const camera_clear_flags& flags) noexcept {
    static void(*func)(C_Camera*,camera_clear_flags);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Camera"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("set_clearFlags"), 1)->methodPointer);
    func(this, flags);
}

void C_Camera::setBackgroundColor(const color_t& color) noexcept {
    static void(*func)(C_Camera*,color_t);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Camera"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("set_backgroundColor"), 1)->methodPointer);
    func(this, color);
}