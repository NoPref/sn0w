#pragma once
#include "../unity/c_transform.h"
#include "../unity/c_component.h"
#include "common/enums.h"

class CBipedMap;

#pragma pack(1)
class CPlayerCharacterView : public C_Component {
char pad2[sizeof(void*)];
public:
    CTransform* m_transform1;
    CTransform* m_transform2;
    bool m_bool1;
    char pad3[0x7];
    void* m_animator1;
    void* m_skinnedMeshLODGroup1;
    CBipedMap* m_bipedMap;
};
#pragma pack()

#pragma pack(1)
class CBipedMap : public C_Component {
char pad2[sizeof(void*)];
public: 
    CTransform* m_data[bip_max];
    void* m_toolPivot;
    bool m_bIkEnabled;

    CTransform* getBone(const bip& num) noexcept;
};
#pragma pack()