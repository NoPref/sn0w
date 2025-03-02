#include "c_game_vars.h"
#include "../includes/il2cpp/il2cpp-api.h"
#include "../globals.hpp"
#include <android/log.h>

bool CGameVars::isInGame() const noexcept {
    if(this->players.m_localPhoton == NULL || this->pCurrentGame == NULL || this->pPlayerManager == NULL)
        return false;
   return this->players.m_localPhoton->getTeam() != team_none;
}

bool CGameVars::isCameraValid() const noexcept {
    if(this->mainCamera == NULL)
        return false;
    return this->mainCamera->getTransform() != NULL;
}

void CGameVars::updateMatrix() noexcept {
    if(this->mainCamera != NULL) {
        C_Camera::m_viewMatrix = this->mainCamera->getViewMatrix();
        C_Camera::m_projMatrix = this->mainCamera->getProjectionMatrix();
    }
}

void CGameVars::getCurrentGame() noexcept {
    static FieldInfo* pField{};
    if(pField == NULL) {
        Il2CppClass* pClass = g.il2cpp.getClass(oxorany("GameController"), oxorany("Axlebolt.Standoff.Game"), oxorany("Assembly-CSharp.dll"));
        const char* const szClassName = g.il2cpp.class_get_name(pClass);
        void* iter{};
        while(FieldInfo* field = g.il2cpp.class_get_fields(pClass, &iter)) {
            const char* const szFieldClassName = g.il2cpp.class_get_name(g.il2cpp.type_get_class_or_element_class(g.il2cpp.field_get_type(field)));
            if(!strcmp(szClassName, szFieldClassName)) {
                pField = field;
                break;
            }
         }
    } else 
        g.il2cpp.field_static_get_value(pField, &this->pCurrentGame);
    
    if(this->pCurrentGame != NULL) {
        this->pControls = *(void**)((unsigned long long)this->pCurrentGame + ofs(game_controller.controls));
        if(this->pControls != NULL) {
            this->pTouchController = *(void**)((unsigned long long)this->pControls + ofs(player_controls.touch));
            this->pHUDView         = *(void**)((unsigned long long)this->pControls + ofs(player_controls.hud));
        }
    } else {
        this->pControls = NULL;
        this->pTouchController = NULL;
        this->pHUDView = NULL;
    }
}

void CGameVars::getNetworkingPeer() noexcept {
    static FieldInfo* pField{};
    if(pField == NULL)
        pField = g.il2cpp.class_get_field_from_name(g.il2cpp.getClass(oxorany("PhotonNetwork"), oxorany(""), oxorany("Assembly-CSharp.dll")), oxorany("networkingPeer"));
    else 
        g.il2cpp.field_static_get_value(pField, &this->pNetworkingPeer);

    if(this->pNetworkingPeer != NULL) {
        this->players.m_localPhoton = *(CPhotonPlayer**)((unsigned long long)this->pNetworkingPeer + ofs(networking_peer.localplayer));
    } else {
        this->players.m_localPhoton = NULL;
    }
}

void CGameVars::getPlayerManager() noexcept {
    static FieldInfo* pField{};
    if(pField == NULL) 
        pField = g.il2cpp.getSingletonField(g.il2cpp.getClass(oxorany("PlayerManager"), oxorany("Axlebolt.Standoff.Player"), oxorany("Assembly-CSharp.dll")));
    else
        g.il2cpp.field_static_get_value(pField, &this->pPlayerManager);

    if(this->pPlayerManager != NULL) {
        this->players.m_local = *(CLocalPlayer**)((unsigned long long)this->pPlayerManager + ofs(player_manager.localplayer));
        this->players.m_data = *(decltype(this->players.m_data)*)((unsigned long long)this->pPlayerManager + ofs(player_manager.players_d));
    } else {
        this->players.m_local = NULL;
        this->players.m_data = NULL;
    }

    static FieldInfo* pFieldT{};
    static FieldInfo* pFieldCT{};
    if(pFieldT == NULL && pFieldCT == NULL) {
        pFieldT  = g.il2cpp.class_get_field_from_name(g.il2cpp.getClass(oxorany("PlayerController"), oxorany("Axlebolt.Standoff.Player"), oxorany("Assembly-CSharp.dll")), oxorany("MaxTrHealth"));
        pFieldCT = g.il2cpp.class_get_field_from_name(g.il2cpp.getClass(oxorany("PlayerController"), oxorany("Axlebolt.Standoff.Player"), oxorany("Assembly-CSharp.dll")), oxorany("MaxCtHealth"));
    } else {
        g.il2cpp.field_static_get_value(pFieldT, &this->maxTHealth);
        g.il2cpp.field_static_get_value(pFieldCT, &this->maxCTHealth);
    }
}

void CGameVars::getGrenadeManager() noexcept {
    static FieldInfo* pField{};
    if(pField == NULL)
        pField = g.il2cpp.getSingletonField(g.il2cpp.getClass(oxorany("GrenadeManager"), oxorany("Axlebolt.Standoff.Inventory.Grenade"), oxorany("Assembly-CSharp.dll")));
    else 
        g.il2cpp.field_static_get_value(pField, &this->pGrenadeManager);
    
   /*if(this->pGrenadeManager != NULL) {
        this->droppedGrenades = *(decltype(this->droppedGrenades)*)((unsigned long long)this->pGrenadeManager + ofs(grenade_manager.dropped));
    } else {
        this->droppedGrenades = NULL;
    }*/
}

void CGameVars::getWeaponDropManager() noexcept {
    static FieldInfo* pField{};
    if(pField == NULL) 
        pField = g.il2cpp.getSingletonField(g.il2cpp.getClass(oxorany("WeaponDropManager"), oxorany("Axlebolt.Standoff.Inventory.Drop"), oxorany("Assembly-CSharp.dll")));
    else 
        g.il2cpp.field_static_get_value(pField, &this->pWeaponDropManager);
    
    /*if(this->pWeaponDropManager != NULL) {
        this->droppedWeapons = *(decltype(this->droppedWeapons)*)((unsigned long long)this->pWeaponDropManager + ofs(weapon_drop_manager.dropped));
    } else {
        this->droppedWeapons = NULL;
    }*/
}

void CGameVars::getGrenadeEffectEmitter() noexcept {
    static FieldInfo* pField{};
    if(pField == NULL)
        pField = g.il2cpp.getSingletonField(g.il2cpp.getClass(oxorany("GrenadeEffectEmitter"), oxorany("Axlebolt.Standoff.Inventory.Grenade"), oxorany("Assembly-CSharp.dll")));
    else
        g.il2cpp.field_static_get_value(pField, &this->pGrenadeEffectEmitter);
    
    if(this->pGrenadeEffectEmitter != NULL) {
        this->grenadeEffects = *(decltype(this->grenadeEffects)*)((unsigned long long)this->pGrenadeEffectEmitter + ofs(grenade_effect_emitter.effects));
    } else {
        this->grenadeEffects = NULL;
    }
}

void CGameVars::getBombManager() noexcept {
    static FieldInfo* pField{};
    if(pField == NULL)
        pField = g.il2cpp.getSingletonField(g.il2cpp.getClass(oxorany("BombManager"), oxorany("Axlebolt.Standoff.Inventory.Bomb"), oxorany("Assembly-CSharp.dll")));
    else 
        g.il2cpp.field_static_get_value(pField, &this->pBombManager);

    if(this->pBombManager != NULL) {
        this->plantedBomb = *(CPlantedBombController**)((unsigned long long)this->pBombManager + ofs(bomb_manager.planted));
    } else {
        this->plantedBomb = NULL;
    }
}

void CGameVars::getRadarManager() noexcept {
    static FieldInfo* pField{};
    if(pField == NULL)
        pField = g.il2cpp.getSingletonField(g.il2cpp.getClass(oxorany("RadarManager"), oxorany("Axlebolt.Standoff.Game.Radar"), oxorany("Assembly-CSharp.dll")));
    else
        g.il2cpp.field_static_get_value(pField, &this->pRadarManager);
}


void CGameVars::getChatManager() noexcept {
    static FieldInfo* pField{};
    if(pField == NULL)
        pField = g.il2cpp.getSingletonField(g.il2cpp.getClass(oxorany("ChatManager"), oxorany("Axlebolt.Standoff.Game"), oxorany("Assembly-CSharp.dll")));
    else
        g.il2cpp.field_static_get_value(pField, &this->pChatManager);
}


void CGameVars::getWeaponMaterialManager() noexcept {
    static FieldInfo* pField{};
    if(pField == NULL)
        pField = g.il2cpp.getSingletonField(g.il2cpp.getClass(oxorany("WeaponMaterialManager"), oxorany("Axlebolt.Standoff.Inventory"), oxorany("Assembly-CSharp.dll")));
    else 
        g.il2cpp.field_static_get_value(pField, &this->pWeaponMaterialManager);
}

void CGameVars::getMainController() noexcept {
    static FieldInfo* pField{};
    if(pField == NULL) {
        Il2CppClass* pClass = g.il2cpp.getClass(oxorany("MainController"), oxorany("Axlebolt.Standoff.Main"), oxorany("Assembly-CSharp.dll"));
        const char* const szClassName = g.il2cpp.class_get_name(pClass);
        void* iter{};
        while(FieldInfo* field = g.il2cpp.class_get_fields(pClass, &iter)) {
            const char* const szFieldClassName = g.il2cpp.class_get_name(g.il2cpp.type_get_class_or_element_class(g.il2cpp.field_get_type(field)));
            if(!strcmp(szClassName, szFieldClassName)) {
                pField = field;
                break;
            }
         }
    } else
        g.il2cpp.field_static_get_value(pField, &this->pMainController);
}

void CGameVars::update() noexcept {
    g.window = CScreen::getResolution();
    CGameVars& thiz = g.vars;
    thiz.mainCamera = C_Camera::getMain();
    thiz.updateMatrix();
    thiz.getCurrentGame();
    thiz.getNetworkingPeer();
    thiz.getPlayerManager();
    thiz.getGrenadeManager();
    thiz.getWeaponDropManager();
    thiz.getGrenadeEffectEmitter();
    thiz.getBombManager();
    thiz.getRadarManager();
    thiz.getChatManager();
    thiz.getWeaponMaterialManager();
    thiz.getMainController();
}