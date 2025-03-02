#pragma once
#include "c_component.h"

class CMaterial;

class CRenderer : public C_Component {
public:
    CMaterial* getMaterial() const noexcept;
    array_t<CMaterial*>* getMaterials() const noexcept;
    void setMaterial(CMaterial* pMaterial) noexcept;
    void setMaterials(array_t<CMaterial*>* aMaterials) noexcept;
};