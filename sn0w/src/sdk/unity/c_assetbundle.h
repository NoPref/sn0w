#pragma once
#include "common/t_type.h"
#include "common/t_array.h"
#include "c_object.h"

class CAssetBundle;

class CAssetBundleCreateRequest {
public:
    CAssetBundle* getAssetBundle() noexcept;
};

class CAssetBundleRequest {
public:
    CObject* getAsset() noexcept;
    array_t<CObject*>* getAssets() noexcept;
};

class CAssetBundle : public CObject {
public:
    static CAssetBundleCreateRequest* loadFromFileAsync(const char* const& szPath) noexcept;
    CAssetBundleRequest* loadAssetAsync(const char* const& szName, type_t* type) noexcept;
    void unload(const bool& unloadObjects) noexcept;
};