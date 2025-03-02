#pragma once
#include "../unity/common/include.h"
#include "../so2/c_playercontroller.h"

class CLocalPlayer : public CPlayerController {
public:
    static CInputs* pCmd;
    static CInputs oldCmd;
    static void* pHitData;
    static CPlayerController* pHitted;

    vec3_t         getEyePos() const noexcept;

    void           clampAngles() noexcept;
    euler_angles_t getViewAngles() const noexcept;
    void           setViewAngles(const euler_angles_t& angViewAngles) noexcept;

    euler_angles_t getAimPunch() const noexcept;
    vec2_t         getJoystickAxis() const noexcept;

    bool           isCanShoot() const noexcept;
    void           forceAttack() noexcept;

    void           forceMove(const vec2_t& vecDirection) noexcept;
};