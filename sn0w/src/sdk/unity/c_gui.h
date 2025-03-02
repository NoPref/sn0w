#pragma once
#include <stdint.h>
#include "common/include.h"
#include "c_texture.h"

enum text_align : uint8_t {
	text_align_upper_left    = 0,
	text_align_upper_center  = 1,
	text_align_upper_right   = 2,
	text_align_middle_left   = 3,
	text_align_middle_center = 4,
	text_align_middle_right  = 5,
	text_align_lower_left    = 6,
	text_align_lower_center  = 7,
	text_align_lower_right   = 8,
};

struct rect_offset_t : public CObject {
public:
    int32_t getLeft() const noexcept;
    void setLeft(const int32_t& v) noexcept;
    int32_t getRight() const noexcept;
    void setRight(const int32_t& v) noexcept;
    int32_t getTop() const noexcept;
    void setTop(const int32_t& v) noexcept;
    int32_t getBottom() const noexcept;
    void setBottom(const int32_t& v) noexcept;
};  

class CFont {
public:
    static CFont* loadFromPath(const char* const& szPath, const char* const& szFontName) noexcept;
};

#pragma pack(1)
class CGUIStyle {
char pad[sizeof(void*)*2];
public:
    unsigned long long m_ptr;
	void* m_normal; 
	void* m_hover;
	void* m_active; 
	void* m_focused; 
	void* m_onNormal; 
	void* m_onHover; 
	void* m_onActive; 
	void* m_onFocused; 
	rect_offset_t* m_border;
	rect_offset_t* m_padding;
	rect_offset_t* m_margin;
	rect_offset_t* m_overflow;
	string_t* m_Name;

    rect_offset_t* getPadding() noexcept;

    CFont* getFont() noexcept;
    void setFont(CFont* const& font) noexcept;
    void setFontSize(const int32_t& size) noexcept;
    float getFontHeight() const noexcept;

    void setTextAlign(const text_align& align) noexcept;

};
#pragma pack()

#pragma pack(1)
class CGUISkin {
char pad[sizeof(void*)*3];
public:
    CFont* m_font;
    CGUIStyle* m_box;
    CGUIStyle* m_button;
    CGUIStyle* m_toggle;
    CGUIStyle* m_label;
    CGUIStyle* m_textField;
    CGUIStyle* m_textArea;
    CGUIStyle* m_window;
    CGUIStyle* m_horizontalSlider;
    CGUIStyle* m_horizontalSliderThumb;
    CGUIStyle* m_horizontalSliderThumbExtent;
    CGUIStyle* m_verticalSlider;
    CGUIStyle* m_verticalSliderThumb;
    CGUIStyle* m_verticalSliderThumbExtent;
    CGUIStyle* m_sliderMixed;
    CGUIStyle* m_horizontalScrollbar;
    CGUIStyle* m_horizontalScrollbarThumb;
    CGUIStyle* m_horizontalScrollbarLeftButton;
    CGUIStyle* m_horizontalScrollbarRightButton;
    CGUIStyle* m_verticalScrollbar;
    CGUIStyle* m_verticalScrollbarThumb;
    CGUIStyle* m_verticalScrollbarUpButton;
    CGUIStyle* m_verticalScrollbarDownButton;
    CGUIStyle* m_scrollView;
    array_t<CGUIStyle*>* m_aCustomStyles;
    void* m_settings;
    dictionary_t<string_t*, CGUIStyle*> m_dStyles;

    void setFont(CFont* const& font) noexcept;
};
#pragma pack()

#pragma pack(1)
class CGUIContent {
char pad[sizeof(void*)*2];
public:
    string_t* m_text;
    CTexture* m_image;
    string_t* m_tooltip;
    void* m_onTextChanged;
    
    static CGUIContent* create(const char* const& szText) noexcept;
};
#pragma pack()

class CGUI {
public:
    static CGUISkin* getSkin() noexcept;
    static void setSkin(CGUISkin* skin) noexcept;
    static color_t getColor() noexcept;
    static void setColor(const color_t& color) noexcept;
    static void drawTexture(const rect_t& rect, const CTexture* const& texture) noexcept;
    static void drawTexture(const rect_t& rect, const CTexture* const& texture, const uint8_t& mode, const bool& alphaBlend, const float& aspect, const color_t& color, const float& width, const float& round) noexcept;
    static void drawTexture(const rect_t& rect, const CTexture* const& texture, const color_t& colLeft, const color_t& colTop, const color_t& colRight, const color_t& colBottom, const rect_t& widths, const rect_t& rounds) noexcept;
    static void drawLabel(const rect_t& rect, const string_t* const& label) noexcept;
    static bool button(const rect_t& rect, const string_t* const& label) noexcept;
    static bool toggle(const rect_t& rect, bool value, CGUIContent* content, CGUIStyle* style) noexcept;
    static float horizontalSlider(const rect_t& rect, float value, const float& min, const float& max, CGUIStyle* slider, CGUIStyle* thumb) noexcept;
};