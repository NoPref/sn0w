#pragma once
#include "c_object.h"
#include "common/t_type.h"

class CTransform;
class CGameObject;

class C_Component : public CObject {
public:

    CTransform* getTransform() const noexcept;
    CGameObject* getGameObject() const noexcept;
    C_Component* getComponentInChildren(type_t* type, bool bInactive = false) const noexcept;
    C_Component* getComponentInParent(type_t* type, bool bInactive = false) const noexcept;
};