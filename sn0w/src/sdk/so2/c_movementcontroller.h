#pragma once
#include <stdint.h>
#include "../unity/c_transform.h"
#include "../unity/common/include.h"
#include "common/safe_vars.h"

class CPlayerController;
class CPlayerOcclusionController;
class CPlayerTranslationParameters;
class CPlayerTranslationData;
class CMecanimController;
class CJumpParameters;
class C_CrouchParameters;
class CWalkParameters;
class CMovementCmd;

#pragma pack(1)
class CMovementController {
char pad[0x58];
public: 
    CPlayerController* m_player;
    CPlayerOcclusionController* m_playerOcclusion;
    bool m_bNeverIdle;
    char pad2[0x7];
    CTransform* m_movementDirector;
    CMovementCmd* m_cmd;
    float m_fDeltaTime;
    float m_fLocalTime;
    void* m_character;
    void* m_trigger;
    array_t<void*>* m_aListeners;
    void* m_translationStatesMap;
    CPlayerTranslationParameters* m_parameters;
    CPlayerTranslationData* m_data;
    void* m_sync;
    CTransform* m_characterTransform;
    CMecanimController* m_mecanim;
    float m_fLastSnapshotReceivedTime;
    char pad3[0x4];
    list_t<void*>* m_lUnhandledBuffer;
    list_t<void*>* m_lBuffer;
    void* m_lastReceivedEvents;
};
#pragma pack()

#pragma pack(1)
class CMovementCmd {
char pad[sizeof(void*)*2];
public:
    vec3_t m_vecTemp;
    float m_fSideMove;
    float m_fForwardMove;
    bool m_bCrouch;
    bool m_bJump;
};
#pragma pack()

#pragma pack(1)
class CPlayerTranslationParameters {
char pad[sizeof(void*)*2];
public: 
    float m_fSpeedDefault;
    nullable<safe_float_t> m_fSpeedDefaultSafe;
    nullable<safe_float_t> m_fSpeedMultiplierSafe;
    float m_fMoveDirectionChangeSpeed;
    float m_fMecanimDirectionChangeSpeed;
    char pad2[0x4];
    CWalkParameters* m_walkParameters;
    void* m_idleParameters;
    C_CrouchParameters* m_crouchParameters;
    CJumpParameters* m_jumpParameters;
    void* m_characterColliderParameters;
    void* m_generalCurveTypes;
};
#pragma pack()

#pragma pack(1)
class CWalkParameters {
char pad[sizeof(void*)*2];
public:
    float m_fWalkSpeedMultiplier;
    float m_fDefaultAcceleration;
    nullable<safe_float_t> m_fWalkSpeedMultiplierSafe;
};
#pragma pack()

#pragma pack(1)
class C_CrouchParameters {
char pad[sizeof(void*)*2];
public:
    float m_fCrouchSpeedMultiplier;
    float m_fCrouchSpeed;
    void* m_standToCrouchCurve;
    nullable<safe_float_t> m_fCrouchSpeedMultiplierSafe;
};
#pragma pack()

#pragma pack(1)
class CJumpParameters {
char pad[sizeof(void*)*2];
public:
    float m_fUpwardSpeedDefault;
    char pad2[0x4];
    void* m_jumpCurve;
    void* m_landCurve;
    void* m_minSpeedCurve;
    void* m_landDelayCurve;
    void* m_landDelayDurationCurve;
    void* m_landDelayMultCurve;
    void* m_movementStopCurve;
    void* m_yRotationSpeedCurve;
    void* m_yRotationSpeedMultCurve;
    float m_fJumpMoveSpeed;
};
#pragma pack()

#pragma pack(1)
class CPlayerTranslationData {
char pad[sizeof(void*)*2];
public: 
    float m_fTargetSpeed;
    float m_fCurrentSpeed;
    float m_fCurrentSpeedMult;
    vec3_t m_vecTargetDelta;
    vec3_t m_vecPrevDelta;
    float m_fPrevDeltaTime;
    vec3_t m_vecPrev;
    vec3_t m_vecCurrent;
    vec2_t m_vecTargetRelativeDirectionMecanim;
    vec2_t m_vecCurrentRelativeDirectionMecanim;
    vec2_t m_vecFixedRelativeDirectionMecanim;
    vec3_t m_vecMoveDirection;
    float m_fCharacterEulerY;
    float m_float1;
    float m_float2;
    float m_float3;
    char pad2[0x4];
    delegate_t* m_inputFilter;
    void* m_delayCurve;
    float m_fDelayDuration;
    float m_fDelaySetTime;
    float m_fDelayMult;
    euler_angles_t m_prevFrameRotation;
    bool m_bIsVelocitySynchronized;
    char pad3[0x3];
    vec3_t m_vecVelocity;
    blended_value_t<float>* m_fStandTypeCoeff;
    blended_value_t<float>* m_fJumpTypeCoeff;
    vec2_t m_vecTargetRelativeDirection;
    float m_fTargetMecanimDirectionMagnitude;
    char pad4[0x4];
    blended_value_t<vec2_t>* m_vecDampedRelativeDirection;
};
#pragma pack()