#pragma once
#include <string>
#include <stdint.h>

struct string_t {
char pad[sizeof(void*)*2];
public:
    int32_t m_iLength;
    char m_aChars[0];

    static string_t* create(const char* const& utf8) noexcept;
    std::string toUTF8() const noexcept;
};