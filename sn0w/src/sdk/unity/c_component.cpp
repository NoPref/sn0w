#include "c_component.h"
#include "../globals.hpp"
#include "../includes/il2cpp/il2cpp-api.h"

CTransform* C_Component::getTransform() const noexcept {
    static CTransform*(*func)(const C_Component*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Component"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_transform"), 0)->methodPointer);
    return func(this);
}

CGameObject* C_Component::getGameObject() const noexcept {
    static CGameObject*(*func)(const C_Component*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Component"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_gameObject"), 0)->methodPointer);
    return func(this);
}

C_Component* C_Component::getComponentInChildren(type_t* type, bool bInactive) const noexcept {
    static C_Component*(*func)(const C_Component*, type_t*, bool);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Component"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("GetComponentInChildren"), 2)->methodPointer);
    return func(this, type, bInactive);
}

C_Component* C_Component::getComponentInParent(type_t* type, bool bInactive) const noexcept {
    static C_Component*(*func)(const C_Component*, type_t*, bool);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Component"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("GetComponentInParent"), 2)->methodPointer);
    return func(this, type, bInactive);
}