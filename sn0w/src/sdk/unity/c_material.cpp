#include "c_material.h"
#include "../globals.hpp"
#include "../includes/il2cpp/il2cpp-api.h"

void CMaterial::create(CMaterial* thiz, CShader* shader) noexcept {
    static void(*func)(CMaterial*,CShader*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Material"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("CreateWithShader"), 2)->methodPointer);
    func(thiz, shader);
}

void CMaterial::create(CMaterial* thiz, CMaterial* material) noexcept {
    static void(*func)(CMaterial*,CMaterial*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Material"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("CreateWithMaterial"), 2)->methodPointer);
    func(thiz, material);
}

CShader* CMaterial::getShader() const noexcept {
    static CShader*(*func)(const CMaterial*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Material"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_shader"), 0)->methodPointer);
    return func(this);
}

void CMaterial::setShader(CShader* pShader) noexcept {
    static void(*func)(CMaterial*, CShader*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Material"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("set_shader"), 1)->methodPointer);
    func(this, pShader);
}

void* CMaterial::getMainTexture() const noexcept {
    static void*(*func)(const CMaterial*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Material"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_mainTexture"), 0)->methodPointer);
    return func(this);
}

void CMaterial::setMainTexture(void* texture) noexcept {
    static void(*func)(CMaterial*, void*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Material"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("set_mainTexture"), 1)->methodPointer);
    func(this, texture);
}

color_t CMaterial::getColor(const char* szProperty) const noexcept {
    static color_t(*func)(const CMaterial*, string_t*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Material"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("GetColor"), 1)->methodPointer);
    return func(this, string_t::create(szProperty));
}

void CMaterial::setColor(const color_t& color, const char* szProperty) noexcept {
    static void(*func)(CMaterial*, string_t*, color_t);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Material"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("SetColor"), 2)->methodPointer);
    func(this, string_t::create(szProperty), color);
}

float CMaterial::getFloat(const char* const& szProperty) const noexcept {
    static float(*func)(const CMaterial*, string_t*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Material"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("GetFloat"), 1)->methodPointer);
    return func(this, string_t::create(szProperty));
}

void CMaterial::setFloat(const float& fValue, const char* const& szProperty) noexcept {
    static void(*func)(CMaterial*, string_t*, float);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Material"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("SetFloat"), 2)->methodPointer);
    func(this, string_t::create(szProperty), fValue);
}

CTexture* CMaterial::getTexture(const char* const& szTexture) const noexcept {
    static CTexture*(*func)(const CMaterial*, string_t*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Material"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("GetTexture"), 1)->methodPointer);
    return func(this, string_t::create(szTexture));
}

void CMaterial::setTexture(CTexture* texture, const char* const& szTexture) noexcept {
    static void(*func)(CMaterial*, string_t*, CTexture*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Material"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("SetTexture"), 2)->methodPointer);
    func(this, string_t::create(szTexture), texture);
}