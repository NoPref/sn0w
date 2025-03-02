#pragma once
#include <stdint.h>

#pragma pack(1)
struct safe_float_t {
//char pad[sizeof(void*)*2];
public:
    int32_t m_iSalt;
    int32_t m_iValue;

    float getValue(bool fixed = false) const noexcept;
    void setValue(const float& fValue) noexcept;
};
#pragma pack()

#pragma pack(1)
struct safe_int_t {
//char pad[sizeof(void*)*2];
public:
    int32_t m_iSalt;
    int32_t m_iValue;

    int32_t getValue(bool fixed = false) const noexcept;
    void setValue(const int32_t& iValue, bool _short = false) noexcept;
};
#pragma pack()

#pragma pack(1)
struct safe_bool_t {
//char pad[sizeof(void*)*2];
public:
    int32_t m_iSalt;
    int32_t m_iValue;

    bool getValue(bool fixed = false) const noexcept;
    void setValue(const bool& bValue) noexcept;
};
#pragma pack()

#pragma pack(1)
template<typename T>
struct nullable {
public:
    bool m_bHasValue;
    char pad[0x3];
    T m_value;
};
#pragma pack()