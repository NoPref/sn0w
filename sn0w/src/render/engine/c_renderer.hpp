#pragma once
#include <stdint.h>
#include "../singleton.hpp"
#include "../unity/common/include.h"
#include "../unity/c_texture.h"
#include "../unity/c_gameobject.h"
#include "../unity/c_gui.h"
#include "../unity/c_assetbundle.h"

class CEngineRenderer : public CSingleton<CEngineRenderer> {
public:
    CTexture2D* m_mainTexture;
    CGameObject* m_object;

    CEngineRenderer() = default;
    ~CEngineRenderer() = default;

    void init() noexcept;

    void line(const vec2_t& vecStart, const vec2_t& vecEnd, const color_t& color, float thickness = 1.f);
    void rect(const vec2_t& vecMin, const vec2_t& vecMax, const color_t& color, float thickness = 1.f, float roundness = 0.f);
    void rectFilled(const vec2_t& vecMin, const vec2_t& vecMax, const color_t& color);
    void circle(const vec2_t& vecCoords, const float& radius, const color_t& color, float thickness = 1.f);
    void text(const vec2_t& vecMin, const vec2_t& vecSize, const color_t& color, const string_t* u16str);
    void text(const vec2_t& vecMin, const vec2_t& vecSize, const color_t& color, const char* const& szText);
    void text(const vec2_t& vecCoords, const color_t& color, const string_t* u16str);
    void text(const vec2_t& vecCoords, const color_t& color, const char* const& szText);
};