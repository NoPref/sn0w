#pragma once
#include <stdint.h>
#include "../singleton.hpp"
#include "../sdk/unity/c_shader.h"
#include "../sdk/unity/c_renderer.h"
#include "../sdk/unity/c_assetbundle.h"

enum chams_material : uint8_t {
    chams_material_solid,
    chams_material_glow,
    chams_material_flat,
    chams_material_glass,
    chams_material_max,
};

class C_Chams : public CSingleton<C_Chams> {
private:
    CShader* m_shaders[chams_material_max];
public:
    C_Chams() = default;
    ~C_Chams() = default;

    static void update() noexcept;

    void applyMaterial(const chams_material& material, CRenderer* const& renderer) noexcept;
    
    void init() noexcept;
    void players() noexcept;
    void localplayer() noexcept;
    void localWeapon() noexcept;
    void arms() noexcept;
};