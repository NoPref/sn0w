#pragma once
#include <stdint.h>
#include "c_renderer.hpp"

enum gui_style_color : uint32_t {
    gui_style_color_window,
    gui_style_color_child,
    gui_style_color_child_border,
    gui_style_color_border,
    gui_style_color_text,
    gui_style_color_button,
    gui_style_color_button_a,
    gui_style_color_checkbox,
    gui_style_color_checkbox_a,
    gui_style_color_max,
};

enum gui_style_padding : uint32_t {
    gui_style_padding_window,
    gui_style_padding_child,
    gui_style_padding_item,
    gui_style_padding_max,
};

enum gui_window_flag : uint32_t {
    gui_window_flag_none,
    gui_window_flag_movable,
    gui_window_flag_scalable,
    gui_window_flag_no_title,
    gui_window_flag_no_border,
    gui_window_flag_max,
};

enum gui_child_flag : uint32_t {
    gui_child_flag_none,
    gui_child_flag_no_border,
    gui_child_flag_no_background,
};

enum gui_style_size : uint32_t {
    gui_style_size_global,
    gui_style_size_checkbox,
    gui_style_size_slider,
    gui_style_size_resize,
    gui_style_size_max,
};

class C_GUIStyle {
public:
    float m_fBorderSize;
    float m_fChildBorderSize;
    CFont* m_pFont;
    color_t m_aColors[gui_style_color_max];
    vec2_t m_aPaddings[gui_style_padding_max];
    float m_aSizes[gui_style_size_max];
    
    C_GUIStyle() = default;
    ~C_GUIStyle() = default;

    C_GUIStyle& operator=(C_GUIStyle&) = default;

    void setDefaultStyle() noexcept;
};