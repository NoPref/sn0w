#include "t_ray.h"
#include "../globals.hpp"

C_Collider* raycast_hit_t::getCollider() const noexcept {
    return (C_Collider*)CObject::findObjectFromID(this->m_iColliderInstanceID);
}