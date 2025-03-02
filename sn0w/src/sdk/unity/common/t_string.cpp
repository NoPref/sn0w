#include "t_string.h"
#include "../globals.hpp"

string_t* string_t::create(const char* const& utf8) noexcept {
    return (string_t*)g.il2cpp.string_new(utf8);
}

std::string string_t::toUTF8() const noexcept {
    std::string ret{};
    if(this->m_iLength > 0 && this->m_aChars != NULL) {
        std::u16string u16str((char16_t*)this->m_aChars,0,this->m_iLength);
        if(!u16str.empty()) {
            const char16_t *p = u16str.data();
            std::u16string::size_type len = u16str.length();
            if(p[0] == 0xFEFF) {
                p+=1;
                len-=1;
            }
            
            ret.reserve(len * 3);

            char16_t u16char;
            for (std::u16string::size_type i = 0; i < len; ++i) {

                u16char = p[i];

                if (u16char < 0x0080) {
                    ret.push_back((char) (u16char & 0x00FF));
                    continue;
                }
                if (u16char >= 0x0080 && u16char <= 0x07FF) {
                    ret.push_back((char) (((u16char >> 6) & 0x1F) | 0xC0));
                    ret.push_back((char) ((u16char & 0x3F) | 0x80));
                    continue;
                }
                if (u16char >= 0xD800 && u16char <= 0xDBFF) {
                    uint32_t highSur = u16char;
                    uint32_t lowSur = p[++i];
                    uint32_t codePoint = highSur - 0xD800;
                    codePoint <<= 10;
                    codePoint |= lowSur - 0xDC00;
                    codePoint += 0x10000;
                    ret.push_back((char) ((codePoint >> 18) | 0xF0));
                    ret.push_back((char) (((codePoint >> 12) & 0x3F) | 0x80));
                    ret.push_back((char) (((codePoint >> 06) & 0x3F) | 0x80));
                    ret.push_back((char) ((codePoint & 0x3F) | 0x80));
                    continue;
                }
                {
                    ret.push_back((char) (((u16char >> 12) & 0x0F) | 0xE0));
                    ret.push_back((char) (((u16char >> 6) & 0x3F) | 0x80));
                    ret.push_back((char) ((u16char & 0x3F) | 0x80));
                    continue;
                }
            }
        }
    }
    return std::move(ret);
}