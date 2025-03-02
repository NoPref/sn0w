#include <math.h>
#include "c_aimbot.hpp"

euler_angles_t CAimbot::calcAngle(const vec3_t& vecSrc, const vec3_t& vecDst) noexcept {
    euler_angles_t ret{};
    const vec3_t vecDelta = vecSrc - vecDst;
    const float magn = vecDelta.magnitude();
    if(magn != 0) {
        ret.pitch = rad2deg(asin(vecDelta.y / magn));
        ret.yaw   = rad2deg(-atan2(vecDelta.x, - vecDelta.z));
        ret.roll = 0.f;
    }
    return ret.normalized();
}

float CAimbot::calcFOV(const euler_angles_t& angView, const euler_angles_t& angTarget) noexcept {
    euler_angles_t diff = (angTarget - angView).normalized();
    return sqrtf((diff.pitch * diff.pitch) + (diff.yaw * diff.yaw));
}

float CAimbot::calcFOV(const euler_angles_t& angView, const vec3_t& vecSrc, const vec3_t& vecDst) noexcept {
    return CAimbot::calcFOV(angView, CAimbot::calcAngle(vecSrc, vecDst));
}