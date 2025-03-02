#pragma once
#include <math.h>
#include "t_quaternion.h"

#define rad2deg(x) ((x) * (180.f / M_PI))
#define deg2rad(x) ((x) * (M_PI / 180.0))

struct euler_angles_t {
public:
    float pitch;
    float yaw;
    float roll;

    euler_angles_t() = default;
    euler_angles_t(const float& _pitch, const float& _yaw, const float& _roll) noexcept {
        this->pitch = _pitch;
        this->yaw   = _yaw;
        this->roll  = _roll;
    }
    ~euler_angles_t() = default;
    
    euler_angles_t operator+(const euler_angles_t& ang) const noexcept {
        return euler_angles_t {
            this->pitch + ang.pitch,
            this->yaw   + ang.yaw,
            this->roll  + ang.roll
        };
    }
    euler_angles_t operator+(const float& _f) const noexcept {
        return euler_angles_t {
            this->pitch + _f,
            this->yaw   + _f,
            this->roll  + _f
        };
    }
    euler_angles_t& operator+=(const euler_angles_t& ang) noexcept {
        *this = *this + ang;
        return *this;
    }
    euler_angles_t& operator+=(const float& _f) noexcept {
        *this = *this + _f;
        return *this;
    }

    euler_angles_t operator-(const euler_angles_t& ang) const noexcept {
        return euler_angles_t {
            this->pitch - ang.pitch,
            this->yaw   - ang.yaw,
            this->roll  - ang.roll
        };
    }
    euler_angles_t operator-(const float& _f) const noexcept {
        return euler_angles_t {
            this->pitch - _f,
            this->yaw   - _f,
            this->roll  - _f
        };
    }
    euler_angles_t& operator-=(const euler_angles_t& ang) noexcept {
        *this = *this - ang;
        return *this;
    }
    euler_angles_t& operator-=(const float& _f) noexcept {
        *this = *this - _f;
        return *this;
    }

    euler_angles_t operator*(const euler_angles_t& ang) const noexcept {
        return euler_angles_t {
            this->pitch * ang.pitch,
            this->yaw   * ang.yaw,
            this->roll  * ang.roll
        };
    }
    euler_angles_t operator*(const float& _f) const noexcept {
        return euler_angles_t {
            this->pitch * _f,
            this->yaw   * _f,
            this->roll  * _f,
        };
    }
    euler_angles_t& operator*=(const euler_angles_t& ang) noexcept {
        *this = *this * ang;
        return *this;
    }
    euler_angles_t& operator*=(const float& _f) noexcept {
        *this = *this * _f;
        return *this;
    }

    euler_angles_t operator/(const euler_angles_t& ang) const noexcept {
        return euler_angles_t {
            this->pitch / ang.pitch,
            this->yaw   / ang.yaw,
            this->roll  / ang.roll
        };
    }
    euler_angles_t operator/(const float& _f) const noexcept {
        return euler_angles_t {
            this->pitch / _f,
            this->yaw   / _f,
            this->roll  / _f
        };
    }
    euler_angles_t& operator/=(const euler_angles_t& ang) noexcept {
        *this = *this / ang;
        return *this;
    }
    euler_angles_t& operator/=(const float& _f) noexcept {
        *this = *this / _f;
        return *this;
    }

    bool operator==(const euler_angles_t& ang) const noexcept {
        return this->pitch == ang.pitch && this->yaw == ang.yaw && this->roll == ang.roll;
    }
    bool operator!=(const euler_angles_t& ang) const noexcept {
        return !(*this == ang);
    }

    bool isEmpty() const noexcept {
        return !this->pitch && !this->yaw && !this->roll;
    }

    void clampPitch(float fMaxPitch = 70.f) noexcept {
        if(this->pitch > fMaxPitch)
            this->pitch = fMaxPitch;
        if(this->pitch < -fMaxPitch)
            this->pitch = -fMaxPitch;
    }

    euler_angles_t clampedPitch(float fMaxPitch = 70.f) noexcept {
        euler_angles_t ret = *this;
        ret.clampPitch(fMaxPitch);
        return ret;
    }

    void normalize(float fMaxPitch = 90.f, bool bClampPitch = true) noexcept {
        if(bClampPitch)
            this->clampPitch(fMaxPitch);
        else {
            if(this->pitch > fMaxPitch)
                this->pitch -= 360.f;
            if(this->pitch < -fMaxPitch)
                this->pitch += 360.f;
        }

        if(this->yaw > 180.f)
            this->yaw -= 360.f;
        if(this->yaw < -180.f)
            this->yaw += 360.f;

        this->roll = 0.f;
    }

    euler_angles_t normalized(float fMaxPitch = 90.f, bool bClampPitch = true) const noexcept {
        euler_angles_t ret = *this;
        ret.normalize(fMaxPitch, bClampPitch);
        return ret;
    }
};