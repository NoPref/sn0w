#include "c_assetbundle.h"
#include "../globals.hpp"

CAssetBundle* CAssetBundleCreateRequest::getAssetBundle() noexcept {
    static CAssetBundle*(*func)(CAssetBundleCreateRequest*);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("AssetBundleCreateRequest"), oxorany("UnityEngine"), oxorany("UnityEngine.AssetBundleModule.dll")), oxorany("get_assetBundle"), 0)->methodPointer;
    return func(this);
}

CObject* CAssetBundleRequest::getAsset() noexcept {
    static CObject*(*func)(CAssetBundleRequest*);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("AssetBundleRequest"), oxorany("UnityEngine"), oxorany("UnityEngine.AssetBundleModule.dll")), oxorany("get_asset"), 0)->methodPointer;
    return func(this);
}

array_t<CObject*>* CAssetBundleRequest::getAssets() noexcept {
    static array_t<CObject*>*(*func)(CAssetBundleRequest*);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("AssetBundleRequest"), oxorany("UnityEngine"), oxorany("UnityEngine.AssetBundleModule.dll")), oxorany("get_assets"), 0)->methodPointer;
    return func(this);
}

CAssetBundleCreateRequest* CAssetBundle::loadFromFileAsync(const char* const& szPath) noexcept {
    static CAssetBundleCreateRequest*(*func)(string_t*);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("AssetBundle"), oxorany("UnityEngine"), oxorany("UnityEngine.AssetBundleModule.dll")), oxorany("LoadFromFileAsync"), 1)->methodPointer;
    return func(string_t::create(szPath));
}

CAssetBundleRequest* CAssetBundle::loadAssetAsync(const char* const& szName, type_t* type) noexcept {
    static CAssetBundleRequest*(*func)(CAssetBundle*,string_t*,type_t*);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("AssetBundle"), oxorany("UnityEngine"), oxorany("UnityEngine.AssetBundleModule.dll")), oxorany("LoadAssetAsync"), 2)->methodPointer;
    return func(this, string_t::create(szName), type);
}

void CAssetBundle::unload(const bool& unloadObjects) noexcept {
    static void(*func)(CAssetBundle*,bool);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("AssetBundle"), oxorany("UnityEngine"), oxorany("UnityEngine.AssetBundleModule.dll")), oxorany("Unload"), 1)->methodPointer;
    func(this, unloadObjects);
}