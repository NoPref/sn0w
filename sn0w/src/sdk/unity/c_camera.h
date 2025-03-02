#pragma once
#include <stdint.h>
#include "common/include.h"
#include "c_component.h"

enum camera_clear_flags : uint8_t {
    camera_clear_flags_none,
    camera_clear_flags_skybox,
    camera_clear_flags_color,
    camera_clear_flags_solid_color,
    camera_clear_flags_depth,
    camera_clear_flags_nothing,
};

class C_Camera : public C_Component {
public:
    static matrix4x4_t m_viewMatrix;
    static matrix4x4_t m_projMatrix;
    
    float getFOV() const noexcept;
    void setFOV(const float& fValue) noexcept;
    static C_Camera* getMain() noexcept;
    static C_Camera* getCurrent() noexcept;
    matrix4x4_t getViewMatrix() const noexcept;
    matrix4x4_t getProjectionMatrix() const noexcept;
    static vec3_t w2s(const vec3_t& vecOrigin) noexcept;
    static vec3_t w2s_clamped(const vec3_t& vecOrigin) noexcept;
    camera_clear_flags getFlags() const noexcept;
    void setFlags(const camera_clear_flags& flags) noexcept;
    void setBackgroundColor(const color_t& color) noexcept;
};