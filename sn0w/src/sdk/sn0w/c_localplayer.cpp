#include <algorithm>
#include "c_localplayer.h"
#include "../includes/il2cpp/il2cpp-api.h"
#include "../so2/include.h"
#include "../hooking.hpp"
#include "../offsets.hpp"
#include "../globals.hpp"

CInputs* CLocalPlayer::pCmd{};
CInputs CLocalPlayer::oldCmd{};
void* CLocalPlayer::pHitData{};
CPlayerController* CLocalPlayer::pHitted{};

vec3_t CLocalPlayer::getEyePos() const noexcept {
    if(this->m_mainCameraHolder != NULL)
        return this->m_mainCameraHolder->getPosition();
    return vec3_t{};
}

void CLocalPlayer::clampAngles() noexcept {
    if(this->m_aim != NULL) {
        if(this->m_aim->m_data != NULL) {
            this->m_aim->m_data->m_angYaw.normalize();
        }
    }
}

euler_angles_t CLocalPlayer::getViewAngles() const noexcept {
    euler_angles_t ret{};
    if(this->m_aim != NULL) {
        if(this->m_aim->m_data != NULL) {
            const float fPitch = this->m_aim->m_data->m_angPitch.pitch;
            const float fYaw = this->m_aim->m_data->m_angYaw.yaw;
            ret = euler_angles_t{fPitch, fYaw, 0.f}.normalized(); //не над нормализовывать
        }
    }
    return ret;
}

void CLocalPlayer::setViewAngles(const euler_angles_t& angViewAngles) noexcept {
    if(this->m_aim != NULL) {
        if(this->m_aim->m_data != NULL) {
            this->m_aim->m_data->m_angPitch.pitch = angViewAngles.pitch;
            this->m_aim->m_data->m_angYaw.yaw = angViewAngles.yaw;
        }
    }
}

euler_angles_t CLocalPlayer::getAimPunch() const noexcept {
    euler_angles_t ret{};
    if(this->isHoldingGun()) {
        const CGunController* pGun = (CGunController*)this->getCurrentWeapon();
        if(pGun != NULL) {
            const CRecoilData* pRecoilData = pGun->m_recoilData;
            if(pRecoilData != NULL) {
                ret = pRecoilData->m_angAimPunch;
            } 
        }
    } 
    return ret;
}

vec2_t CLocalPlayer::getJoystickAxis() const noexcept {
    vec2_t ret{};
    if(g.vars.pTouchController != NULL) {
        const void* const pJoystick = *(void**)((unsigned long long)g.vars.pTouchController + g.offsets.touch_con.joystick);
        if(pJoystick != NULL) {
            const float fRadius = *(float*)((unsigned long long)pJoystick + g.offsets.joystick.radius);
            const vec3_t vecCurTouch = *(vec3_t*)((unsigned long long)pJoystick + g.offsets.joystick.cur_pos);
            const vec3_t vecJoystick = *(vec3_t*)((unsigned long long)pJoystick + g.offsets.joystick.pos);
            vec3_t vecDelta = vecCurTouch - vecJoystick;
            float fNum = std::clamp<float>(vecDelta.magnitude() / fRadius, 0.f, 1.f);
            vecDelta.normalize();
            if(fNum >= .45f && fNum < .8f) {
                ret.x = vecDelta.x * .45f;
                ret.y = vecDelta.y * .45f;
            }
            else {
                if(fNum < .45f) {
                    fNum = 0.f;
                }
                ret.x = vecDelta.x * fNum;
                ret.y = vecDelta.y * fNum;
            }
        }
    }
    return ret;
}

bool CLocalPlayer::isCanShoot() const noexcept {
    if(this->isHoldingGun()) {
        const state_simple_t<gun_state>* pState = ((CGunController*)this->getCurrentWeapon())->m_state;
        if(pState != NULL) {
            return pState->m_curState == gun_state_ready;
        }
    }
    return false;
}

void CLocalPlayer::forceAttack() noexcept {
    if(this->pCmd != NULL)
        this->pCmd->m_bFire = true;
}

void CLocalPlayer::forceMove(const vec2_t& vecDirection) noexcept {
    if(this->m_movement != NULL) {
        CPlayerTranslationParameters* pars = this->m_movement->m_parameters;
        CPlayerTranslationData* data = this->m_movement->m_data;
        if(data != NULL && pars != NULL) {
            CWalkParameters* walkPars = pars->m_walkParameters;
            C_CrouchParameters* crouchPars = pars->m_crouchParameters;
            blended_value_t<vec2_t>* dir = data->m_vecDampedRelativeDirection;
            if(dir != NULL && crouchPars != NULL) {
                dir->m_actual = (vecDirection * (this->isCrouching() ? crouchPars->m_fCrouchSpeedMultiplier : walkPars->m_fWalkSpeedMultiplier));
            }
        }
    }
}