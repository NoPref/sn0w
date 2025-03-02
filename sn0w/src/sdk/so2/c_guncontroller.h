#pragma once
#include "../unity/c_transform.h"
#include "common/structs.h"
#include "safe_vars.h"
#include "c_weaponcontroller.h"

enum shooting_state : uint8_t {
	shooting_state_not_stated    = 0,
	shooting_state_stopped       = 2,
	shooting_state_loop_shooting = 3,
};

enum gun_state : uint8_t {
    gun_state_reloading     = 0,
    gun_state_pre_reloading = 1,
    gun_state_switching     = 2,
    gun_state_try_to_switch = 3,
    gun_state_ready         = 4,
};

enum aiming_mode : uint8_t {
    aiming_mode_aiming        = 0,
    aiming_mode_aiming_reload = 1,
    aiming_mode_not_aiming    = 2,
    aiming_mode_start_aiming  = 3,
    aiming_mode_finish_aiming = 4,
};

enum sight_type : uint8_t {
    sight_type_default          = 0,
    sight_type_collimator_sight = 1,
    sight_type_sniper_scope     = 2,
};

enum rifle_type : uint8_t {
    rifle_type_not_stated     = 0,
    rifle_type_bolt_type      = 1,
    rifle_type_semi_automatic = 2,
    rifle_type_automatic      = 3,
};

enum bullet_trace_type : uint8_t {
	bullet_trace_type_pistol 	   = 0,
	bullet_trace_type_heavy_pistol = 1,
	bullet_trace_type_smg 		   = 2,
	bullet_trace_type_rifle 	   = 3,
	bullet_trace_type_sniper       = 4,
	bullet_trace_type_submachine   = 5,
	bullet_trace_type_snow_gun 	   = 6,
};

enum reload_type : uint8_t {
	reload_type_magazine     = 0,
	reload_type_single_round = 1,
};

enum ammunition_type : uint8_t {
	ammunition_type_cartridge 	  = 0,
	ammunition_type_shotgun_shell = 1,
};

enum muzzle_type : uint8_t {
	muzzle_type_single = 0,
	muzzle_type_double = 1,
};

enum muzzle_flash_type : int8_t {
	muzzle_flash_type_none    = -1,
	muzzle_flash_type_pistol  = 0,
	muzzle_flash_type_smg     = 1,
	muzzle_flash_type_rifle   = 2,
	muzzle_flash_type_sniper  = 3,
	muzzle_flash_type_shotgun = 4,
};

enum surface_type : uint8_t {
	surface_type_unknown              = 0,
	surface_type_glass                = 1,
	surface_type_cardboard            = 2,
	surface_type_metal_grate          = 3,
	surface_type_wood                 = 4,
	surface_type_plaster              = 5,
	surface_type_tile                 = 6,
	surface_type_metal                = 7,
	surface_type_concrete             = 8,
	surface_type_brick                = 9,
	surface_type_solid_metal          = 10,
	surface_type_thin_metal           = 11,
	surface_type_thin_wood            = 12,
	surface_type_character            = 13,
	surface_type_ground               = 14,
	surface_type_surface_mark_trigger = 15,
	surface_type_snow_concrete        = 16,
	surface_type_snow_metal           = 17,
	surface_type_snow_ground          = 18,
	surface_type_solid_metal_no_hole  = 19,
	surface_type_gravel               = 20,
	surface_type_grass                = 21,
	surface_type_paper                = 22,
	surface_type_water                = 23,
	surface_type_glass_waterfall      = 24,
	surface_type_wood_solid           = 25,
};

class CGunParameters;
class CRecoilData;
class CShootEventData;
class CSingleShotData;
class CSurfaceHit;
class CBulletHitData;
class CDamage;
class CAmmunition;

#pragma pack(1)
class CGunController : public CWeaponController {
public:
    safe_float_t m_fFireIntervalSafe;
    safe_float_t m_fTimeFiredSafe;
    int32_t m_iShotID;
    int32_t m_iAudioSourceIndex;
    safe_int_t m_iCapacitySafe;
    safe_int_t m_iMagazineCapacitySafe;
    safe_bool_t m_bInfinityAmmoSafe; 
    safe_bool_t m_bInfinityMagazineSafe; 
    CRecoilData* m_recoilData;
    void* m_soundController;
    shooting_state m_shootingState;
    char pad8[0x7];
    void* m_unknown3;
    void* m_recoilControl;
    CGunParameters* m_parameters;
    void* m_sightViewControl;
    float m_fLastHandledShotTime;
    float m_fLastShotSoundPlayedTime;
    void* m_syncData;
    state_simple_t<gun_state>* m_state;
    state_simple_t<aiming_mode>* m_aimingMode;
    list_t<CShootEventData*>* m_lShotBuffer;
    list_t<CShootEventData*>* m_lUnhandledShotBuffer;
    CTransform* m_cameraTransform;
    CTransform* m_muzzlePoint;
    CTransform* m_muzzlePoint2;
    void* m_soundParameters;
    float m_fSwitchAnimConfirmDuration;
    float m_fReloadAnimConfirmDuration;
    int32_t m_iCurrentMuzzleIndex;
    safe_float_t m_fRadiusSafe;
    safe_float_t m_fMinRandomDegreeSafe; 
    safe_float_t m_fMaxRandomDegreeSafe;
    bool m_bool1;
    char pad9[0x3];
    float m_fAccuracyAdditive;
    char pad10[0x4];
    void* m_accuracyData;
    dictionary_t<void*, list_t<CBulletHitData*>*>* m_dCharacterHits; 
    dictionary_t<void*, list_t<CSurfaceHit*>*>* m_dSurfaceHits;
    float m_fRecoilMult;
    float m_fAccuracyMult;
    float m_fReloadCycle;
    bool m_bIsRoundTaken;
    char pad11[0x3];
    void* m_action1;
};
#pragma pack()

#pragma pack(1)
class CGunParameters : public CWeaponParameters {
public:
    sight_type m_sightType;
    char pad2[0x3];
    bool m_bDrawDefaultRecoilLinesNotInAiming;
    rifle_type m_rifleType; 
    bullet_trace_type m_bulletTraceType; 
    reload_type m_reloadType; 
    ammunition_type m_ammunitionType; 
    char pad3[0x7];
    void* m_shotgunShellParameters; 
    muzzle_type m_muzzleType; 
    bool m_bCombineMeshInIdle; 
    char pad4[0x2];
    float m_fScopeAimSensitivityMult;
    CAmmunition* m_ammunition;
    CDamage* m_damage; 
    float m_fHitRange;
    int32_t m_iFireRate;
    int32_t m_iRecoilControl;
    char pad5[0x4];
    void* m_recoilParameters; 
    void* m_accuracyAdditiveCurve; 
    float m_fAccuracyMultOnJump; 
    char pad6[0x4];
    void* m_additiveNoAimDispertionCurve; 
    float m_fRecoilMultOnCrouch; 
    float m_fAccuracyMultOnCrouch; 
    float m_fRecoilAimMult; 
    float m_fAccuracyAimMult; 
    float m_fRecoilAimMultOnCrouch; 
    float m_fAccuracyAimMultOnCrouch; 
    int32_t m_iAccurateRange; 
    char pad7[0x4];
    void* m_sightViewParameters; 
    float m_fArmorPenetration; 
    int32_t m_iPenetrationPower; 
    float m_fReloadDuration;
    float m_fRoundInsertDuration; 
    float m_fReloadStartOffset; 
    float m_fRoundInsertOffset; 
    int32_t m_iVisibleCartridgeCount; 
    float m_fMagazineInsertTime; 
    float m_fTakeDuration; 
    float m_fPreReloadTime; 
    int32_t m_iImpulse;
    muzzle_flash_type m_muzzleFlashType;
    char pad8[0x3];
    nullable<safe_float_t> m_fFireRateSafe; 
    nullable<safe_float_t> m_fScopeAimSensitivityMultSafe; 
    nullable<safe_float_t> m_fAccuracyMultOnJumpSafe; 
    nullable<safe_float_t> m_fRecoilMultOnCrouchSafe; 
    nullable<safe_float_t> m_fAccuracyMultOnCrouchSafe; 
    nullable<safe_float_t> m_fRecoilAimMultSafe; 
    nullable<safe_float_t> m_fAccuracyAimMultSafe; 
    nullable<safe_float_t> m_fRecoilAimMultOnCrouchSafe; 
    nullable<safe_float_t> m_fAccuracyAimMultOnCrouchSafe; 
    nullable<safe_int_t> m_iRecoilControlSafe; 
    nullable<safe_int_t> m_iAccurateRangeSafe; 
    nullable<safe_float_t> m_fArmorPenetrationSafe; 
    nullable<safe_int_t> m_iPenetrationPowerSafe; 
    nullable<safe_float_t> m_fReloadDurationSafe; 
    nullable<safe_float_t> m_fReloadStartOffsetSafe; 
    nullable<safe_float_t> m_fRoundInsertOffsetSafe; 
    nullable<safe_float_t> m_fRoundInsertDurationSafe; 
    nullable<safe_float_t> m_fMagazineInsertTimeSafe; 
    nullable<safe_float_t> m_fTakeDurationSafe; 
    nullable<safe_float_t> m_fPreReloadTimeSafe; 
    nullable<safe_int_t> m_iImpulseSafe; 
    nullable<safe_float_t> m_fHitRangeSafe; 
    nullable<safe_bool_t> m_bCombineMeshInIdleSafe; 
    nullable<safe_int_t> m_iVisibleCartridgeCountSafe; 
    nullable<safe_bool_t> m_bDrawDefaultRecoilLinesNotInAimingSafe; 
};
#pragma pack()

#pragma pack(1)
class CRecoilData {
char pad[sizeof(void*)*2];
public:
    euler_angles_t m_angAimPunch;
    vec2_t m_vecRelativeDispersion;
};
#pragma pack()

#pragma pack(1)
class CSurfaceHit {
char pad[sizeof(void*)*2];
public:
    vec3_t m_vecPoint;
    vec3_t m_vecNormal;
    surface_type m_surfaceType;
};
#pragma pack()

#pragma pack(1)
class CSingleShotData {
char pad[sizeof(void*)*2];
public:
    vec3_t m_vecStartPoint;
    vec3_t m_vecEndPoint;
    array_t<CSurfaceHit*>* m_aSurfaceHits;
};
#pragma pack()

#pragma pack(1)
class CShootEventData {
char pad[sizeof(void*)*2];
public:
    uint8_t m_iEventType;
    char pad2[0x3];
    float m_fEventTime;
    array_t<CSingleShotData*>* m_aShots;
};
#pragma pack()

#pragma pack(1)
class CBulletHitData {
char pad[sizeof(void*)*2];
public:
    vec3_t m_vecShotPoint;
    vec3_t m_vecPoint;
    float m_fImpulse;
    int m_iDamage;
    float m_fArmorPenetration;
    bip m_bip;
    char pad2[0x3];
    bool m_bPenetrated;
};
#pragma pack()

#pragma pack(1)
class CAmmunition {
char pad[sizeof(void*)*2];
public:
    int16_t m_iMagazineCapacity;
    int16_t m_iCapacity;
    nullable<safe_int_t> m_iMagazineCapacitySafe;
    nullable<safe_int_t> m_iCapacitySafe;
};
#pragma pack()

#pragma pack(1)
class CDamage {
char pad[sizeof(void*)*2];
public:
    int32_t m_iHeadDamage;
    int32_t m_iChestAndArmsDamage;
    int32_t m_iStomachDamage;
    int32_t m_iLegsDamage;
    void* m_distanceDamageMult;
};
#pragma pack()