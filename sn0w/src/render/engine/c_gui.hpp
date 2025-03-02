#pragma once
#include <stdint.h>
#include <string.h>
#include "c_renderer.hpp"
#include "c_gui_style.hpp"
#include "c_gui_internal.hpp"
#include "../singleton.hpp"

/*render via engine*/
//бля тут такая хуйня это пиздец просто,ну я давно писал еще хотел через юнити рендерить и в итоге забил на эту хуйню
//ну в принципе если доделать то +- норм будет

//window base
class C_GUIBase {
public:
    char m_szTitle[32];
    bool m_bActive;
    bool m_bOpened;
    vec2_t m_vecPos;
    vec2_t m_vecSize;
    gui_window_flag m_flags;
    uint8_t m_nChilds;

    void create(const char* szTitle, bool bOpen = true, vec2_t pos = {}, vec2_t size = {200, 200}, uint32_t flags = 0) noexcept;

    C_GUIBase() = default;
    C_GUIBase(const char* szTitle, bool bOpen = true, vec2_t pos = {}, vec2_t size = {200, 200}, uint32_t flags = 0) {
        this->create(szTitle, bOpen, pos, size, flags);
    }
};

//managing stuff
class C_GUIManager : public CSingleton<C_GUIManager> {
public:
    vec2_t m_vecTouch{};
    vec2_t m_vecDeltaTouch{};
    vec2_t m_vecClickTouch{};
    bool m_bTouched{};
    bool m_bTouchItem{};
    bool m_bClampSize = true;
    C_GUIStack m_stack{};
    C_GUIStyle m_style{};
    C_GUIBase* m_pCurrentMenu{};
    
    void handleTouches() noexcept;
    static bool isTouchInArea(const vec2_t& touch, const vec2_t& pos, const vec2_t& size) noexcept;

    static float getFontHeight() noexcept;
};

//drawing
class C_GUIRenderer : public CSingleton<C_GUIRenderer> {

struct fonts_t {
public:
    CFont* verdana{};
    CFont* verdana_bold{};
    CFont* undefeated{};
    CFont* tahoma{};
    CFont* pixel{}; 
    CFont* lucon{};
};

public:
    fonts_t m_fonts;
    C_GUIBase* m_pCurrentMenu;
    C_GUIManager* man;
    CEngineRenderer engine;

    void init() noexcept;
    void initFonts() noexcept;

    vec2_t getSpace() const noexcept;
    void sameLine() noexcept;

    void setFont(CFont* const& font, uint8_t size = 18) noexcept;
    void setTextAlign(const text_align& align) noexcept;

    void beginWindow(C_GUIBase& gui) noexcept;
    void endWindow() noexcept;

    void beginChild(vec2_t size = {}, uint32_t flags = 0) noexcept;
    void endChild() noexcept;

    void label(const char* const& text) noexcept;
    bool button(const char* const& text, vec2_t size = {}) noexcept;
    void checkbox(const char* const& text, bool& value) noexcept;
    void sliderfloat(const char* const& text, float& fValue, const float& fMin, const float& fMax) noexcept;
};