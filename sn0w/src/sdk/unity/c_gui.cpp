#include "c_gui.h"
#include "../globals.hpp"

int32_t rect_offset_t::getLeft() const noexcept {
    static int32_t(*func)(const rect_offset_t*);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("RectOffset"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_left"), 0)->methodPointer;
    return func(this);
}

void rect_offset_t::setLeft(const int32_t& v) noexcept {
    static void(*func)(rect_offset_t*,int32_t);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("RectOffset"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("set_left"), 1)->methodPointer;
    func(this, v);
}

int32_t rect_offset_t::getRight() const noexcept {
    static int32_t(*func)(const rect_offset_t*);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("RectOffset"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_right"), 0)->methodPointer;
    return func(this);
}
void rect_offset_t::setRight(const int32_t& v) noexcept {
    static void(*func)(rect_offset_t*,int32_t);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("RectOffset"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("set_right"), 1)->methodPointer;
    func(this, v);
}

int32_t rect_offset_t::getTop() const noexcept {
    static int32_t(*func)(const rect_offset_t*);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("RectOffset"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_top"), 0)->methodPointer;
    return func(this);
}

void rect_offset_t::setTop(const int32_t& v) noexcept {
    static void(*func)(rect_offset_t*,int32_t);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("RectOffset"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("set_top"), 1)->methodPointer;
    func(this, v);
}

int32_t rect_offset_t::getBottom() const noexcept {
    static int32_t(*func)(const rect_offset_t*);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("RectOffset"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_bottom"), 0)->methodPointer;
    return func(this);
}

void rect_offset_t::setBottom(const int32_t& v) noexcept {
    static void(*func)(rect_offset_t*,int32_t);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("RectOffset"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("set_bottom"), 1)->methodPointer;
    func(this, v);
}

CFont* CFont::loadFromPath(const char* const& szPath, const char* const& szFontName) noexcept {
    static CAssetBundle* bundle{};
    if(bundle == NULL)
        bundle = CAssetBundle::loadFromFileAsync(szPath)->getAssetBundle();

    static type_t* fontType{};
    if(fontType == NULL)
        fontType = type_t::find(oxorany("UnityEngine.Font, UnityEngine.TextRenderingModule.dll"));

    return (CFont*)(bundle->loadAssetAsync(szFontName, fontType)->getAsset());
}

rect_offset_t* CGUIStyle::getPadding() noexcept {
    static rect_offset_t*(*func)(CGUIStyle*);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("GUIStyle"), oxorany("UnityEngine"), oxorany("UnityEngine.IMGUIModule.dll")), oxorany("get_padding"), 0)->methodPointer;
    return func(this);
}

CFont* CGUIStyle::getFont() noexcept {
    static CFont*(*func)(CGUIStyle*);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("GUIStyle"), oxorany("UnityEngine"), oxorany("UnityEngine.IMGUIModule.dll")), oxorany("get_font"), 0)->methodPointer;
    return func(this);
}

void CGUIStyle::setFont(CFont* const& font) noexcept {
    static void(*func)(CGUIStyle*, CFont*);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("GUIStyle"), oxorany("UnityEngine"), oxorany("UnityEngine.IMGUIModule.dll")), oxorany("set_font"), 1)->methodPointer;
    func(this, font);
}

void CGUIStyle::setFontSize(const int32_t& size) noexcept {
    static void(*func)(CGUIStyle*, int32_t);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("GUIStyle"), oxorany("UnityEngine"), oxorany("UnityEngine.IMGUIModule.dll")), oxorany("set_fontSize"), 1)->methodPointer;
    func(this, size);
}

float CGUIStyle::getFontHeight() const noexcept {
    static float(*func)(const CGUIStyle*);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("GUIStyle"), oxorany("UnityEngine"), oxorany("UnityEngine.IMGUIModule.dll")), oxorany("get_lineHeight"), 0)->methodPointer;
    return func(this);
}

void CGUIStyle::setTextAlign(const text_align& align) noexcept {
    static void(*func)(CGUIStyle*, text_align);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("GUIStyle"), oxorany("UnityEngine"), oxorany("UnityEngine.IMGUIModule.dll")), oxorany("set_alignment"), 1)->methodPointer;
    func(this, align);
}

void CGUISkin::setFont(CFont* const& font) noexcept {
    static void(*func)(CGUISkin*,CFont*);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("GUISkin"), oxorany("UnityEngine"), oxorany("UnityEngine.IMGUIModule.dll")), oxorany("set_font"), 1)->methodPointer;
    func(this, font);
}

CGUIContent* CGUIContent::create(const char* const& szText) noexcept {
    static CGUIContent*(*func)(string_t*);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("GUIContent"), oxorany("UnityEngine"), oxorany("UnityEngine.IMGUIModule.dll")), oxorany("Temp"), 1)->methodPointer;
    static CGUIContent* ret{};
    if(ret == NULL)
        ret = func(string_t::create(szText));
    return ret;
}

CGUISkin* CGUI::getSkin() noexcept {
    static CGUISkin*(*func)();
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("GUI"), oxorany("UnityEngine"), oxorany("UnityEngine.IMGUIModule.dll")), oxorany("get_skin"), 0)->methodPointer;
    return func();
}

void CGUI::setSkin(CGUISkin* skin) noexcept {
    static void(*func)(CGUISkin*);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("GUI"), oxorany("UnityEngine"), oxorany("UnityEngine.IMGUIModule.dll")), oxorany("set_skin"), 1)->methodPointer;
    func(skin);
}

color_t CGUI::getColor() noexcept {
    static color_t(*func)();
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("GUI"), oxorany("UnityEngine"), oxorany("UnityEngine.IMGUIModule.dll")), oxorany("get_color"), 0)->methodPointer;
    return func();
}

void CGUI::setColor(const color_t& color) noexcept {
    static void(*func)(color_t);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("GUI"), oxorany("UnityEngine"), oxorany("UnityEngine.IMGUIModule.dll")), oxorany("set_color"), 1)->methodPointer;
    func(color);
}

void CGUI::drawTexture(const rect_t& rect, const CTexture* const& texture) noexcept {
    static void(*func)(rect_t,const CTexture*);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("GUI"), oxorany("UnityEngine"), oxorany("UnityEngine.IMGUIModule.dll")), oxorany("DrawTexture"), 2)->methodPointer;
    func(rect, texture);
}

void CGUI::drawTexture(const rect_t& rect, const CTexture* const& texture, const uint8_t& mode, const bool& alphaBlend, const float& aspect, const color_t& color, const float& width, const float& round) noexcept {
    static void(*func)(rect_t,const CTexture*,uint8_t,bool,float,color_t,float,float);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("GUI"), oxorany("UnityEngine"), oxorany("UnityEngine.IMGUIModule.dll")), oxorany("DrawTexture"), 8)->methodPointer;
    func(rect, texture, mode, alphaBlend, aspect, color, width, round);
}

void CGUI::drawTexture(const rect_t& rect, const CTexture* const& texture, const color_t& colLeft, const color_t& colTop, const color_t& colRight, const color_t& colBottom, const rect_t& widths, const rect_t& rounds) noexcept {
    static void(*func)(rect_t,const CTexture*, uint8_t, bool, float, color_t, color_t, color_t, color_t, rect_t, rect_t, bool);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("GUI"), oxorany("UnityEngine"), oxorany("UnityEngine.IMGUIModule.dll")), oxorany("DrawTexture"), 12)->methodPointer;
    func(rect, texture, 0, true, 1.f, colLeft, colTop, colRight, colBottom, widths, rounds, true);
}

void CGUI::drawLabel(const rect_t& rect, const string_t* const& label) noexcept {
    static void(*func)(rect_t,const string_t*);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("GUI"), oxorany("UnityEngine"), oxorany("UnityEngine.IMGUIModule.dll")), oxorany("Label"), 2)->methodPointer;
    func(rect, label);
}

bool CGUI::button(const rect_t& rect, const string_t* const& label) noexcept {
    static bool(*func)(rect_t,const string_t*);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("GUI"), oxorany("UnityEngine"), oxorany("UnityEngine.IMGUIModule.dll")), oxorany("Button"), 2)->methodPointer;
    return func(rect, label);
}

bool CGUI::toggle(const rect_t& rect, bool value, CGUIContent* content, CGUIStyle* style) noexcept {
    static bool(*func)(rect_t,bool,CGUIContent*,CGUIStyle*);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("GUI"), oxorany("UnityEngine"), oxorany("UnityEngine.IMGUIModule.dll")), oxorany("Toggle"), 4)->methodPointer;
    return func(rect, value, content, style);
}

float CGUI::horizontalSlider(const rect_t& rect, float value, const float& min, const float& max, CGUIStyle* slider, CGUIStyle* thumb) noexcept {
    static float(*func)(rect_t,float,float,float,CGUIStyle*,CGUIStyle*);
    if(func == NULL)    
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("GUI"), oxorany("UnityEngine"), oxorany("UnityEngine.IMGUIModule.dll")), oxorany("HorizontalSlider"), 6)->methodPointer;
    return func(rect, value, min, max, slider, thumb);
}