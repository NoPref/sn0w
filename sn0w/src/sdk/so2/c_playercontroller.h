#pragma once
#include "../includes/imgui/imgui.h"
#include "../unity/c_component.h"
#include "../unity/c_transform.h"
#include "../unity/c_gameobject.h"
#include "../unity/c_renderer.h"
#include "../photonengine/c_photonplayer.h"
#include "../photonengine/c_photonview.h"
#include "common/include.h"

class CPlayerCharacterView;
class CBipedMap;
class CPlayerOcclusionController;
class CAimController;
class CWeaponryController;
class CWeaponController;
class CMecanimController;
class CMovementController;
class C_CharacterLODGroup;
class CArmsLodGroup;
class C_Camera;

#pragma pack(1)
class CPlayerController : public C_Component {
char pad[sizeof(void*)*2];
public:
    CTransform* m_mainCameraHolder;
    CGameObject* m_FPSCameraHolder;
    CGameObject* m_FPSDirective;
    void* m_levelZones;
    CPlayerCharacterView* m_characterTPS;
    CPlayerCharacterView* m_characterFPS;
    bool m_bReconnectedInstance;
    team m_team;
    char pad2[0x2];
    float m_fLocalTime;
    CAimController* m_aim;
    CWeaponryController* m_weaponry;
    CMecanimController* m_mecanim;
    CMovementController* m_movement;
    void* m_armsAnimation;
    void* m_playerHit;
    CPlayerOcclusionController* m_playerOcclusion;
    void* m_network;
    CArmsLodGroup* m_armsLODGroup; 
    CPlayerCharacterView* m_characterView;
    bool m_bIsCharacterVisible;
    bool m_bIsCharacterVisible2;
    char pad3[0x2];
    float m_fSnapshotSetTime;
    void* m_playerSound;
    void* m_mainCamera; 
    void* m_FPSCamera; 
    void* m_playerMarkerTrigger; 
    CTransform* m_transform;
    array_t<void*>* m_aControllers; 
    dictionary_t<void*,void*>* m_dControllerByType;
    void* m_character; 
    void* m_skinnedMeshLodGroup; 
    C_CharacterLODGroup* m_characterLODGroup; 
    bool m_bIsPreInitialized;
    bool m_bIsPostInitialized;
    char pad4[0x2];
    view_mode m_viewMode;
    char pad5[0x3];
    char pad6[sizeof(void*)*3];
    CPhotonView* m_view; 
    int32_t m_iPlayerID;
    int32_t m_iPlayerViewID; 
    CPhotonPlayer* m_photon;

    bool isAlive() const noexcept;
    CWeaponController* getCurrentWeapon() const noexcept;
    bool hasWeapon(const weapon_id& id) const noexcept;
    bool isHoldingGun() const noexcept;
    bool isScoped() const noexcept;
    bool isReloading() const noexcept;
    bool isCrouching() const noexcept;
    bool isVisible() const noexcept;
    bool isInAir() const noexcept;
    bool isDefusing() const noexcept;
    bool isPlanting() const noexcept;
    void setView(const view_mode& viewMode) noexcept;
    CTransform* getBone(const bip& num) const noexcept;
    void forceVisible() noexcept;
};
#pragma pack()

#pragma pack(1)
class CInputs {
char pad[sizeof(void*)*2];
public:
    float m_fSideMove;
    float m_fForwardMove;
    bool m_bCrouch;
    bool m_bReload;
    char pad2[0x2];
    int32_t m_iSwitchToWeapon;
    bool m_bAim;
    bool m_bFire;
    bool m_bJump;
    bool m_bDrop;
    bool m_bAction;
    bool m_bInspect;
    bool m_bPickup;
    bool m_bUnknown;
    vec2_t m_vecDeltaAimAngles;
};
#pragma pack()

#pragma pack(1)
class C_CharacterLODGroup {
char pad[0x38];
public:
    CRenderer* m_meshRenderer;
    string_t* m_sCharacter;
    string_t* m_sSkinName;
    array_t<CRenderer*>* m_aMeshRenderers;
};
#pragma pack()

#pragma pack(1)
class CArmsLodGroup {
char pad[0x38];
public:
    CRenderer* m_glovesMeshRenderer;
    CRenderer* m_armsMeshRenderer;
    CObject* m_mesh;
    string_t* m_sArmsName;
    string_t* m_sGlovesName;
};
#pragma pack()