#pragma once
#include "../unity/c_transform.h"
#include "common/enums.h"

#pragma pack(1)
class CObjectOccludee {
char pad[0x20];
public:
    array_t<void*>* m_array1;
    CTransform* m_transform;
    bool m_bEnabled;
    bool m_bool1;
    bool m_bool2;
    char pad2[0x1];
    observation_state m_state;
    char pad3[0x3];
    observation_state m_obstructionState;
    char pad4[0x3];
};
#pragma pack()

#pragma pack(1)
class CPlayerOcclusionController : public CObjectOccludee {

};
#pragma pack()