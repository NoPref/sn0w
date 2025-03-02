#include "c_ragebot.hpp"
#include "c_aimbot.hpp"
#include "../sn0w/c_raycaster.h"
#include "../globals.hpp"

void CRagebot::createMove() noexcept {
    if(g.config.rage.aimbot.enabled) {
        if(!g.config.rage.aimbot.exploits[2]) {
            if(g.sn0w.rage->getCamera())
                g.sn0w.rage->rotateCameraCM();
        }
        if(g.sn0w.rage->processTarget()) {
            if(g.sn0w.rage->updateTarget()) {
                g.sn0w.rage->checkTarget();
                g.sn0w.rage->autos();
            }
        }
        if(!g.config.rage.aimbot.exploits[2]) {
            g.sn0w.rage->aimbot();
        }
    }
}

void CRagebot::lateUpdate() noexcept {
    if(g.config.rage.aimbot.enabled && !g.config.rage.aimbot.exploits[2]) {
        if(g.sn0w.rage->getCamera()) {
            g.sn0w.rage->rotateCamera();
        }
    }
}

void CRagebot::update() noexcept {
    if(g.config.rage.aimbot.enabled) {
        g.sn0w.rage->doubletap();
    }
}

//pasted from unknowncheats, idc
void CRagebot::movementFix(const float& cameraYaw, const float& realYaw) {
    if(CLocalPlayer::pCmd != NULL) {
        CInputs& oldCmd = CLocalPlayer::oldCmd;
        CInputs* pcmd = CLocalPlayer::pCmd;
        if(pcmd->m_fForwardMove != 0.f && pcmd->m_fSideMove != 0.f) {
            float yawDelta = cameraYaw - realYaw;
            float f1{}, f2{};

            if (cameraYaw < 0.f)
                f1 = 360.f + cameraYaw;
            else
                f1 = cameraYaw;

            if (realYaw < 0.f)
                f2 = 360.f + realYaw;
            else
                f2 = realYaw;

            if (f2 < f1)
                yawDelta = abs(f2 - f1);
            else
                yawDelta = 360.0f - abs(f1 - f2);

            yawDelta = 360.0f - yawDelta;

            const vec2_t oldMove {
                oldCmd.m_fSideMove,
                oldCmd.m_fForwardMove
            };

            const vec2_t fixed {
                // cos(deg2rad(yawDelta)) * oldMove.x + cos(deg2rad(yawDelta + 90)) * oldMove.y,
                // sin(deg2rad(yawDelta)) * oldMove.x + sin(deg2rad(yawDelta + 90)) * oldMove.y,
            };

            g.vars.players.m_local->forceMove(fixed);
            pcmd->m_fForwardMove = fixed.y;
            pcmd->m_fSideMove = fixed.x;
        }
    }
}

bool CRagebot::isTargetValid() const noexcept {
    return this->m_target.isValid();
}

void CRagebot::destroyTarget() noexcept {
    this->m_target.destroy();
}

bool CRagebot::getCamera() noexcept {
    CLocalPlayer* local = g.vars.players.m_local;
    if(local != NULL && g.vars.isCameraValid()) {
        if(local->isAlive() && local->m_aim != NULL) {
            if(local->m_aim->m_FPSP != NULL) {

                if(local->m_viewMode == view_mode_fps)
                    this->m_currentCamera = local->m_aim->m_FPSP;
                else 
                    this->m_currentCamera = g.vars.mainCamera->getTransform();

                return this->m_currentCamera != NULL;
            }
        } 
    } 
    return false;
}

void CRagebot::rotateCamera() noexcept {
    CLocalPlayer* local = g.vars.players.m_local;
    const euler_angles_t viewAngles = local->getViewAngles();
    
    if(!this->m_bFiring) {
        this->m_cameraAngles = viewAngles;
    } else {
        if(this->isTargetValid()) {
            this->m_currentCamera->setEulerAngles(this->m_cameraAngles);
        } 
    }
}

void CRagebot::rotateCameraCM() noexcept {
    CLocalPlayer* local = g.vars.players.m_local;
    if(this->m_bFiring) {
        this->m_cameraAngles.pitch -= local->oldCmd.m_vecDeltaAimAngles.x;
        this->m_cameraAngles.yaw += local->oldCmd.m_vecDeltaAimAngles.y;
        this->m_cameraAngles.normalize(70);
    }
}

bool CRagebot::processTarget() noexcept {
    float maxFOV = 7777.f;
    const CPlayerList& list = g.vars.players;
    const CLocalPlayer* local = list.m_local;
    if(!list.isEmpty() && local != NULL && list.m_localPhoton != NULL && this->m_currentCamera != NULL) {
        if(local->isAlive()) {
            if(local->isHoldingGun()) {

                this->m_bFiring = local->pCmd->m_bFire && local->isCanShoot();

                const euler_angles_t viewAngles = g.vars.mainCamera->getTransform()->getEulerAngles().normalized(90.f, false);
                const vec3_t vecLocalOrigin = local->m_transform->getPosition();
                const vec3_t vecCamera = local->getEyePos();

                this->m_psInfo.m_vecDst = vecCamera;
                
                bool found{};
                for(uint8_t i=0;i<list.getSize();++i) {
                    if(found)
                        break;
                    const CPlayerController* player = list[i];
                    if(player != NULL) {
                        if(player->isAlive()) {
                            if(player->m_photon->getTeam() != list.m_localPhoton->getTeam()) {
                                for(uint8_t c=0;c<(sizeof(g.config.rage.aimbot.hitbox) / sizeof(g.config.rage.aimbot.hitbox[0]));++c) {
                                    if(g.config.rage.aimbot.hitbox[c]) {
                                        const CTransform* bone = player->getBone((bip)c);
                                        if(bone != NULL) {
                                            const vec3_t vecBone = bone->getPosition();
                                            const float fov = CAimbot::calcFOV(viewAngles, vecCamera, vecBone);
                                            if(fov <= g.config.rage.aimbot.max_fov) {
                                                if(CRaycaster::isVisible(vecCamera, vecBone)) {
                                                    found = true;
                                                    this->m_target.m_pPlayer = player;
                                                    this->m_target.m_pBone = bone;
                                                    break;
                                                } else {
                                                    if(fov < maxFOV) {
                                                        maxFOV = fov;
                                                        this->m_target.m_pPlayer = player;
                                                        this->m_target.m_pBone = bone;
                                                    } 
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

            }
        }
    }
    const bool isValid = this->isTargetValid();
    this->m_psInfo.m_bValid = isValid;
    if(isValid) {
        this->m_psInfo.m_vecDirection = (this->m_target.m_pBone->getPosition() - this->m_psInfo.m_vecDst).normalized();
    }
    return isValid;
}

bool CRagebot::updateTarget() noexcept {
    CLocalPlayer* local = g.vars.players.m_local;

    if(!this->isTargetValid()) {
        return false;
    }

    if(local == NULL || !g.vars.isCameraValid()) {
        this->destroyTarget();
        return false;
    }
    if(!local->isAlive()) {
        this->destroyTarget();
        return false;
    }
    if(!local->isHoldingGun()) {
        this->destroyTarget();
        return false;
    }

    const vec3_t vecCamera = local->getEyePos();
    const vec3_t vecBone = this->m_target.m_pBone->getPosition();
    const euler_angles_t viewAngles = g.vars.mainCamera->getTransform()->getEulerAngles().normalized(90.f, false);

    const float fov = CAimbot::calcFOV(viewAngles, vecCamera, vecBone);
    if(fov > g.config.rage.aimbot.max_fov) {
        this->destroyTarget();
        return false;
    }
    return true;
}

void CRagebot::checkTarget() noexcept {
    const CLocalPlayer* local = g.vars.players.m_local;
    const CInputs& oldCmd = local->oldCmd;
    const vec3_t vecCamera = local->getEyePos();
    const vec3_t vecBone = this->m_target.m_pBone->getPosition();

    this->m_target.m_bVisible = CRaycaster::isVisible(vecCamera, vecBone) || g.config.exploits.wallshot;
    
    if(oldCmd.m_fForwardMove != 0.f && oldCmd.m_fSideMove != 0.f) {
        //const float speed = sqrtf((oldCmd.m_fForwardMove * oldCmd.m_fForwardMove) + (oldCmd.m_fSideMove * oldCmd.m_fSideMove));
        const vec3_t vecForward = g.vars.mainCamera->getTransform()->getForward() * (oldCmd.m_fForwardMove / g.config.rage.aimbot.autostop_peek_factor);
        const vec3_t vecRight = g.vars.mainCamera->getTransform()->getRight() * (oldCmd.m_fSideMove / g.config.rage.aimbot.autostop_peek_factor);
        const vec3_t vecWish = vecCamera + vecForward + vecRight;

        this->m_target.m_bPredicted = CRaycaster::isVisible(vecWish, vecBone);
    } else this->m_target.m_bPredicted = false;

    this->m_psInfo.m_bValid = (this->m_target.m_bCanWallbang || this->m_target.m_bVisible);
}

void CRagebot::autoStop() noexcept {
    CLocalPlayer* local = g.vars.players.m_local;
    if(this->m_target.m_bPredicted || this->m_target.m_bVisible || this->m_target.m_bCanWallbang) {
        local->pCmd->m_fForwardMove /= g.config.rage.aimbot.autostop_mult;
        local->pCmd->m_fSideMove /= g.config.rage.aimbot.autostop_mult;
        local->oldCmd.m_fForwardMove = local->pCmd->m_fForwardMove;
        local->oldCmd.m_fSideMove = local->pCmd->m_fSideMove;
    }
}

void CRagebot::autoScope() noexcept {
    CLocalPlayer* local = g.vars.players.m_local;
    if(this->m_target.m_bPredicted || this->m_target.m_bVisible || this->m_target.m_bCanWallbang) {
        if(!local->isScoped())
            local->pCmd->m_bAim = true;
    }
}

void CRagebot::autoWall() noexcept {
    CLocalPlayer* local = g.vars.players.m_local;
    return; //POTOM
}

void CRagebot::autoFire() noexcept {
    CLocalPlayer* local = g.vars.players.m_local;
    this->m_bFiring = this->m_target.m_bVisible || this->m_target.m_bCanWallbang;
    if(!g.config.rage.aimbot.exploits[2] && local->isInAir() && this->m_bFiring) {
        this->m_bFiring = false;
    }
    if(this->m_bFiring)
        local->pCmd->m_bFire = true;
}
 
void CRagebot::autos() noexcept {
    CLocalPlayer* local = g.vars.players.m_local;
    if(!this->isTargetValid() || local == NULL)
        return;
    if(!local->isAlive())
        return;
    if(!local->isCanShoot())
        return;

    if(g.config.rage.aimbot.autostop && !g.config.rage.aimbot.exploits[2])
        this->autoStop();
    if(g.config.rage.aimbot.autoscope)
        this->autoScope();
    if(g.config.rage.aimbot.autowall)
        this->autoWall();
    if(g.config.rage.aimbot.autofire)
        this->autoFire();
}

void CRagebot::doubletap() noexcept {
    if(this->m_fDoubletapRecharge < 8.f) 
        this->m_fDoubletapRecharge += ImGui::GetIO().DeltaTime;

    if(g.config.rage.aimbot.exploits[0]) {
        CLocalPlayer* local = g.vars.players.m_local;
        if(local != NULL) {
            if(local->isAlive()) {
                if(local->isHoldingGun()) {
                    CGunController* gun = (CGunController*)local->getCurrentWeapon();
                    if(local->pCmd->m_bFire && this->m_fDoubletapRecharge >= 8.f) {
                        gun->m_fTimeFiredSafe.setValue(gun->m_fTimeFiredSafe.getValue() - (gun->m_fFireIntervalSafe.getValue()*2));
                        this->m_fDoubletapRecharge = 0.f;
                    }
                }
            }
        }
    }
}

void CRagebot::aimbot() noexcept {
    static bool returnViewAngles{};
    CLocalPlayer* local = g.vars.players.m_local;
    if(local != NULL) {
        if(local->isAlive()) {
            if(local->isHoldingGun() && this->m_bFiring && (this->m_target.m_bVisible || this->m_target.m_bCanWallbang) && this->isTargetValid()) {
                returnViewAngles = true;
                const vec3_t vecCamera = local->getEyePos();
                const vec3_t vecBone = this->m_target.m_pBone->getPosition();
                const euler_angles_t aimPunch = local->getAimPunch();
                euler_angles_t aimAngle = CAimbot::calcAngle(vecCamera, vecBone);
                aimAngle.pitch += aimPunch.pitch;
                aimAngle.yaw -= aimPunch.yaw;

                const CWeaponController* weapon = local->getCurrentWeapon();
                const float interval = (weapon->m_fLocalTime - ((CGunController*)weapon)->m_fTimeFiredSafe.getValue(true));
                const float maxInterval = ((CGunController*)weapon)->m_fFireIntervalSafe.getValue(true);
                if(maxInterval - interval < 0.05f) {

                    local->pCmd->m_vecDeltaAimAngles = {};
                    
                    local->setViewAngles(aimAngle.clampedPitch(70));
                    this->movementFix(this->m_cameraAngles.yaw, aimAngle.yaw);
                    
                } else {
                    local->setViewAngles(this->m_cameraAngles);
                }

            } else {
                if(returnViewAngles) {
                    local->setViewAngles(this->m_cameraAngles);
                    returnViewAngles = false;
                }
            }

        } else returnViewAngles = false;
    } else returnViewAngles = false;
}