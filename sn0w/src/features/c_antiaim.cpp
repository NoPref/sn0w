#include <random>
#include "c_antiaim.hpp"
#include "../globals.hpp"

void CAntiAim::createMove() noexcept {
    if(g.config.rage.antiaim.enabled) {
        g.sn0w.antiaim->getAngles();
        g.sn0w.antiaim->setAngles();
    }
}

void CAntiAim::lateUpdate() noexcept {
    if(g.config.rage.antiaim.enabled) {
        g.sn0w.antiaim->getCamera();
        g.sn0w.antiaim->rotateCamera();
    }
}

void CAntiAim::getCamera() noexcept {
    const CLocalPlayer* local = g.vars.players.m_local;
    if(local != NULL) {
        if(local->isAlive() && local->m_aim != NULL) {
            if(local->m_aim->m_FPSP != NULL) {

                if(local->m_viewMode == view_mode_fps)
                    this->m_currentCamera = local->m_aim->m_FPSP;
                else 
                    this->m_currentCamera = g.vars.mainCamera->getTransform();

            }
        } else this->m_currentCamera = NULL;
    } else this->m_currentCamera = NULL;
}

void CAntiAim::getAngles() noexcept {
    const CLocalPlayer* local = g.vars.players.m_local;
    if(local != NULL){
        if(local->isAlive()) {
            if(this->m_cameraAngles.isEmpty())
                this->m_cameraAngles = local->getViewAngles();
        } else this->m_cameraAngles = euler_angles_t{};
    } else this->m_cameraAngles = euler_angles_t{};
}

void CAntiAim::setAngles() noexcept {
    CRagebot* const& rage = g.sn0w.rage;
    std::random_device device{};
    std::mt19937 randomizer(device());
    static bool randFlick{};

    CLocalPlayer* local = g.vars.players.m_local;
    if(local != NULL && !this->m_cameraAngles.isEmpty()){
        this->m_cameraAngles.normalize(70.f);
        if(local->isAlive()) {
            const float oldForward = local->pCmd->m_fForwardMove;
            const float oldSide = local->pCmd->m_fSideMove;
            this->m_cameraAngles.pitch -= local->oldCmd.m_vecDeltaAimAngles.x;
            this->m_cameraAngles.yaw += local->oldCmd.m_vecDeltaAimAngles.y;

            euler_angles_t anglesToSet{};
            switch(g.config.rage.antiaim.mode) {
                case 0: { //static
                    // anglesToSet = euler_angles_t{g.config.rage.antiaim.pitch, g.config.rage.antiaim.yaw, 0};
                    break;
                }
                case 1: { //jitter
                    static bool flip{};
                    // anglesToSet = euler_angles_t{g.config.rage.antiaim.pitch, g.config.rage.antiaim.yaw, 0};
                    if(flip) {
                        anglesToSet.yaw += g.config.rage.antiaim.jitter_range;
                    } else {
                        anglesToSet.yaw -= g.config.rage.antiaim.jitter_range;
                    }
                    flip = !flip;
                    break;
                }
                case 2: { //spin
                    static float yaw = 0;
                    // anglesToSet = euler_angles_t{g.config.rage.antiaim.pitch, yaw, 0};
                    yaw += g.config.rage.antiaim.spin_speed;
                    if(yaw > 360)
                        yaw = 0;
                    break;
                }
                default: { //random flick
                    static float timer{};
                    // anglesToSet = euler_angles_t{g.config.rage.antiaim.pitch, g.config.rage.antiaim.yaw, 0};
                    timer += ImGui::GetIO().DeltaTime;
                    if(timer >= (float)g.config.rage.antiaim.flick_rate / 1000) {
                        randFlick = !randFlick;
                        timer = 0;
                    }
                    if(randFlick) {
                        std::uniform_int_distribution<> randYaw(-180, 180);
                        std::uniform_int_distribution<> randPitch(-70, 70);

                        anglesToSet.yaw = randYaw(randomizer);
                        anglesToSet.pitch = randPitch(randomizer);
                        randFlick = false;
                    } else {
                        anglesToSet.yaw = g.config.rage.antiaim.yaw;
                        anglesToSet.pitch = g.config.rage.antiaim.pitch;
                    }
                    break;
                }
            };

            if(g.config.rage.antiaim.defensive) {
                if((g.config.rage.aimbot.enabled && rage->isTargetValid()) && (rage->m_target.m_bVisible || rage->m_target.m_bCanWallbang || rage->m_target.m_bPredicted || local->isInAir())) {
                    std::uniform_int_distribution<> randYaw(-180, 180);
                    std::uniform_int_distribution<> randPitch(-70, 70);

                    anglesToSet.yaw = randYaw(randomizer);
                    anglesToSet.pitch = randPitch(randomizer);
                }
            }

            if((g.config.rage.antiaim.pitch == -1 && g.config.rage.antiaim.mode != 3 && !randFlick) && g.config.rage.antiaim.mode != 3)
                anglesToSet.pitch = this->m_cameraAngles.pitch;

            anglesToSet.normalize(70);

            bool silentShoot{};
            bool pSilentShoot{};
            bool grenadeThrow{};
            bool returnAngles{};
            
            const CWeaponController* curWeapon = local->getCurrentWeapon();
            if(curWeapon != NULL) {
                if(curWeapon->getType() == weapon_type_grenade) {
                    CGrenadeController* grenade = (CGrenadeController*)curWeapon;
                    if(grenade->m_bPrevAimCmd || grenade->m_bPrevFireCmd) {
                        grenadeThrow = true;
                    }
                }
            }

            if(local->pCmd->m_bFire && g.config.rage.aimbot.enabled && rage->isTargetValid() && (rage->m_target.m_bVisible || rage->m_target.m_bCanWallbang)) {
                silentShoot = true;
                if(g.config.rage.aimbot.exploits[2])
                    pSilentShoot = true;
            }

            if(local->pCmd->m_bFire || local->pCmd->m_bDrop || local->pCmd->m_bPickup || grenadeThrow) {
                returnAngles = true;
            }

            if(!returnAngles || pSilentShoot) {
                local->setViewAngles(euler_angles_t{anglesToSet.pitch, this->m_cameraAngles.yaw - anglesToSet.yaw, 0});
            } else {
                if(!silentShoot)
                    local->setViewAngles(this->m_cameraAngles);
            }
            
            CRagebot::movementFix(this->m_cameraAngles.yaw, local->getViewAngles().yaw);
        }
    }
}

void CAntiAim::rotateCamera() noexcept {
    const CLocalPlayer* local = g.vars.players.m_local;
    if(local != NULL && this->m_currentCamera != NULL) {
        if(local->isAlive()) {
            this->m_currentCamera->setEulerAngles(this->m_cameraAngles);
        }
    }
}