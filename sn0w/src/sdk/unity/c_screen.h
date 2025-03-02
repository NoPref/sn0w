#pragma once
#include <stdint.h>

struct resolution_t {
    int32_t m_iWidth;
    int32_t m_iHeight;

    resolution_t() = default;
    ~resolution_t() = default;
    resolution_t(const int32_t& w, const int32_t& h) {
        this->m_iWidth = w;
        this->m_iHeight = h;
    }
};

class CScreen {
public:
    static resolution_t getResolution() noexcept;
    static void setResolution(const int32_t& w, const int32_t& h) noexcept;
    static void setResolution(const resolution_t& res) noexcept;
};