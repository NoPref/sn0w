#include "safe_vars.h"
#include "../globals.hpp"

float safe_float_t::getValue(bool fixed) const noexcept {
    if(!fixed) return (float)(this->m_iValue ^ this->m_iSalt);
    static float(*func)(safe_float_t);
    if(func == NULL)
        func = (decltype(func))(g.lpBase + oxorany(0x230fd94));
    return func(*this);
}

void safe_float_t::setValue(const float& fValue) noexcept {
    this->m_iValue = (int32_t)fValue ^ this->m_iSalt;
}

int32_t safe_int_t::getValue(bool fixed) const noexcept {
    if(!fixed) return (int32_t)(this->m_iValue ^ this->m_iSalt);
    static int32_t(*func)(safe_int_t);
    if(func == NULL)
        func = (decltype(func))(g.lpBase + oxorany(0x2227d30));
    return func(*this);
}

void safe_int_t::setValue(const int32_t& iValue, bool _short) noexcept {
    this->m_iValue = (int32_t)iValue ^ this->m_iSalt;
}

bool safe_bool_t::getValue(bool fixed) const noexcept {
    if(!fixed) return (bool)(this->m_iValue ^ this->m_iSalt);
    static bool(*func)(safe_bool_t);
    if(func == NULL)
        func = (decltype(func))(g.lpBase + oxorany(0x25b4f90));
    return func(*this);
}

void safe_bool_t::setValue(const bool& bValue) noexcept {
    this->m_iValue = (int32_t)bValue ^ this->m_iSalt;
}