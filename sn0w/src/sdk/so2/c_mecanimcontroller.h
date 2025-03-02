#pragma once
#include <stdint.h>
#include "../unity/common/include.h"

class CPlayerController;
class CPlayerOcclusionController;
class CMecanimLayerInfo;

enum execution_type : uint8_t {
    execution_type_driven       = 0,
    execution_type_synchronized = 1,
    execution_type_not_stated   = 2,
};

#pragma pack(1)
class CMecanimController {
char pad[0x58];
public:
    void* m_ptr1;
    CPlayerController* m_player;
    CPlayerOcclusionController* m_playerOcclusion;
    void* m_animator;
    void* m_ikController;
    void* m_config;
    void* m_sync;
    execution_type m_executionType;
    char pad2[0x7];
    CMecanimLayerInfo* m_layerInfo;
    delegate_t* m_onLateUpdate;
    void* m_listeners;
    delegate_t* m_onShot;
    float m_fMecanimEvaluateTime;
    char pad3[0x4];
    void* m_syncParameters;
};
#pragma pack()

#pragma pack(1)
class CMecanimLayerInfo {
char pad[0x10];
public:
    float m_fTime;
    int32_t m_iLayerID;
    bool m_bIsInTransition;
    char pad2[0x3];
    int32_t m_iStateNameHash;
    float m_fStateNormalizedTime;
    float m_fStateLength;
    float m_fStateEnterTime;
    float m_fStateSpeed;
    float m_fTransitionDurationNT;
    float m_fTransitionDuration;
    int32_t m_iNextStateNameHash;
    int32_t m_iTransitionNameHash;
    float m_fTransitionNormalizedTime;
    float m_fTransitionOffset;
    float m_fTransitionStartTime;
    bool m_bIsSynchronized;
    char pad3[0x3];
    list_t<void*>* m_lBufferParameters;
};
#pragma pack()