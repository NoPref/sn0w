#pragma once
#include "../unity/common/include.h"

class CRaycaster {
public:
    static bool raycast(const vec3_t& vecSrc, const vec3_t& vecDirection, raycast_hit_t& rHit, const float& fDistance, const int32_t& nLayer);
    static bool isVisible(const vec3_t& vecSrc, const vec3_t& vecDst) noexcept;
};