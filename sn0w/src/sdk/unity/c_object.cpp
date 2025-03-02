#include "c_object.h"
#include "../globals.hpp"
#include "../includes/il2cpp/il2cpp-api.h"

int CObject::getInstanceID() const noexcept {
    static int(*func)(const CObject*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Object"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("GetInstanceID"), 0)->methodPointer);
    return func(this);
}

CObject* CObject::findObjectFromID(const int32_t& id) noexcept {
    static CObject*(*func)(int32_t);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Object"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("FindObjectFromInstanceID"), 1)->methodPointer);
    return func(id);
}

array_t<CObject*>* CObject::findObjectsOfType(type_t* type) noexcept {
    static array_t<CObject*>*(*func)(type_t*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Object"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("FindObjectsOfType"), 1)->methodPointer);
    return func(type);
}

array_t<CObject*>* CObject::findObjectsByType(type_t* type) noexcept {
    static array_t<CObject*>*(*func)(type_t*,uint8_t,uint8_t);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Object"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("FindObjectsByType"), 3)->methodPointer);
    return func(type,0,0);
}

CObject* CObject::findObjectOfType(type_t* type) noexcept {
    array_t<CObject*>* pArr = CObject::findObjectsOfType(type);
    if(pArr != NULL) {
        if(pArr->isValid()) {
            return pArr->get(0);
        }
    }
    return NULL;
}

CObject* CObject::instantiate(CObject* orig, const vec3_t& vecOrigin, const quaternion_t& qRot) noexcept {
    static CObject*(*func)(CObject* original, vec3_t pos, quaternion_t rot);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Object"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("Instantiate"), 3)->methodPointer);
    return func(orig, vecOrigin, qRot);
}

CObject* CObject::instantiate(CObject* orig, const vec3_t& vecOrigin, const quaternion_t& qRot, CTransform* parent) noexcept {
    static CObject*(*func)(CObject*, vec3_t, quaternion_t, CTransform*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Object"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("Instantiate"), 4)->methodPointer);
    return func(orig, vecOrigin, qRot, parent);
}

void CObject::destroy() noexcept {
    static void(*func)(CObject*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Object"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("Destroy"), 1)->methodPointer);
    func(this);
}

void CObject::dontDestroyOnLoad() noexcept {
    static void(*func)(CObject*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Object"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("DontDestroyOnLoad"), 1)->methodPointer);
    func(this);
}

string_t* CObject::getName() const noexcept {
    static string_t*(*func)(const CObject*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Object"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_name"), 0)->methodPointer);
    return func(this);
}

void CObject::setName(string_t* u16str) noexcept {
    static void(*func)(CObject*, string_t*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Object"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("set_name"), 1)->methodPointer);
    func(this, u16str);
}

void CObject::setName(const char* const& u8str) noexcept {
    this->setName(string_t::create(u8str));
}