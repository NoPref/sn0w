#include "c_playercontroller.h"
#include "../globals.hpp"
#include "../unity/c_camera.h"
#include "../includes/il2cpp/il2cpp-api.h"
#include "common/structs.h"
#include "common/enums.h"
#include "c_aimcontroller.h"
#include "c_weaponrycontroller.h"
#include "c_weaponcontroller.h"
#include "c_kitcontroller.h"
#include "c_guncontroller.h"
#include "c_mecanimcontroller.h"
#include "c_movementcontroller.h"
#include "c_playerocclusion.h"
#include "c_bombcontroller.h"
#include "c_bipedmap.h"

bool CPlayerController::isAlive() const noexcept {
    if(this->m_photon        != NULL &&
       this->m_view          != NULL &&
       this->m_transform     != NULL && 
       this->m_weaponry      != NULL) {
        return this->m_photon->getHealth() > 0;
    }
    return false;
}

CWeaponController* CPlayerController::getCurrentWeapon() const noexcept {
    CWeaponController* pCurrent = this->m_weaponry->m_currentWeapon;
    if(pCurrent != NULL) {
        if(pCurrent->m_parameters != NULL) {
            if(pCurrent->m_parameters->m_id > 0) {
                return pCurrent;
            }
        }
    }
    return NULL;
}

bool CPlayerController::hasWeapon(const weapon_id& id) const noexcept {
    return this->m_weaponry->hasWeapon(id);
}

bool CPlayerController::isHoldingGun() const noexcept {
    const CWeaponController* pCurrent = this->getCurrentWeapon();
    if(pCurrent != NULL) {
        const weapon_id& id = pCurrent->m_parameters->m_id;
        return id > weapon_id_none && id < weapon_id_knife;
    }
    return false;
}

bool CPlayerController::isScoped() const noexcept {
    if(this->isHoldingGun()) {
        const CGunController* pCurrent = (CGunController*)this->getCurrentWeapon();
        const CGunParameters* pPars = pCurrent->m_parameters;
        if(pPars != NULL) {
            const sight_type& sightType = pPars->m_sightType;
            if(sightType != sight_type_default) {
                const state_simple_t<aiming_mode>* pAimingMode = pCurrent->m_aimingMode;
                const state_simple_t<gun_state>* pGunState = pCurrent->m_state;
                if(pAimingMode != NULL && pGunState != NULL) {
                    return ((pAimingMode->m_curState == aiming_mode_aiming || pAimingMode->m_curState == aiming_mode_start_aiming) && (pGunState->m_curState != gun_state_reloading || pGunState->m_curState != gun_state_pre_reloading));
                }
            }
        }
    }
    return false;
}

bool CPlayerController::isReloading() const noexcept {
    if(this->isHoldingGun()) {
        const CGunController* pCurrent = (CGunController*)this->getCurrentWeapon();
        const state_simple_t<gun_state>* pState = pCurrent->m_state;
        if(pState != NULL) 
            return pState->m_curState == gun_state_pre_reloading || pState->m_curState == gun_state_reloading;
    }
    return false;
}

bool CPlayerController::isCrouching() const noexcept {
    if(this->m_aim != NULL) {
        const state_simple_t<move_state>* pState = this->m_aim->m_moveState;
        if(pState != NULL)
            return pState->m_curState == move_state_crouch || pState->m_curState == move_state_finished_crouch;
    }
    return false;
}

bool CPlayerController::isVisible() const noexcept {
    if(this->m_playerOcclusion != NULL)
        return this->m_playerOcclusion->m_state == observation_state_visible;
    return false;
}

bool CPlayerController::isInAir() const noexcept {
    static bool (*func)(void*);
    if(func == NULL)
        func = (decltype(func))(g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("CharacterController"), oxorany("UnityEngine"), oxorany("UnityEngine.PhysicsModule.dll")), oxorany("get_isGrounded"), 0)->methodPointer);
    if(this->m_character != NULL) {
        return !func(this->m_character);
    }
    return false;
}

bool CPlayerController::isDefusing() const noexcept {
    const CDefuseKitController* pKit = this->m_weaponry->m_kit;
    if(pKit != NULL) {
        return pKit->m_state == defuse_kit_state_defusing;
    }
    return false;
}

bool CPlayerController::isPlanting() const noexcept {
    const CWeaponController* pCurrent = this->getCurrentWeapon();
    if(pCurrent != NULL) {
        if(pCurrent->m_parameters->m_id == weapon_id_bomb) {
            const CBombController* pBomb = (CBombController*)pCurrent;
            if(pBomb->m_state != NULL) {
                return pBomb->m_state->m_curState == bomb_state_planting;
            }
        }
    }
    return false;
}

void CPlayerController::setView(const view_mode& viewMode) noexcept {
    static void (*func)(CPlayerController*, CPlayerCharacterView*);
    static void (*func2)(CPlayerController*, view_mode);

    if(func == NULL && func2 == NULL) {
        func = (decltype(func))(g.lpBase + oxorany(0x27041ec)); 
        func2 = (decltype(func2))(g.lpBase + oxorany(0x2704340));
    }

    if(this->m_characterTPS != NULL && this->m_characterFPS != NULL && this->m_viewMode != viewMode) {
        if(viewMode == view_mode_tps) {
            func(this, this->m_characterTPS);
        } else {
            func(this, this->m_characterFPS);
        }
        func2(this, viewMode);
    }

}

CTransform* CPlayerController::getBone(const bip& num) const noexcept {
    if(this->m_characterTPS != NULL) {
        if(this->m_characterTPS->m_bipedMap != NULL) {
            return this->m_characterTPS->m_bipedMap->getBone(num);
        }
    }
    return NULL;
}

void CPlayerController::forceVisible() noexcept {
    static void (*func)(CObjectOccludee*,bool);
    if(func == NULL) 
        func = (decltype(func))(g.lpBase + oxorany(0x222c224));

    if(this->m_playerOcclusion != NULL) {
        this->m_playerOcclusion->m_bool2 = false;
        func(this->m_playerOcclusion, true);
    }
}