#include "t_delegate.h"
#include "../globals.hpp"

void delegate_t::hook(void* hk, void** origin) noexcept {
    if(*origin == NULL)
        *origin = this->m_pInvokeImpl;
    this->m_pInvokeImpl = hk;
}