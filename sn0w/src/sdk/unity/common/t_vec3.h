#pragma once
#include <math.h>

struct vec3_t {
public:
    float x;
    float y;
    float z;

    vec3_t() = default;
    vec3_t(const float& _x, const float& _y, const float& _z) noexcept {
        this->x = _x;
        this->y = _y;
        this->z = _z;
    }
    ~vec3_t() = default;
    
    vec3_t operator+(const vec3_t& vec) const noexcept {
        return vec3_t {
            this->x + vec.x,
            this->y + vec.y,
            this->z + vec.z
        };
    }
    vec3_t operator+(const float& _f) const noexcept {
        return vec3_t {
            this->x + _f,
            this->y + _f,
            this->z + _f
        };
    }
    vec3_t& operator+=(const vec3_t& vec) noexcept {
        *this = *this + vec;
        return *this;
    }
    vec3_t& operator+=(const float& _f) noexcept {
        *this = *this + _f;
        return *this;
    }

    vec3_t operator-(const vec3_t& vec) const noexcept {
        return vec3_t {
            this->x - vec.x,
            this->y - vec.y,
            this->z - vec.z
        };
    }
    vec3_t operator-(const float& _f) const noexcept {
        return vec3_t {
            this->x - _f,
            this->y - _f,
            this->z - _f
        };
    }
    vec3_t& operator-=(const vec3_t& vec) noexcept {
        *this = *this - vec;
        return *this;
    }
    vec3_t& operator-=(const float& _f) noexcept {
        *this = *this - _f;
        return *this;
    }

    vec3_t operator*(const vec3_t& vec) const noexcept {
        return vec3_t {
            this->x * vec.x,
            this->y * vec.y,
            this->z * vec.z
        };
    }
    vec3_t operator*(const float& _f) const noexcept {
        return vec3_t {
            this->x * _f,
            this->y * _f,
            this->z * _f
        };
    }
    vec3_t& operator*=(const vec3_t& vec) noexcept {
        *this = *this * vec;
        return *this;
    }
    vec3_t& operator*=(const float& _f) noexcept {
        *this = *this * _f;
        return *this;
    }

    vec3_t operator/(const vec3_t& vec) const noexcept {
        return vec3_t {
            this->x / vec.x,
            this->y / vec.y,
            this->z / vec.z
        };
    }
    vec3_t operator/(const float& _f) const noexcept {
        return vec3_t {
            this->x / _f,
            this->y / _f,
            this->z / _f
        };
    }
    vec3_t& operator/=(const vec3_t& vec) noexcept {
        *this = *this / vec;
        return *this;
    }
    vec3_t& operator/=(const float& _f) noexcept {
        *this = *this / _f;
        return *this;
    }

    bool operator==(const vec3_t& vec) const noexcept {
        return this->x == vec.x && this->y == vec.y && this->z == vec.z;
    }
    bool operator!=(const vec3_t& vec) const noexcept {
        return !(*this == vec);
    }

    bool isEmpty() const noexcept {
        return !this->x && !this->y && !this->z;
    }

    float sqrMagnitude() const noexcept {
        return (this->x * this->x) + (this->y * this->y) + (this->z * this->z);
    }

    float magnitude() const noexcept {
        return sqrtf(this->sqrMagnitude());
    }

    float distanceTo(const vec3_t& vec) const noexcept {
        return (*this - vec).magnitude();
    }

    void normalize() noexcept {
        const float fMagnitude = this->magnitude();
        if(fMagnitude != 0.f)
            *this /= fMagnitude;
    }

    vec3_t normalized() noexcept {
        vec3_t ret = *this;
        ret.normalize();
        return ret;
    }

    float dot(const vec3_t& vec) const noexcept {
        return (this->x * vec.x) + (this->y * vec.y) + (this->z * vec.z);
    }

};
    