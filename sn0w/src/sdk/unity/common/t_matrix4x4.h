#pragma once

#pragma pack(1)
struct matrix4x4_t {
    float m00;
    float m10;
    float m20;
    float m30;
    float m01;
    float m11;
    float m21;
    float m31;
    float m02;
    float m12;
    float m22;
    float m32;
    float m03;
    float m13;
    float m23;
    float m33;

    matrix4x4_t operator*(const matrix4x4_t& a1) const noexcept {
        matrix4x4_t ret{};
        ret.m00 = this->m00 * a1.m00 + this->m01 * a1.m10 + this->m02 * a1.m20 + this->m03 * a1.m30;
        ret.m01 = this->m00 * a1.m01 + this->m01 * a1.m11 + this->m02 * a1.m21 + this->m03 * a1.m31;
        ret.m02 = this->m00 * a1.m02 + this->m01 * a1.m12 + this->m02 * a1.m22 + this->m03 * a1.m32;
        ret.m03 = this->m00 * a1.m03 + this->m01 * a1.m13 + this->m02 * a1.m23 + this->m03 * a1.m33;

        ret.m10 = this->m10 * a1.m00 + this->m11 * a1.m10 + this->m12 * a1.m20 + this->m13 * a1.m30;
        ret.m11 = this->m10 * a1.m01 + this->m11 * a1.m11 + this->m12 * a1.m21 + this->m13 * a1.m31;
        ret.m12 = this->m10 * a1.m02 + this->m11 * a1.m12 + this->m12 * a1.m22 + this->m13 * a1.m32;
        ret.m13 = this->m10 * a1.m03 + this->m11 * a1.m13 + this->m12 * a1.m23 + this->m13 * a1.m33;

        ret.m20 = this->m20 * a1.m00 + this->m21 * a1.m10 + this->m22 * a1.m20 + this->m23 * a1.m30;
        ret.m21 = this->m20 * a1.m01 + this->m21 * a1.m11 + this->m22 * a1.m21 + this->m23 * a1.m31;
        ret.m22 = this->m20 * a1.m02 + this->m21 * a1.m12 + this->m22 * a1.m22 + this->m23 * a1.m32;
        ret.m23 = this->m20 * a1.m03 + this->m21 * a1.m13 + this->m22 * a1.m23 + this->m23 * a1.m33;

        ret.m30 = this->m30 * a1.m00 + this->m31 * a1.m10 + this->m32 * a1.m20 + this->m33 * a1.m30;
        ret.m31 = this->m30 * a1.m01 + this->m31 * a1.m11 + this->m32 * a1.m21 + this->m33 * a1.m31;
        ret.m32 = this->m30 * a1.m02 + this->m31 * a1.m12 + this->m32 * a1.m22 + this->m33 * a1.m32;
        ret.m33 = this->m30 * a1.m03 + this->m31 * a1.m13 + this->m32 * a1.m23 + this->m33 * a1.m33;

        return ret;
    }

};
#pragma pack()