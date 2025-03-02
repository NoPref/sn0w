#pragma once
#include <stdint.h>
#include "c_player_list.h"
#include "../unity/include.h"
#include "../so2/include.h"

class CGameVars {
public:
    void* pCurrentGame{};
    void* pControls{};
    void* pTouchController{};
    void* pHUDView{};
    void* pNetworkingPeer{};
    void* pPlayerManager{};
    void* pGrenadeManager{};
    void* pWeaponDropManager{};
    void* pGrenadeEffectEmitter{};
    void* pBombManager{};
    void* pRadarManager{};
    void* pChatManager{};
    void* pWeaponMaterialManager{};
    void* pPlayerType{};
    void* pMainController{};
    C_Camera* mainCamera{};
    int32_t maxCTHealth{};
    int32_t maxTHealth{};
    CPlayerList players{}; 
    list_t<void*>* grenadeEffects{};
    CPlantedBombController* plantedBomb{};

    CGameVars() = default;
    ~CGameVars() = default;

    bool isInGame() const noexcept;
    bool isCameraValid() const noexcept;
    
    void updateMatrix() noexcept;
    void getCurrentGame() noexcept;
    void getNetworkingPeer() noexcept;
    void getPlayerManager() noexcept;
    void getGrenadeManager() noexcept;
    void getWeaponDropManager() noexcept;
    void getGrenadeEffectEmitter() noexcept;
    void getBombManager() noexcept;
    void getRadarManager() noexcept;
    void getChatManager() noexcept;
    void getWeaponMaterialManager() noexcept;
    void getMainController() noexcept;
    
    static void update() noexcept;
};