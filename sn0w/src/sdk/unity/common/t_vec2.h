#pragma once
#include <math.h>

struct vec2_t {
public:
    float x;
    float y;

    vec2_t() = default;
    vec2_t(const float& _x, const float& _y) noexcept {
        this->x = _x;
        this->y = _y;
    }
    ~vec2_t() = default;
    
    vec2_t operator+(const vec2_t& vec) const noexcept {
        return vec2_t {
            this->x + vec.x,
            this->y + vec.y
        };
    }
    vec2_t operator+(const float& _f) const noexcept {
        return vec2_t {
            this->x + _f,
            this->y + _f
        };
    }
    vec2_t& operator+=(const vec2_t& vec) noexcept {
        *this = *this + vec;
        return *this;
    }
    vec2_t& operator+=(const float& _f) noexcept {
        *this = *this + _f;
        return *this;
    }

    vec2_t operator-(const vec2_t& vec) const noexcept {
        return vec2_t {
            this->x - vec.x,
            this->y - vec.y
        };
    }
    vec2_t operator-(const float& _f) const noexcept {
        return vec2_t {
            this->x - _f,
            this->y - _f
        };
    }
    vec2_t& operator-=(const vec2_t& vec) noexcept {
        *this = *this - vec;
        return *this;
    }
    vec2_t& operator-=(const float& _f) noexcept {
        *this = *this - _f;
        return *this;
    }

    vec2_t operator*(const vec2_t& vec) const noexcept {
        return vec2_t {
            this->x * vec.x,
            this->y * vec.y
        };
    }
    vec2_t operator*(const float& _f) const noexcept {
        return vec2_t {
            this->x * _f,
            this->y * _f
        };
    }
    vec2_t& operator*=(const vec2_t& vec) noexcept {
        *this = *this * vec;
        return *this;
    }
    vec2_t& operator*=(const float& _f) noexcept {
        *this = *this * _f;
        return *this;
    }

    vec2_t operator/(const vec2_t& vec) const noexcept {
        return vec2_t {
            this->x / vec.x,
            this->y / vec.y
        };
    }
    vec2_t operator/(const float& _f) const noexcept {
        return vec2_t {
            this->x / _f,
            this->y / _f
        };
    }
    vec2_t& operator/=(const vec2_t& vec) noexcept {
        *this = *this / vec;
        return *this;
    }
    vec2_t& operator/=(const float& _f) noexcept {
        *this = *this / _f;
        return *this;
    }

    bool operator==(const vec2_t& vec) const noexcept {
        return this->x == vec.x && this->y == vec.y;
    }
    bool operator!=(const vec2_t& vec) const noexcept {
        return !(*this == vec);
    }

    bool isEmpty() const noexcept {
        return !this->x && !this->y;
    }

    float sqrMagnitude() const noexcept {
        return (this->x * this->x) + (this->y * this->y);
    }

    float magnitude() const noexcept {
        return sqrtf(this->sqrMagnitude());
    }

    float distanceTo(const vec2_t& vec) const noexcept {
        return (*this - vec).magnitude();
    }

    void normalize() noexcept {
        const float fMagnitude = this->magnitude();
        if(fMagnitude != 0.f)
            *this /= fMagnitude;
    }

    vec2_t normalized() noexcept {
        vec2_t ret = *this;
        ret.normalize();
        return ret;
    }

};
    