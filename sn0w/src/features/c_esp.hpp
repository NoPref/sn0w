#pragma once
#include "../singleton.hpp"
#include "../includes/imgui/include.h"
#include "../sdk/unity/common/include.h"
#include "../sdk/unity/c_camera.h"
#include "../sdk/so2/include.h"
#include "../sdk/sn0w/c_player_list.h"

/*
    i have 2 player lists (first in CGameVars) due to data race(game will crash due to null ptr dereference), 
    so i get one list from game thread and one from render thread.
*/

namespace esp {
    struct hitted_skeleton_t {
        vec3_t m_vecBones[bip_max_tps]{};
    };
};

class C_ESP : public CSingleton<C_ESP> {
public:
    ImDrawList* m_pDrawlist{};
    C_Camera* m_pCamera{};
    void* m_pNetworkingPeer{};
    void* m_pPlayerManager{};
    void* m_pWeaponDropManager{};
    void* m_pGrenadeManager{};
    void* m_pBombManager{};
    CPlantedBombController* m_pPlantedBomb{};
    CPlayerList m_players{};
    dictionary_t<void*, CWeaponDropController*>* m_droppedWeapons{};
    dictionary_t<void*, CDroppedGrenadeController*>* m_droppedGrenades{};

    //hitted_skeleton_t m_aHittedSkeletons[5]{};
    uint8_t m_iCurrentHittedIndex{};

    C_ESP() = default;
    ~C_ESP() = default;

    static void render() noexcept;
    //static void hitP() noexcept;
    void updateVars() noexcept;

    ImRect getRect(const vec3_t& vecCoords, const vec3_t& vecHeadCoords, const float& width) noexcept;
    float getAlphaFactor(const vec3_t& vecOrigin, float startDistance = 6.5f) const noexcept;
    
    void players() noexcept;
    void droppedWeapons() noexcept;
    void droppedGrenades() noexcept;
    void bomb() noexcept;
};