#include "c_raycaster.h"
#include "../globals.hpp"

//call in unity thread only

bool CRaycaster::raycast(const vec3_t& vecSrc, const vec3_t& vecDirection, raycast_hit_t& rHit, const float& fDistance, const int32_t& nLayer) {
    static bool(*func)(vec3_t,vec3_t,raycast_hit_t,float,int32_t);
    if(func == NULL)
        func = (decltype(func))(g.lpBase + oxorany(0x4a0e5cc));
    return func(vecSrc, vecDirection, rHit, fDistance, nLayer);
}

bool CRaycaster::isVisible(const vec3_t& vecSrc, const vec3_t& vecDst) noexcept {
    raycast_hit_t hit{};
    return !CRaycaster::raycast(vecSrc, vec3_t(vecDst - vecSrc).normalized(), hit, vecSrc.distanceTo(vecDst), oxorany(16384));
};  