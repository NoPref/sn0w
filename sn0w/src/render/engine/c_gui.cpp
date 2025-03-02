#include <cmath>
#include "c_gui.hpp"
#include "../globals.hpp"

void C_GUIBase::create(const char* szTitle, bool bOpen, vec2_t pos, vec2_t size, uint32_t flags) noexcept {
    strncpy(this->m_szTitle, szTitle, sizeof(this->m_szTitle));
    this->m_bActive = false;
    this->m_bOpened = bOpen;
    this->m_vecPos = pos;
    this->m_vecSize = size;
    this->m_flags = (gui_window_flag)flags;
}

void C_GUIManager::handleTouches() noexcept {
    static bool firstTouchFlag{};
    static bool resizing{};

    if(g.hooks.orig.engine.getTouchCount() > 0) {
        const touch_t touch = touch_t::getTouch(0);
        vec2_t touchPos = touch.m_vecCoords;
        touchPos.y = (g.window.m_iHeight - touchPos.y);
        this->m_vecTouch = touchPos;

        vec2_t deltaTouchPos = touch.m_vecCoordsDelta;
        deltaTouchPos.y -= deltaTouchPos.y*2;
        this->m_vecDeltaTouch = deltaTouchPos;

        if(touch.m_phase == touch_phase_began || touch.m_phase == touch_phase_stationary) {
            this->m_bTouched = true;
        } else if(touch.m_phase == touch_phase_canceled || touch.m_phase == touch_phase_ended) {
            this->m_bTouched = false;
        }

        if(this->m_bTouched) {
            if(!firstTouchFlag) {
                firstTouchFlag = true;
                this->m_vecClickTouch = this->m_vecTouch;
            }
        } else 
            firstTouchFlag = false;

        if(this->m_pCurrentMenu != NULL) {
            
            if(this->m_bClampSize) {
                if(this->m_pCurrentMenu->m_vecSize.x < 100)
                    this->m_pCurrentMenu->m_vecSize.x = 100;
                if(this->m_pCurrentMenu->m_vecSize.y < 100)
                    this->m_pCurrentMenu->m_vecSize.y = 100;
            }

            if(this->m_pCurrentMenu->m_bActive) {
                
                if(this->m_pCurrentMenu->m_flags & gui_window_flag_scalable) {
                    const vec2_t vecClick = this->m_vecClickTouch;
                    const vec2_t vecPos = this->m_pCurrentMenu->m_vecPos;
                    const vec2_t vecSize = this->m_pCurrentMenu->m_vecSize;
                    const vec2_t vecResize = vec2_t{1.f, 1.f} * this->m_style.m_aSizes[gui_style_size_resize];
                    if(this->isTouchInArea(vecClick, vecPos + (vecSize - vecResize), vecResize)) {
                        resizing = true;
                    }
                    if(resizing) {
                        const vec2_t vecSet = this->m_pCurrentMenu->m_vecSize + this->m_vecDeltaTouch;
                        if(vecSet.x >= 100 && vecSet.y >= 100)
                            this->m_pCurrentMenu->m_vecSize = vecSet;
                    }
                }

                if(this->m_pCurrentMenu->m_flags & gui_window_flag_movable && !resizing)
                    this->m_pCurrentMenu->m_vecPos += this->m_vecDeltaTouch;
                
            }
        }

    } else {
        this->m_bTouched = false;
        firstTouchFlag = false;
        resizing = false;
    }
}

bool C_GUIManager::isTouchInArea(const vec2_t& touch, const vec2_t& pos, const vec2_t& size) noexcept {
    return 
        touch.x >= pos.x && touch.y >= pos.y &&
        touch.x <= (pos.x + size.x) && touch.y <= (pos.y + size.y);
}

float C_GUIManager::getFontHeight() noexcept {
    return CGUI::getSkin()->m_label->getFontHeight();
}

void C_GUIRenderer::init() noexcept {
    this->man = C_GUIManager::inst();
    this->engine.init();
    this->initFonts();
}

void C_GUIRenderer::initFonts() noexcept {
    const char* const szAssetPath = "/data/data/com.axlebolt.standoff2/files/asset1";
    this->m_fonts.verdana      = CFont::loadFromPath(szAssetPath, oxorany("verdana"));
    this->m_fonts.verdana_bold = CFont::loadFromPath(szAssetPath, oxorany("verdanab"));
    this->m_fonts.undefeated   = CFont::loadFromPath(szAssetPath, oxorany("undefeated"));
    this->m_fonts.tahoma       = CFont::loadFromPath(szAssetPath, oxorany("tahoma"));
    this->m_fonts.pixel        = CFont::loadFromPath(szAssetPath, oxorany("04b03"));
    this->m_fonts.lucon        = CFont::loadFromPath(szAssetPath, oxorany("lucon"));
}

vec2_t C_GUIRenderer::getSpace() const noexcept {
    return this->man->m_stack.m_vecCurFreeSpace;
}

void C_GUIRenderer::sameLine() noexcept {
    C_GUIStack& stack = this->man->m_stack;
    stack.m_vecCursor.x += stack.m_vecCurItemSize.x;
    stack.m_vecCursor.y -= stack.m_vecCurItemSize.y;
}

void C_GUIRenderer::setFont(CFont* const& font, uint8_t size) noexcept {
    CGUISkin* skin = CGUI::getSkin();
    skin->m_font = font;
    skin->m_label->setFont(font);
    skin->m_label->setFontSize(size);
    skin->m_label->getPadding()->setLeft(0);
    skin->m_label->getPadding()->setRight(0);
    skin->m_label->getPadding()->setTop(0);
    skin->m_label->getPadding()->setBottom(0);
    //CGUI::setSkin(skin);
}

void C_GUIRenderer::setTextAlign(const text_align& align) noexcept {
    CGUISkin* skin = CGUI::getSkin();
    skin->m_label->setTextAlign(align);
}

void C_GUIRenderer::beginWindow(C_GUIBase& gui) noexcept {
    C_GUIStyle& style = this->man->m_style;
    C_GUIStack& stack = this->man->m_stack;

    //drawing
    this->engine.rectFilled(gui.m_vecPos, gui.m_vecPos + gui.m_vecSize, style.m_aColors[gui_style_color_window]);

    if(!(gui.m_flags & gui_window_flag_no_border)) {
        const vec2_t border = vec2_t{style.m_fBorderSize, style.m_fBorderSize} / 2;
        const vec2_t min = gui.m_vecPos - border;
        const vec2_t max = gui.m_vecPos + gui.m_vecSize + border;
        this->engine.rect(min, max, style.m_aColors[gui_style_color_border], style.m_fBorderSize);
    }
    
    //logic
    if(this->man->m_bTouched && !this->man->m_bTouchItem) {
        if(this->man->isTouchInArea(this->man->m_vecClickTouch, gui.m_vecPos, gui.m_vecSize))
            gui.m_bActive = true;
    } else gui.m_bActive = false;

    if(gui.m_bActive)
        this->man->m_pCurrentMenu = &gui;

    //add to stack
    stack.m_vecPadding += style.m_aPaddings[gui_style_padding_window];
    stack.m_vecCursor += style.m_aPaddings[gui_style_padding_window];
    stack.m_vecCurItemSize = gui.m_vecSize;
    stack.m_vecCurFreeSpace = gui.m_vecSize - (style.m_aPaddings[gui_style_padding_window] * 2);
    this->m_pCurrentMenu = &gui;
}

void C_GUIRenderer::endWindow() noexcept {
    C_GUIStyle& style = this->man->m_style;
    C_GUIStack& stack = this->man->m_stack;

    this->man->m_stack.clear();
    this->m_pCurrentMenu = NULL;
}

void C_GUIRenderer::beginChild(vec2_t size, uint32_t flags) noexcept {
    C_GUIStyle& style = this->man->m_style;
    C_GUIStack& stack = this->man->m_stack;

    if(size.x <= 0)
        size.x = this->getSpace().x;
    if(size.y <= 0)
        size.y = this->getSpace().y;

    vec2_t min = this->m_pCurrentMenu->m_vecPos + stack.m_vecCursor;
    vec2_t max = (min + size);

    //drawing
    if(!(flags & gui_child_flag_no_background)) {
        this->engine.rectFilled(min, max, style.m_aColors[gui_style_color_child]);
    }
    
    if(!(flags & gui_child_flag_no_border)) {
        const vec2_t border = vec2_t{style.m_fChildBorderSize, style.m_fChildBorderSize} / 2;
        min -= border;
        max += border;
        this->engine.rect(min, max, style.m_aColors[gui_style_color_child_border], style.m_fChildBorderSize);
    }

    //add to stack
    stack.m_vecPadding += style.m_aPaddings[gui_style_padding_child];
    stack.m_vecCursor += style.m_aPaddings[gui_style_padding_child];
    stack.m_vecCurItemSize = max - min;
    stack.m_vecCurChildSize = max - min;
    stack.m_vecCurFreeSpace = (max - min) - (style.m_aPaddings[gui_style_padding_child] * 2);
}

void C_GUIRenderer::endChild() noexcept {
    C_GUIStyle& style = this->man->m_style;
    C_GUIStack& stack = this->man->m_stack;

    stack.m_vecPadding -= style.m_aPaddings[gui_style_padding_child];
    stack.m_vecCursor.x = stack.m_vecPadding.x;
    stack.m_vecCursor.y += stack.m_vecCurChildSize.y;
    stack.m_vecCurChildSize = {};
    stack.m_vecCurWidgetsSize = {};
    stack.m_vecCurFreeSpace = this->m_pCurrentMenu->m_vecSize - ((stack.m_vecPadding + stack.m_vecCursor) - vec2_t{style.m_fBorderSize / 2, 0});
}

void C_GUIRenderer::label(const char* const& text) noexcept {
    C_GUIStyle& style = this->man->m_style;
    C_GUIStack& stack = this->man->m_stack;
    
    const vec2_t labelSize = vec2_t{0, this->man->getFontHeight()};
    const vec2_t pos = this->m_pCurrentMenu->m_vecPos + stack.m_vecCursor + stack.m_vecCurWidgetsSize;

    this->engine.text(pos, style.m_aColors[gui_style_color_text], text);

    stack.m_vecCurWidgetsSize.y += labelSize.y + style.m_aPaddings[gui_style_padding_item].y;
}

bool C_GUIRenderer::button(const char* const& text, vec2_t size) noexcept {
    bool ret{};
    C_GUIStyle& style = this->man->m_style;
    C_GUIStack& stack = this->man->m_stack;

    if(size.x <= 0)
        size.x = this->getSpace().x;
    if(size.y <= 0)
        size.y = 40.f;
    
    const vec2_t min = this->m_pCurrentMenu->m_vecPos + stack.m_vecCursor + stack.m_vecCurWidgetsSize;
    const vec2_t max = min + size;

    CGUI::setColor(color_t{});
    ret = CGUI::button(rect_t{min.x, min.y, size.x, size.y}, string_t::create(""));

    this->engine.rectFilled(min, max, (ret ? style.m_aColors[gui_style_color_button_a] : style.m_aColors[gui_style_color_button]));
    this->setTextAlign(text_align_middle_center);
    this->engine.text(min, size, style.m_aColors[gui_style_color_text], text);
    this->setTextAlign(text_align_upper_left);
    this->engine.rect(min, max,style.m_aColors[gui_style_color_border], 1.f);
    
    stack.m_vecCurWidgetsSize.y += size.y + style.m_aPaddings[gui_style_padding_item].y;

    return ret;
}

void C_GUIRenderer::checkbox(const char* const& text, bool& value) noexcept {
    C_GUIStyle& style = this->man->m_style;
    C_GUIStack& stack = this->man->m_stack;

    const float size = style.m_aSizes[gui_style_size_checkbox];

    vec2_t min = this->m_pCurrentMenu->m_vecPos + stack.m_vecCursor + stack.m_vecCurWidgetsSize + vec2_t{0, size/4};
    vec2_t max = min + (size/2);
    this->engine.rectFilled(min, max, (value ? style.m_aColors[gui_style_color_checkbox_a] : style.m_aColors[gui_style_color_checkbox]));
    this->engine.text(vec2_t{max.x + style.m_aPaddings[gui_style_padding_item].x, min.y - (size/3)}, style.m_aColors[gui_style_color_text], text);

    min -= vec2_t{0, size/4};
    max = min + size;
    CGUI::setColor(color_t{});
    value = CGUI::toggle(rect_t{min.x, min.y, max.x - min.x, max.y - min.y}, value, CGUIContent::create(oxorany("")), CGUI::getSkin()->m_toggle);

    stack.m_vecCurWidgetsSize.y += size + style.m_aPaddings[gui_style_padding_item].y;
}

void C_GUIRenderer::sliderfloat(const char* const& text, float& fValue, const float& fMin, const float& fMax) noexcept {
    C_GUIStyle& style = this->man->m_style;
    C_GUIStack& stack = this->man->m_stack;

    vec2_t min = this->m_pCurrentMenu->m_vecPos + stack.m_vecCursor + stack.m_vecCurWidgetsSize;

    this->engine.text(min, style.m_aColors[gui_style_color_text], text);
    min.y += CGUI::getSkin()->m_label->getFontHeight() + style.m_aPaddings[gui_style_padding_item].y;

    const vec2_t max = min + vec2_t{this->getSpace().x, 10.f};

    this->engine.rectFilled(min, max, color_t{0.1f,0.1f,0.1f});

    const vec2_t norm = {min.x + (((fValue - fMin) / (fMax - fMin)) * (max.x - min.x)), max.y};
    this->engine.rectFilled(min, norm - vec2_t{1.f, 0.f}, color_t{1.f,1.f,1.f});

    CGUIStyle* gstyle = CGUI::getSkin()->m_label;
    CGUI::setColor(color_t{});
    fValue = CGUI::horizontalSlider(rect_t{min.x, min.y, max.x - min.x, max.y - min.y}, fValue, fMin, fMax, gstyle, gstyle);

    if(this->man->m_bTouched && this->man->isTouchInArea(this->man->m_vecClickTouch, min, max - min)) {
        this->man->m_bTouchItem = true;
    } else if(!this->man->m_bTouched) {
        this->man->m_bTouchItem = false;
    }

    stack.m_vecCurWidgetsSize.y += (max.y - min.y) + style.m_aPaddings[gui_style_padding_item].y + CGUI::getSkin()->m_label->getFontHeight() + 10.f;
}