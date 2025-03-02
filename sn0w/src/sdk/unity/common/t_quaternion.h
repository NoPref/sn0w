#pragma once
#include <math.h>

struct quaternion_t {
public:
    float x;
    float y;
    float z;
    float w;

    quaternion_t() = default;
    quaternion_t(const float& _x, const float& _y, const float& _z, const float& _w) noexcept {
        this->x = _x;
        this->y = _y;
        this->z = _z;
        this->w = _w;
    }
    ~quaternion_t() = default;
    
    quaternion_t operator+(const quaternion_t& q) const noexcept {
        return quaternion_t {
            this->x + q.x,
            this->y + q.y,
            this->z + q.z,
            this->w + q.w
        };
    }
    quaternion_t operator+(const float& _f) const noexcept {
        return quaternion_t {
            this->x + _f,
            this->y + _f,
            this->z + _f,
            this->w + _f
        };
    }
    quaternion_t& operator+=(const quaternion_t& q) noexcept {
        *this = *this + q;
        return *this;
    }
    quaternion_t& operator+=(const float& _f) noexcept {
        *this = *this + _f;
        return *this;
    }

    quaternion_t operator-(const quaternion_t& q) const noexcept {
        return quaternion_t {
            this->x - q.x,
            this->y - q.y,
            this->z - q.z,
            this->w - q.w
        };
    }
    quaternion_t operator-(const float& _f) const noexcept {
        return quaternion_t {
            this->x - _f,
            this->y - _f,
            this->z - _f,
            this->w - _f
        };
    }
    quaternion_t& operator-=(const quaternion_t& q) noexcept {
        *this = *this - q;
        return *this;
    }
    quaternion_t& operator-=(const float& _f) noexcept {
        *this = *this - _f;
        return *this;
    }

    quaternion_t operator*(const quaternion_t& q) const noexcept {
        return quaternion_t {
            this->x * q.x,
            this->y * q.y,
            this->z * q.z,
            this->w * q.w
        };
    }
    quaternion_t operator*(const float& _f) const noexcept {
        return quaternion_t {
            this->x * _f,
            this->y * _f,
            this->z * _f,
            this->w * _f
        };
    }
    quaternion_t& operator*=(const quaternion_t& q) noexcept {
        *this = *this * q;
        return *this;
    }
    quaternion_t& operator*=(const float& _f) noexcept {
        *this = *this * _f;
        return *this;
    }

    quaternion_t operator/(const quaternion_t& q) const noexcept {
        return quaternion_t {
            this->x / q.x,
            this->y / q.y,
            this->z / q.z,
            this->w / q.w
        };
    }
    quaternion_t operator/(const float& _f) const noexcept {
        return quaternion_t {
            this->x / _f,
            this->y / _f,
            this->z / _f,
            this->w / _f
        };
    }
    quaternion_t& operator/=(const quaternion_t& q) noexcept {
        *this = *this / q;
        return *this;
    }
    quaternion_t& operator/=(const float& _f) noexcept {
        *this = *this / _f;
        return *this;
    }

    bool operator==(const quaternion_t& q) const noexcept {
        return this->x == q.x && this->y == q.y && this->z == q.z && this->w == q.w;
    }
    bool operator!=(const quaternion_t& q) const noexcept {
        return !(*this == q);
    }

    bool isEmpty() const noexcept {
        return !this->x && !this->y && !this->z && !this->w;
    }

    float sqrMagnitude() const noexcept {
        return (this->x * this->x) + (this->y * this->y) + (this->z * this->z) + (this->w * this->w);
    }

    float magnitude() const noexcept {
        return sqrtf(this->sqrMagnitude());
    }
};
    