#include "c_gui_style.hpp"

void C_GUIStyle::setDefaultStyle() noexcept {
    this->m_fBorderSize = 5.f;
    this->m_fChildBorderSize = 2.f;

    this->m_pFont = NULL;

    this->m_aColors[gui_style_color_window]       = color_t{0.08f, 0.08f, 0.08f, 1.f};
    this->m_aColors[gui_style_color_child]        = color_t{0.13f, 0.13f, 0.13f, 1.f};
    this->m_aColors[gui_style_color_child_border] = color_t{0.08f, 0.08f, 0.08f, 1.f};
    this->m_aColors[gui_style_color_border]       = color_t{0.18f, 0.18f, 0.18f, 1.f};
    this->m_aColors[gui_style_color_text]         = color_t{1.f, 1.f, 1.f, 1.f};
    this->m_aColors[gui_style_color_button]       = color_t{0.15f, 0.15f, 0.15f, 1.f};
    this->m_aColors[gui_style_color_button_a]     = color_t{0.12f, 0.12f, 0.12f, 1.f};
    this->m_aColors[gui_style_color_checkbox]     = color_t{0.15f, 0.15f, 0.15f, 1.f};
    this->m_aColors[gui_style_color_checkbox_a]   = color_t{1.f, 1.f, 1.f, 1.f};

    this->m_aPaddings[gui_style_padding_window]   = vec2_t{10.f, 10.f};
    this->m_aPaddings[gui_style_padding_child]    = vec2_t{10.f, 10.f};
    this->m_aPaddings[gui_style_padding_item]     = vec2_t{5.f, 5.f};

    this->m_aSizes[gui_style_size_global]   = 1.f;
    this->m_aSizes[gui_style_size_checkbox] = 20.f;
    this->m_aSizes[gui_style_size_slider]   = 20.f;
    this->m_aSizes[gui_style_size_resize]   = 50.f;
}