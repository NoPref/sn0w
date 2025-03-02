#pragma once
#include "common/t_vec3.h"

struct bounds_t {
public:
    vec3_t m_vecCenter;
    vec3_t m_vecExtents;

    vec3_t getMin() const noexcept {
        return this->m_vecCenter - this->m_vecExtents;
    }

    vec3_t getMax() const noexcept {
        return this->m_vecCenter + this->m_vecExtents;
    }

    vec3_t getSize() const noexcept {
        return this->m_vecExtents*2;
    }
};