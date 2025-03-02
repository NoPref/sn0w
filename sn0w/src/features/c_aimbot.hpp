#pragma once
#include "../singleton.hpp"
#include "../sdk/so2/include.h"
#include "../sdk/unity/common/include.h"

class CAimbot : public CSingleton<CAimbot> {
public:
    CAimbot() = default;
    ~CAimbot() = default;

    static euler_angles_t calcAngle(const vec3_t& vecSrc, const vec3_t& vecDst) noexcept;
    static float calcFOV(const euler_angles_t& angView, const euler_angles_t& angTarget) noexcept;
    static float calcFOV(const euler_angles_t& angView, const vec3_t& vecSrc, const vec3_t& vecDst) noexcept;
};