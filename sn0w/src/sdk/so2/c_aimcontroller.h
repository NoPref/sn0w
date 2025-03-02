#pragma once
#include <stdint.h>
#include "../unity/c_transform.h"
#include "common/enums.h"
#include "common/structs.h"

enum aim_type : uint8_t {
	aim_type_target = 0,
	aim_type_delta  = 1,
};

enum weapon_offset_state : uint8_t {
	weapon_offset_state_not_stated  = 0,
	weapon_offset_state_translation = 1,
};

enum move_state : uint8_t {
	move_state_not_stated      = 0,
	move_state_crouch          = 1,
	move_state_stand           = 2,
	move_state_finished_crouch = 3,
	move_state_finished_stand  = 4,
};

class CPlayerController;
class CMovementController;
class CMecanimController;
class CWeaponryController;
class CAimingData;

#pragma pack(1)
class CAimController {
char pad[0x53];
public:
    bool m_bOverrideSpineRotation;
    observation_state m_observationState; 
    char pad2[0x3];
    float m_fSensitivityX; 
    float m_fSensitivityY; 
    float m_fMinimumX; 
    float m_fMaximumX;
    CTransform* m_FPSP; 
    CTransform* m_spineDirector; 
    CTransform* m_FPSCamera; 
    CTransform* m_camTransform; 
    void* m_parameters; 
    CAimingData* m_data; 
    void* m_interpolatorsBunch; 
    void* m_tuningParams;
    float m_fHeadDampingSpeed;
    char pad3[0x4];
    CPlayerController* m_player;
    CMovementController* m_movement;
    CTransform* m_movementDirector;
    CMecanimController* m_mecanim;
    CTransform* m_helper;
    bool m_bIsGpOffsetInitialized;
    char pad4[0x7];
    void* m_commands;
    state_simple_t<view_mode>* m_viewMode;
    euler_angles_t m_angCurSpineAim;
    char pad5[0x4];
    state_simple_t<weapon_offset_state>* m_weaponOffsetState;
    state_simple_t<move_state>* m_moveState;
    transform_tr_t* m_weaponDirOnStand;
    transform_tr_t* m_weaponDirOnCrouch;
    void* m_pose1;
    void* m_pose2;
    void* m_pose3;
    void* m_pose4;
    void* m_pose5;
    void* m_weaponAnimationPars;
    void* m_syncData;
    delegate_t* m_action;
    bool m_bool1;
    char pad6[0x3];
    float m_float1;
    float m_float2;
    void* m_ptr1;
    float m_float3;
    float m_float4;
    array_t<void*>* m_array1;
    CWeaponryController* m_weaponry;
    quaternion_t m_quaternion1;
    bool m_bToolPivotTuning;
    bool m_bSpineRotation;
    char pad7[0x2];
    euler_angles_t m_angles1;
    euler_angles_t m_angles2;
    euler_angles_t m_angles3;
    void* m_pose6;
};
#pragma pack()

#pragma pack(1)
class CAimingData {
char pad[sizeof(void*)*2];
public: 
    float m_fCurWTCoeff;
    float m_fCurMTCoeff;
    euler_angles_t m_angPitch;
    euler_angles_t m_angYaw;
    transform_tr_t* m_gunSubstitude;
    float m_fCurrentSpineZAxisOffset;
    float m_fStandTypeCoeff;
};
#pragma pack()
