#pragma once
#include <stdint.h>
#include "t_vec2.h"
#include "t_vec3.h"

enum touch_phase : uint8_t {
    touch_phase_began      = 0,
    touch_phase_moved      = 1,
    touch_phase_stationary = 2,
    touch_phase_ended      = 3,
    touch_phase_canceled   = 4,
};

enum touch_type : uint8_t {
    touch_type_direct   = 0,
    touch_type_indirect = 1,
    touch_type_stylus   = 2,
};

#pragma pack(1)
struct touch_t {
public:
    int32_t m_iFingerID;
    vec2_t m_vecCoords; 
    vec2_t m_vecRawCoords; 
    vec2_t m_vecCoordsDelta; 
    float m_fTimeDelta; 
    int32_t m_iTapCount; 
    touch_phase m_phase;
    char pad[0x3];
    touch_type m_type; 
    char pad2[0x3];
    float m_fPressure; 
    float m_fMaximumPossiblePressure;
    float m_fRadius; 
    float m_fRadiusVariance; 
    float m_fAltitudeAngle; 
    float m_fAzimuthAngle;

    touch_t() = default;
    ~touch_t() = default;

    static touch_t getTouch(const uint8_t& index) noexcept;
};
#pragma pack()
