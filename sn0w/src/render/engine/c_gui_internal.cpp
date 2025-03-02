#include "c_gui_internal.hpp"

void C_GUIStack::clear() noexcept {
    this->m_vecPadding = {};
    this->m_vecCursor = {};
    this->m_vecCurItemSize = {};
    this->m_vecCurWidgetsSize = {};
    this->m_vecCurChildSize = {};
    this->m_vecCurFreeSpace = {};
}