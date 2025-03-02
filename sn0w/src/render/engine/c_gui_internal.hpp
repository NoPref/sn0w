#pragma once
#include <stdint.h>
#include "c_gui_style.hpp"
#include "../sdk/unity/common/include.h"

class C_GUIStack {
public:
    vec2_t m_vecPadding;
    vec2_t m_vecCursor;
    vec2_t m_vecCurItemSize;
    vec2_t m_vecCurWidgetsSize;
    vec2_t m_vecCurChildSize;
    vec2_t m_vecCurFreeSpace;

    C_GUIStack() = default;
    ~C_GUIStack() = default;

    void clear() noexcept;
};