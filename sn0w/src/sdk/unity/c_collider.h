#pragma once 
#include "c_component.h"
#include "t_bounds.h"

class C_Collider : public C_Component {
public:
    bounds_t getBounds() const noexcept;
};