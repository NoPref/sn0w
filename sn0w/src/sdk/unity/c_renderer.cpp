#include "c_renderer.h"
#include "c_material.h"
#include "../globals.hpp"
#include "../includes/il2cpp/il2cpp-api.h"

CMaterial* CRenderer::getMaterial() const noexcept {
    static CMaterial*(*func)(const CRenderer*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Renderer"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_material"), 0)->methodPointer);
    return func(this);
}

array_t<CMaterial*>* CRenderer::getMaterials() const noexcept {
    static array_t<CMaterial*>*(*func)(const CRenderer*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Renderer"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_materials"), 0)->methodPointer);
    return func(this);
}

void CRenderer::setMaterial(CMaterial* pMaterial) noexcept {
    static void(*func)(CRenderer*, CMaterial*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Renderer"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("set_material"), 1)->methodPointer);
    func(this, pMaterial);
}

void CRenderer::setMaterials(array_t<CMaterial*>* aMaterials) noexcept {
    static void(*func)(CRenderer*, array_t<CMaterial*>*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Renderer"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("set_materials"), 1)->methodPointer);
    func(this, aMaterials);
}