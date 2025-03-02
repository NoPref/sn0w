#pragma once
#include <stdint.h>
#include "../singleton.hpp"
#include "../src/sdk/unity/common/t_color.h"
#include "../includes/imgui/include.h"

#define float4toimcolor(col) ImColor(col[0], col[1], col[2], col[3])
#define float3toimcolor(col) ImColor(col[0], col[1], col[2], 1.f)
#define float4toimvec4(col)  ImVec4(col[0], col[1], col[2], col[3])
#define float3toimvec4(col)  ImVec4(col[0], col[1], col[2], 1.f)
#define float4tocolor(col) color_t(col[0], col[1], col[2], col[3])
#define float3tocolor(col) color_t(col[0], col[1], col[2], 1.f)

struct imgui_fonts_t {
public:
    struct ui {
        ImFont* verdana{};
        ImFont* verdana_pages{};
        ImFont* verdana_bold{};
        ImFont* verdana_bold_child{};
        ImFont* verdana_bold_slider{};
        ImFont* verdana_bold_button{};
        ImFont* undefeated{};
        ImFont* undefeated_pages{};
    } ui;
    struct esp {
        ImFont* tahoma{}; //nick
        ImFont* verdana_bold{}; //weapon
        ImFont* verdana_bold_small{}; //dropped weapon
        ImFont* undefeated{}; //weapon
        ImFont* undefeated_bigger{}; //dropped weapon
        ImFont* pixel{}; //healthbar text
    } esp;
    struct other {
        ImFont* lucon{}; //lucida console
        /*ImFont* segoeui{};
        ImFont* segoeui_semi{};
        ImFont* segoeui_bold{};*/

    } other;

    imgui_fonts_t() = default;
    ~imgui_fonts_t() = default;

    void init() noexcept;
};

class CImGuiRenderer : public CSingleton<CImGuiRenderer> {
public:
    imgui_fonts_t m_fonts;
    
    CImGuiRenderer() = default;
    ~CImGuiRenderer() = default;

    void init() noexcept;
    void beginFrame() noexcept;
    void endFrame() noexcept;

    void text(ImDrawList* pDrawlist, const ImVec2& vecCoords, const ImColor& color, const char* const& szText, bool shadow = true, bool outline = false) noexcept;
    void glow(ImDrawList* const pDrawlist, const ImVec2& vecLeftUpper, const ImVec2& vecRightLower, const ImColor& col, const float& fWidth, bool bInner = false) noexcept;
    void glowCircle(ImDrawList* const pDrawlist, const ImVec2& vecCoords, const float& fRadius, const ImColor& col, bool bInner = false) noexcept;
    void box(ImDrawList* pDrawlist, const ImVec2& vecMin, const ImVec2& vecMax, const ImColor& color, bool outline = true, bool corners = false, float roundness = 0.f) noexcept;
    void boxFilled(ImDrawList* pDrawlist, const ImVec2& vecMin, const ImVec2& vecMax, const ImColor& color, float roundness = 0.f) noexcept;
    void line(ImDrawList* pDrawlist, const ImVec2& vecMin, const ImVec2& vecMax, const ImColor& color, float thick = 1.f) noexcept;
    void circle(ImDrawList* pDrawlist, const ImVec2& vecCoords, const float& radius, const ImColor& color, float thick = 1.f) noexcept;
    ImRect progressBar(ImDrawList* pDrawlist, const ImVec2& vecStart, const ImVec2& vecEnd, const ImColor& color, const float& maxValue, const float& curValue, bool outline = true, bool horizontal = false, bool showText = true, const char* format = "%d") noexcept;
};