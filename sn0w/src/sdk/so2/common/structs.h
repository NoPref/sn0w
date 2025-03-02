#pragma once
#include "../unity/common/include.h"

template<typename T>
struct state_simple_t {
    char pad[sizeof(void*)*2];
    public:
        T m_curState;
        T m_prevState;
        float m_fTimeSwitched;
        bool m_bIsJustSwitched;
        int m_iStateNo;
};

template<typename T>
struct blended_value_t {
    char pad[sizeof(void*)*2];
    public:
        T m_actual;
        T m_actualPrevFrame;
        T m_blended;
        T m_previous;
        float m_fTimeFix;
        float m_fBlendDuration;
};

struct transform_tr_t {
    char pad[0x8];

    public:
        vec3_t m_vecPos;
        euler_angles_t m_angRot;
};

struct transform_trs_t {
    char pad[0x8];

    public:
        vec3_t m_vecPos;
        euler_angles_t m_angRot;
        vec3_t m_vecScale;
};