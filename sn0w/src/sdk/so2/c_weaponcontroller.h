#pragma once
#include <stdint.h>
#include <string>
#include "../includes/imgui/imgui.h"
#include "../unity/c_component.h"
#include "../unity/c_transform.h"
#include "../unity/c_renderer.h"
#include "common/include.h"

enum visibility_state : uint8_t {
    visibility_state_just_switched = 0,
    visibility_state_waiting_switch_animation = 1,
    visibility_state_set_visible = 2,
};

enum handle_state : uint8_t {
    handle_state_primary = 0,
    handle_state_secondary = 1,
    handle_state_not_stated = 2,
};

class CPlayerController;
class CMecanimController;
class CMecanimLayerInfo;
class CWeaponLodGroup;
class CWeaponParameters;
class CWeaponMaterialController;
class CWeaponDropData;

#pragma pack(1)
class CWeaponController : public C_Component {
char pad3[sizeof(void*)];
public: 
    CPlayerController* m_player;
    CMecanimController* m_mecanim;
    void* m_weaponAnimationController;
    void* m_weaponAnimationParameters;
    visibility_state m_animVisibilityState;
    char pad4[0x3];
    view_mode m_viewMode;
    char pad5[0x3];
    delegate_t* m_action1;
    delegate_t* m_action2;
    CTransform* m_transform;
    array_t<void*>* m_aControllers;
    void* m_ptr1;
    void* m_ptr2;
    float m_fLocalTime;
    float m_fDeltaTime;
    CWeaponLodGroup* m_LODGroup;
    handle_state m_handlingState;
    char pad6[0x3];
    uint8_t m_iAnimationWeaponID;
    char pad7[0x3];
    string_t* m_sAnimationWeaponName;
    int32_t m_iOwnerID;
    int32_t m_int1;
    CWeaponParameters* m_parameters;
    void* m_ptr3;
    void* m_map;
    uint8_t m_iSlotIndex;
    bool m_bIsActive;
    char pad9[0x6];
    void* m_statrackController;
    CWeaponMaterialController* m_material;
    CMecanimLayerInfo* m_layerInfo;
    void* m_cmd;
    void* m_ptr4;
    void* m_ptr5;

    weapon_type getType() const noexcept;
    std::string getName() const noexcept;
    char getIcon() const noexcept;
};
#pragma pack()

#pragma pack(1)
class CWeaponLodGroup : public C_Component {
char pad2[sizeof(void*)];
public:
    array_t<void*>* m_aWeaponLayers;
    bool m_bInitialized;
    char pad3[0x7];
    array_t<void*>* m_aActiveLodChildren;
    array_t<CRenderer*>* m_aChildMeshRenderers;
    void* m_activeLOD;
    array_t<CRenderer*>* m_aMeshRenderers;
    CRenderer* m_meshRenderer;
    weapon_id m_id;
    char pad4[0x7];
    CTransform* m_transform;
    int32_t m_iCurrentLayerIndex;
    bool m_bCombined;
};
#pragma pack()

#pragma pack(1)
class CInventoryParameters {
char pad[sizeof(void*)*3];
public:
    weapon_id m_id;
    char pad2[0x7];
    string_t* m_sDisplayName;
    int32_t m_iCost;
    int32_t m_iMovementRate;
    void* m_sprites;
    team m_team;
    bool m_bAvailableCreateBuyReq;
    char pad3[0x2];
    nullable<safe_int_t> m_idSafe;
    nullable<safe_int_t> m_costSafe;
    nullable<safe_int_t> m_movementRateSafe;
};
#pragma pack()

#pragma pack(1)
class CWeaponParameters : public CInventoryParameters {
public:
    float m_fFixScale;
    bool m_bDropBoxCollider; 
    char pad2[0x3];
    void* m_throwParameters; 
    bool m_bInspectable;
    bool m_bForceTakeAfterPickup; 
    bool m_bInspectableBonus;
    char pad3[0x5];
    void* m_hitDelayParameters; 
    string_t* m_sCustomAnimationName; 
    weapon_id m_iCustomAnimationWeaponId;
    bool m_bIsDroppable;
    char pad4[0x6];
    void* m_customButtonSprite;
    uint8_t m_shootInShiftFireBehaviourType;
    char pad5[0x3];
    uint8_t m_shootInShiftFireAdditionalBehaviourType;
    char pad6[0x3];
    float m_fShootInShiftSpeedMult;
    bool m_bDrawStrecherOnGettingReadyToFire;
    bool m_bHasCancelAimButton;
    uint8_t m_cancelAimBehaviourType;
    uint8_t m_weaponAmmoIconType;
    bool m_bShowHitMarker;
    char pad7[0x3];
    uint8_t m_killType;
    char pad8[0x3];
    nullable<safe_float_t> m_fFixScaleSafe;
    nullable<safe_bool_t> m_bDropBoxColliderSafe;
    nullable<safe_bool_t> m_bInspectableSafe;
    nullable<safe_bool_t> m_bForceTakeAfterPickupSafe;
    nullable<safe_bool_t> m_bInspectableBonusSafe;
    nullable<safe_bool_t> m_bIsDroppableSafe;
    nullable<safe_bool_t> m_bHasCancelAimButtonSafe;
    nullable<safe_bool_t> m_bShowHitMarkerSafe;
    
    weapon_type getType() const noexcept;
    std::string getName() const noexcept;
    char getIcon() const noexcept;
        
};
#pragma pack()

#pragma pack(1)
class CWeaponMaterialController : public C_Component {
public:
    weapon_id m_id;
    char pad2[0x3];
    uint32_t m_iInventoryID;
    CWeaponLodGroup* m_LODGroup;
};
#pragma pack()

#pragma pack(1)
class CWeaponDropController : public C_Component {
char pad[sizeof(void*)];
public:
    C_Component* m_collider;
    void* m_rigidbody; 
    CWeaponParameters* m_parameters;
    void* m_markerTrigger;
    void* m_map;
    void* m_dropParameters;
    void* m_occlusion;
    void* m_soundEmitter;
    void* m_soundEmitter2;
    int32_t m_iIndex; 
    float m_fDropTime;
    void* m_ptr1;
    list_t<void*>* m_lComponents; 
    weapon_id m_id;
    char pad3[0x3];
    int32_t m_iDropID;
    uint32_t m_iInventoryID;
    char pad4[0x4];
    CTransform* m_transform;
    CWeaponLodGroup* m_LODGroup;
    int m_integer1;
    CWeaponDropData* m_dropData;
    uint8_t m_iSlotIndex;
    char pad5[0x7];
    CWeaponMaterialController* m_materialController;
};
#pragma pack()

#pragma pack(1)
class CWeaponDropData {
char pad[sizeof(void*)*2];
public:
    weapon_id m_id;
    char pad2[0x3];
    uint32_t m_iSkinID;
    int16_t m_iOwnerID;
    char pad3[0x2];
    vec3_t m_vecOrigin; 
    euler_angles_t m_vecRotation; 
    vec3_t m_vecVelocity; 
    vec3_t m_vecAngularVelocity; 
    int32_t m_iViewID; 
    int16_t m_iMagazineCapacity; 
    int16_t m_iCapacity; 
};
#pragma pack()