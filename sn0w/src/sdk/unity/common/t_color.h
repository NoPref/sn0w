#pragma once

struct color_t {
    float r, g, b, a;

    color_t() = default;
    ~color_t() = default;

    color_t(const float& _r, const float& _g, const float& _b, float _a = 1.f) {
        this->r = _r;
        this->g = _g;
        this->b = _b;
        this->a = _a;
    }
};