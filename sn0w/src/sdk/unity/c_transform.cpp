#include "c_transform.h"
#include "../globals.hpp"
#include "../includes/il2cpp/il2cpp-api.h"

vec3_t CTransform::getPosition() const noexcept {
    vec3_t ret{};
    static void(*func)(const CTransform*, vec3_t&);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Transform"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_position_Injected"), 1)->methodPointer);
    func(this, ret);
    return ret;
}

void CTransform::setPosition(const vec3_t& vecOrigin) noexcept {
    static void(*func)(CTransform*, vec3_t*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Transform"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("set_position_Injected"), 1)->methodPointer);
    func(this, const_cast<vec3_t*>(&vecOrigin));
}

vec3_t CTransform::getLocalPosition() const noexcept {
    vec3_t ret{};
    static void(*func)(const CTransform*, vec3_t&);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Transform"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_localPosition_Injected"), 1)->methodPointer);
    func(this, ret);
    return ret;
}

void CTransform::setLocalPosition(const vec3_t& vecOrigin) noexcept {
    static void(*func)(CTransform*, vec3_t*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Transform"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("set_localPosition_Injected"), 1)->methodPointer); 
    func(this, const_cast<vec3_t*>(&vecOrigin));
}

euler_angles_t CTransform::getEulerAngles() const noexcept {
    static euler_angles_t(*func)(const CTransform*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Transform"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_eulerAngles"), 0)->methodPointer); 
    return func(this);
}

void CTransform::setEulerAngles(const euler_angles_t& ang) noexcept {
    static void(*func)(CTransform*, euler_angles_t);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Transform"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("set_eulerAngles"), 1)->methodPointer); 
    func(this, ang);
}

euler_angles_t CTransform::getLocalEulerAngles() const noexcept {
    static euler_angles_t(*func)(const CTransform*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Transform"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_localEulerAngles"), 0)->methodPointer); 
    return func(this);
}

void CTransform::setLocalEulerAngles(const euler_angles_t& ang) noexcept {
    static void(*func)(CTransform*, euler_angles_t);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Transform"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("set_localEulerAngles"), 1)->methodPointer); 
    func(this, ang);
}

vec3_t CTransform::getRight() const noexcept {
    static vec3_t(*func)(const CTransform*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Transform"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_right"), 0)->methodPointer);
    return func(this);
}

vec3_t CTransform::getUp() const noexcept {
    static vec3_t(*func)(const CTransform*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Transform"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_up"), 0)->methodPointer);
    return func(this);
}

vec3_t CTransform::getForward() const noexcept {
    static vec3_t(*func)(const CTransform*);
    if(func == NULL) 
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Transform"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_forward"), 0)->methodPointer);
    return func(this);
}

quaternion_t CTransform::getRotation() const noexcept {
    quaternion_t ret{};
    static void(*func)(const CTransform*, quaternion_t&);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Transform"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_rotation_Injected"), 1)->methodPointer);
    func(this, ret);
    return ret;
}

void CTransform::setRotation(const quaternion_t& qRotation) noexcept {
    static void(*func)(CTransform*, quaternion_t*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Transform"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("set_rotation_Injected"), 1)->methodPointer);
    func(this, const_cast<quaternion_t*>(&qRotation));
}

quaternion_t CTransform::getLocalRotation() const noexcept {
    quaternion_t ret{};
    static void(*func)(const CTransform*, quaternion_t&);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Transform"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_localRotation_Injected"), 1)->methodPointer);
    func(this, ret);
    return ret;
}

void CTransform::setLocalRotation(const quaternion_t& qRotation) noexcept {
    static void(*func)(CTransform*, quaternion_t*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Transform"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("set_localRotation_Injected"), 1)->methodPointer);
    func(this, const_cast<quaternion_t*>(&qRotation));
}

vec3_t CTransform::getLocalScale() const noexcept {
    vec3_t ret{};
    static void(*func)(const CTransform*, vec3_t&);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Transform"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_localScale_Injected"), 1)->methodPointer);
    func(this, ret);
    return ret;
}

void CTransform::setLocalScale(const vec3_t& vecScale) noexcept {
    static void(*func)(CTransform*, vec3_t*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Transform"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("set_localScale_Injected"), 1)->methodPointer);
    func(this, const_cast<vec3_t*>(&vecScale));
}

vec3_t CTransform::getLossyScale() const noexcept {
    vec3_t ret{};
    static void(*func)(const CTransform*, vec3_t&);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Transform"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_lossyScale_Injected"), 1)->methodPointer);
    func(this, ret);
    return ret;
}

CTransform* CTransform::getParent() const noexcept {
    static CTransform*(*func)(const CTransform*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Transform"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("GetParent"), 0)->methodPointer);
    return func(this);
}

void CTransform::setParent(CTransform* parent) noexcept {
    static void(*func)(CTransform*, CTransform*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Transform"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("SetParent"), 1)->methodPointer);
    func(this, parent);
}

void CTransform::setParent(CTransform* parent, bool bWorldPosStays) noexcept {
    static void(*func)(CTransform*, CTransform*, bool);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Transform"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("SetParent"), 2)->methodPointer);
    func(this, parent, bWorldPosStays);
}