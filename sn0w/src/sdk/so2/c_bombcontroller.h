#pragma once
#include <cstdint>
#include "../unity/c_component.h"
#include "../unity/c_transform.h"
#include "../unity/common/include.h"
#include "common/structs.h"
#include "safe_vars.h"
#include "c_weaponcontroller.h"

enum bomb_state : uint8_t {
	bomb_state_none = 0,
	bomb_state_planting = 1,
	bomb_state_switching = 2,
	bomb_state_try_to_switch = 3,
	bomb_state_ready = 4,
};

class CBombParameters;

#pragma pack(1)
class CBombController : public CWeaponController {
public:
    state_simple_t<bomb_state>* m_state;
    float m_fProgress;
    char pad7[0x4];
    void* m_map;
    CBombParameters* m_parameters;
};
#pragma pack()

#pragma pack(1)
class CPlantedBombController : public C_Component {
char pad[sizeof(void*)];
public:
    CBombParameters* m_parameters;
    void* m_extendedParameters;
    void* m_particleSystem;
    CTransform* m_mainCamera;
    void* m_bombIndicator;
    float m_fBeepInterval;
    int32_t m_iBeepStateIndex;
    delegate_t* m_beepHandler;
    void* m_soundParameters;
    void* m_beepSoundEmitter;
    void* m_detonatedSoundEmitter;
    void* m_FPSDefusedSoundEmitter;
    void* m_emitter1;
    void* m_emitter2;
    void* m_occlusionController;
    void* m_occlusionController2;
    CWeaponLodGroup* m_LODGroup;
    void* m_ptr1;
    bool m_bIsPlanted;
    bool m_bIsDetonated;
    bool m_bIsDefused;
    char pad2[0x1];
    double m_fPlantServerTime;
    float m_fPlantTime;
    CTransform* m_transform;
};
#pragma pack()

#pragma pack(1)
class CBombParameters : public CWeaponParameters {
public:
    float m_fPlantDuration; 
    float m_fDetonationDuration;
    float m_fDamageRadius;
    float m_fDamage; 
    float m_fTakeDuration;
    char pad6[0x4];
    void* m_damageCurve; 
    void* m_armorPenetrationCurve; 
    float m_fImpulse; 
    char pad7[0x4];
    transform_tr_t* m_spine2Offset;
    bool m_bDummyOnly;
    char pad8[0x3];
    nullable<safe_float_t> m_fPlantDurationSafe; 
    nullable<safe_float_t> m_fDetonationDurationSafe; 
    nullable<safe_float_t> m_fDamageRadiusSafe; 
    nullable<safe_float_t> m_fDamageSafe; 
    nullable<safe_float_t> m_fTakeDurationSafe; 
    nullable<safe_float_t> m_fImpulseSafe; 
};
#pragma pack()