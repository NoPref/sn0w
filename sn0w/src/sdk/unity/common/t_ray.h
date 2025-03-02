#pragma once
#include <stdint.h>
#include "t_vec3.h"
#include "t_vec2.h"

struct ray_t {
public:
    vec3_t m_vecOrigin;
    vec3_t m_vecDirection;

    ray_t() = default;
    ~ray_t() = default;

    ray_t(const vec3_t& vecOrigin, const vec3_t& vecDirection) {
        this->m_vecOrigin = vecOrigin;
        this->m_vecDirection = vecDirection;
    }

};

class C_Collider;

struct raycast_hit_t {
public:
    vec3_t    m_vecPoint;
    vec3_t    m_vecNormal;
    uint32_t  m_iFaceID;
    float     m_fDistance;
    vec2_t    m_vecUV;
    uint64_t  m_iColliderInstanceID;

    raycast_hit_t() = default;
    ~raycast_hit_t() = default;

    C_Collider* getCollider() const noexcept;
};