#include "c_legitbot.hpp"
#include "c_aimbot.hpp"
#include "../sn0w/c_raycaster.h"
#include "../globals.hpp"

void CLegitbot::createMove() noexcept {
    CLegitbot* const& thiz = g.sn0w.legit;
    if(!g.config.rage.aimbot.enabled && !g.config.rage.antiaim.enabled) {
        bool enabled{};
        for(uint8_t i=0;i<(sizeof(g.config.legit.configs) / sizeof(g.config.legit.configs[0]));++i) {
            if(g.config.legit.configs[i].m_bEnabled)
                enabled = true;
        }
        if(enabled) {
            if(thiz->processConfig()) {
                if(thiz->processTarget()) {
                    if(thiz->updateTarget()) {
                        thiz->aimbot();
                    }
                }
            }
        }
    }
}

bool CLegitbot::isTargetValid() const noexcept {
    if(this->m_target != NULL && this->m_targetBone != NULL) {
        return this->m_target->isAlive();
    }
    return false;
}

void CLegitbot::destroyTarget() noexcept {
    this->m_target = NULL;
    this->m_targetBone = NULL;
}

bool CLegitbot::processConfig() noexcept {
    const CLocalPlayer* local = g.vars.players.m_local;
    if(local != NULL && g.vars.players.m_localPhoton != NULL && g.vars.isCameraValid()) {
        if(local->isAlive()) {
            if(local->isCanShoot()) {
                for(uint8_t i=0;i<(sizeof(g.config.legit.configs) / sizeof(g.config.legit.configs[0])); ++i) {
                    legitbot_config_t& cfg = g.config.legit.configs[i];
                    if(cfg.m_weaponType == local->getCurrentWeapon()->getType()) {
                        this->m_currentConfig = &cfg;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool CLegitbot::processTarget() noexcept {
    float maxFOV = 7777.f;
    const CPlayerList& list = g.vars.players;
    const CLocalPlayer* local = list.m_local;
    if(local->getCurrentWeapon()->getType() == this->m_currentConfig->m_weaponType) {

        const euler_angles_t viewAngles = g.vars.mainCamera->getTransform()->getEulerAngles().normalized(90.f, false);
        const vec3_t vecCamera = local->getEyePos();

        for(uint8_t i=0;i<list.getSize();++i) {
            const CPlayerController* player = list[i];
            if(player != NULL) {
                if(player->isAlive()) {
                    if(player->m_photon->getTeam() != g.vars.players.m_localPhoton->getTeam()) {
                        for(uint8_t c=0;c<(sizeof(this->m_currentConfig->m_bones) / sizeof(this->m_currentConfig->m_bones[0]));++c) {
                            if(this->m_currentConfig->m_bones[c].m_bEnabled) {
                                const CTransform* bone = player->getBone(this->m_currentConfig->m_bones[c].m_bip);
                                if(bone != NULL) {
                                    const vec3_t vecBone = bone->getPosition();
                                    float fov = CAimbot::calcFOV(viewAngles, vecCamera, vecBone) / 2;
                                    if(fov <= this->m_currentConfig->m_fMaxFOV) {
                                        if(CRaycaster::isVisible(vecCamera, vecBone)) {
                                            if(fov < maxFOV) {
                                                maxFOV = fov;
                                                this->m_target = player;
                                                this->m_targetBone = bone;
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
    return this->isTargetValid();
}

bool CLegitbot::updateTarget() noexcept {
    const CLocalPlayer* local = g.vars.players.m_local;
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

    if(!local->isCanShoot()) {
        this->destroyTarget();
        return false;
    }

    if(local->getCurrentWeapon()->getType() != this->m_currentConfig->m_weaponType) {
        this->destroyTarget();
        return false;
    }

    const vec3_t vecCamera = local->getEyePos();
    const vec3_t vecBone = this->m_targetBone->getPosition();
    const euler_angles_t viewAngles = g.vars.mainCamera->getTransform()->getEulerAngles().normalized(90.f, false);

    const float fov = CAimbot::calcFOV(viewAngles, vecCamera, vecBone) / 2;
    if(fov > this->m_currentConfig->m_fMaxFOV) {
        this->destroyTarget();
        return false;
    }

    if(!CRaycaster::isVisible(vecCamera, vecBone)) {
        this->destroyTarget();
        return false;
    }
    return true;
}

void CLegitbot::aimbot() noexcept {
    CLocalPlayer* local = g.vars.players.m_local;
    const euler_angles_t viewAngles = local->getViewAngles();

    euler_angles_t aimAngle = CAimbot::calcAngle(local->getEyePos(), this->m_targetBone->getPosition());
    if(this->m_currentConfig->m_bRCS) {
        const euler_angles_t aimPunch = local->getAimPunch();
        aimAngle.pitch += aimPunch.pitch;
        aimAngle.yaw -= aimPunch.yaw;
    }

    euler_angles_t relative = (aimAngle - viewAngles);
    relative.pitch /= ((local->pCmd->m_bFire ? this->m_currentConfig->m_fPitchFire : this->m_currentConfig->m_fPitch) * 2);
    relative.yaw   /= ((local->pCmd->m_bFire ? this->m_currentConfig->m_fYawFire   : this->m_currentConfig->m_fYaw) * 2);
    relative.normalize();

    const euler_angles_t setAngle = (viewAngles + relative).normalized(70);
    local->setViewAngles(setAngle);
}