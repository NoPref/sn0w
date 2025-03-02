#pragma once
#include "../unity/c_transform.h"
#include "../unity/c_component.h"
#include "../photonengine/c_photonplayer.h"
#include "common/structs.h"
#include "common/safe_vars.h"
#include "c_weaponcontroller.h"

enum grenade_state : uint8_t {
	grenade_state_equipped       = 1,
	grenade_state_switching      = 2,
	grenade_state_try_to_switch  = 3,
	grenade_state_ready          = 4,
	grenade_state_ready_to_throw = 5,
	grenade_state_thrown         = 6,
	grenade_state_throwing       = 7,
};

enum dropped_grenade_state : uint8_t {
	dropped_grenade_state_thrown     = 0,
	dropped_grenade_state_stopped    = 1,
	dropped_grenade_state_not_stated = 2,
	dropped_grenade_state_detonated  = 3,
};

enum grenade_detonation_type : uint8_t {
	grenade_detonation_type_by_timer   = 0,
	grenade_detonation_type_after_stop = 1,
	grenade_detonation_type_one_hit    = 2,
};

class CGrenadeParameters;

#pragma pack(1)
class CGrenadeController : public CWeaponController {
public:
    vec3_t m_vec1;
    char pad7[0x4];
    state_simple_t<grenade_state>* m_state;
    CGrenadeParameters* m_grenadeParameters;
    bool m_bPrevFireCmd;
    bool m_bPrevAimCmd;
    char pad8[0x2];
    float m_fLastFireCmdTime;
    safe_bool_t m_bIsUnlimitedSafe;
    void* m_unknown;
    void* m_soundController;
    CGameObject* m_gameobject1;
    CGameObject* m_gameobject2;
    bool m_bool1;
    bool m_bool2;
    bool m_bool3;
    bool m_bool4;
    char pad9[0x4];
    void* m_tracerArc;
    void* m_fullTracerArcSrc;
    bool m_bool5;
    bool m_bool6;
    char pad10[0x2];
    int32_t m_integer1;
    int32_t m_integer2;
};
#pragma pack()

#pragma pack(1)
class CGrenadeParameters : public CWeaponParameters {
public:
    float m_fTakeDuration;
    float m_fThrowDuration;
    float m_fNearThrowDuration;
    bool m_bThrowByTap;
    char pad5[0x3];
    void* m_nearThrowParameters;
    void* m_farThrowParameters;
    void* m_ballisticParameters;
    void* m_ballisticRotationParameters;
    vec3_t m_vecScaleOnThrow;
    grenade_detonation_type m_detonationType;
    char pad6[0x3];
    float m_fDetonationDuration;
    float m_fDamageRadius; 
    int32_t m_iDamage;
    int32_t m_iPenetrationPower; 
    float m_fArmorPenetration;
    int32_t m_iImpulse;
    void* m_damageCurve;
    float m_fBackToPoolDelay;
    bool m_bUnlimited;
    char pad7[0x3];
    CGameObject* m_effectEmitter1;
    CGameObject* m_effectEmitter2;
    CGameObject* m_effectEmitterTPS1;
    CGameObject* m_effectEmitterTPS2;
    string_t* m_sDescription;
    bool m_bCountKillToStats;
    uint8_t m_grenadeStatsFormatKeyType;
    nullable<safe_float_t> m_fTakeDurationSafe;
    nullable<safe_float_t> m_fThrowDurationSafe;
    nullable<safe_float_t> m_fNearThrowDurationSafe;
    nullable<safe_bool_t> m_bThrowByTapSafe;
    nullable<safe_float_t> m_fDetonationDurationSafe;
    nullable<safe_float_t> m_fDamageRadiusSafe;
    nullable<safe_int_t> m_iDamageSafe;
    nullable<safe_int_t> m_iPenetrationPowerSafe;
    nullable<safe_int_t> m_fArmorPenetrationPowerSafe;
    nullable<safe_int_t> m_iImpulseSafe;
    nullable<safe_int_t> m_fBackToPoolDelaySafe;
    nullable<safe_int_t> m_bUnlimitedSafe;
    nullable<safe_int_t> m_bCountKillToStatsSafe;
    void* m_greandeStatsFormatKeyTypeSafe;
};
#pragma pack()

#pragma pack(1)
class CDroppedGrenadeController : public C_Component {
char pad[sizeof(void*)];
public:
    list_t<void*>* m_list1;
    list_t<void*>* m_list2;
    CGrenadeParameters* m_parameters;
    void* m_soundParameters;
    CTransform* m_transform;
    void* m_map;
    CWeaponLodGroup* m_LODGroup;
    CWeaponMaterialController* m_materialController;
    void* m_patternController;
    float m_fTimeStamp;
    char pad3[0x4];
    dropped_grenade_state m_state;
    char pad4[0x3];
    float m_fThrowTime;
    CPhotonPlayer* m_owner;
    void* m_soundEmmiter;
    void* m_ptr1;
    nullable<void*> m_physicCollisionData;
    weapon_id m_id;
    char pad5[0x7];
    CGameObject* m_gameobject1;
    CGameObject* m_gameobject2;
    void* m_raycastPhysicsController;
    vec3_t m_vec1;
    vec3_t m_vec2;
    team m_ownerTeam;
    char pad6[0x3];
    vec3_t m_vecThrow;
};
#pragma pack()