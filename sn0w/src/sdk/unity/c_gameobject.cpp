#include "c_gameobject.h"
#include "../globals.hpp"
#include "../includes/il2cpp/il2cpp-api.h"

void CGameObject::create(const char* const& szName) noexcept {
    static void(*func)(const CGameObject*, string_t*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("GameObject"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("Internal_CreateGameObject"), 2)->methodPointer);
    return func(this, string_t::create(szName));
}

CTransform* CGameObject::getTransform() const noexcept {
    static CTransform*(*func)(const CGameObject*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("GameObject"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_transform"), 0)->methodPointer);
    return func(this);
}

std::string CGameObject::getTag() const noexcept {
    static string_t*(*func)(const CGameObject*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("GameObject"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_tag"), 0)->methodPointer);
    return std::move(func(this)->toUTF8());
}

bool CGameObject::compareTag(const char* const& szTag) const noexcept {
    return !strcmp(szTag, this->getTag().c_str());
}

bool CGameObject::getIsActive() const noexcept {
    static bool (*func)(const CGameObject*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("GameObject"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_activeSelf"), 0)->methodPointer);
    return func(this);
}

void CGameObject::setActive(const bool& bValue) const noexcept {
    static void (*func)(const CGameObject*, bool);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("GameObject"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("SetActive"), 1)->methodPointer);
    func(this, bValue);
}

int CGameObject::getLayer() const noexcept {
    static int(*func)(const CGameObject*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("GameObject"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_layer"), 0)->methodPointer);
    return func(this);
}

C_Component* CGameObject::addComponent(void* type) noexcept {
    static C_Component*(*func)(CGameObject*, void*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("GameObject"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("AddComponent"), 1)->methodPointer);
    return func(this, type);
}