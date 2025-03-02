#pragma once
#include <string>
#include "c_object.h"

class CTransform;
class C_Component;

class CGameObject : public CObject {
public:
    void create(const char* const& szName) noexcept;
    CTransform* getTransform() const noexcept;
    std::string getTag() const noexcept;
    bool compareTag(const char* const& szTag) const noexcept;
    bool getIsActive() const noexcept;
    void setActive(const bool& bValue) const noexcept;
    int getLayer() const noexcept;
    C_Component* addComponent(void* type) noexcept;
};