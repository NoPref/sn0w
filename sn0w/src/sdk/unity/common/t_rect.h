#pragma once
#include "t_vec2.h"

struct rect_t {
public:
    union {
        struct {
            float x, y, w, h;
        };
        vec2_t min;
        vec2_t max;
    };

    rect_t() = default;
    ~rect_t() = default;
    rect_t(const float& _x, const float& _y, const float& _w, const float& _h) {
        this->x = _x;
        this->y = _y;
        this->w = _w;
        this->h = _h;
    }
    rect_t(const vec2_t& _xy, const vec2_t& _wh) {
        this->x = _xy.x;
        this->y = _xy.y;
        this->w = _wh.x;
        this->h = _wh.y;
    }
};