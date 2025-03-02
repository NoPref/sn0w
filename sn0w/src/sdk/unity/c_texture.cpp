#include "c_texture.h"
#include "../globals.hpp"

CTexture2D* CTexture2D::getWhiteTexture() noexcept {
    static CTexture2D*(*func)();
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Texture2D"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_whiteTexture"), 0)->methodPointer;
    return func();
}

void CTexture2D::ctor(CTexture2D* thiz, const int32_t& w, const int32_t& h, const texture_format& format, bool mipChain) noexcept {
    static void(*func)(CTexture2D*,int32_t,int32_t,texture_format,bool);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Texture2D"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany(".ctor"), 4)->methodPointer;
    func(thiz, w, h, format, mipChain);
}

array_t<color_t>* CTexture2D::getPixels() const noexcept {
    static array_t<color_t>*(*func)(const CTexture2D*);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Texture2D"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("GetPixels"), 0)->methodPointer;
    return func(this);
}

void CTexture2D::setPixels(const array_t<color_t>* const& pixels) noexcept {
    static void(*func)(const CTexture2D*, const array_t<color_t>*);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Texture2D"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("SetPixels"), 1)->methodPointer;
    func(this, pixels);
}

void CTexture2D::setPixel(const uint32_t& x, const uint32_t& y, const color_t& color) noexcept {
    static void(*func)(CTexture2D*, color_t);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Texture2D"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("SetPixel"), 3)->methodPointer;
    func(this, color);
}

void CTexture2D::apply() noexcept {
    static void(*func)(CTexture2D*);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Texture2D"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("Apply"), 0)->methodPointer;
    func(this);
}