#pragma once
#include <stdint.h>
#include "c_object.h"
#include "common/include.h"

enum texture_format : uint8_t {
    texture_format_alpha8 = 1,
    texture_format_argb4444 = 2,
    texture_format_rgb24 = 3,
    texture_format_rgba32 = 4,
    texture_format_argb32 = 5,
    texture_format_rgb565 = 7,
    texture_format_r16 = 9,
    texture_format_dxt1 = 10,
    texture_format_dxt5 = 12,
    texture_format_rgba4444 = 13,
    texture_format_bgra32 = 14,
    texture_format_rhalf = 15,
    texture_format_rghalf = 16,
    texture_format_rgbahalf = 17,
    texture_format_rfloat = 18,
    texture_format_rgfloat = 19,
    texture_format_rgbafloat = 20,
    texture_format_yuy2 = 21,
    texture_format_rgb9e5float = 22,
    texture_format_bc4 = 26,
    texture_format_bc5 = 27,
    texture_format_bc6h = 24,
    texture_format_bc7 = 25,
    texture_format_dxt1crunched = 28,
    texture_format_dxt5crunched = 29,
    texture_format_pvrtc_rgb2 = 30,
    texture_format_pvrtc_rgba2 = 31,
    texture_format_pvrtc_rgb4 = 32,
    texture_format_pvrtc_rgba4 = 33,
    texture_format_etc_rgb4 = 34,
    texture_format_eac_r = 41,
    texture_format_eac_r_signed = 42,
    texture_format_eac_rg = 43,
    texture_format_eac_rg_signed = 44,
    texture_format_etc2_rgb = 45,
    texture_format_etc2_rgba1 = 46,
    texture_format_etc2_rgba8 = 47,
    texture_format_astc_4x4 = 48,
    texture_format_astc_5x5 = 49,
    texture_format_astc_6x6 = 50,
    texture_format_astc_8x8 = 51,
    texture_format_astc_10x10 = 52,
    texture_format_astc_12x12 = 53,
    texture_format_etc_rgb4_3ds = 60,
    texture_format_etc_rgba8_3ds = 61,
    texture_format_rg16 = 62,
    texture_format_r8 = 63,
    texture_format_etc_rgb4crunched = 64,
    texture_format_etc2_rgba8crunched = 65,
    texture_format_astc_hdr_4x4 = 66,
    texture_format_astc_hdr_5x5 = 67,
    texture_format_astc_hdr_6x6 = 68,
    texture_format_astc_hdr_8x8 = 69,
    texture_format_astc_hdr_10x10 = 70,
    texture_format_astc_hdr_12x12 = 71,
    texture_format_astc_rgb_4x4 = 48,
    texture_format_astc_rgb_5x5 = 49,
    texture_format_astc_rgb_6x6 = 50,
    texture_format_astc_rgb_8x8 = 51,
    texture_format_astc_rgb_10x10 = 52,
    texture_format_astc_rgb_12x12 = 53,
    texture_format_astc_rgba_4x4 = 54,
    texture_format_astc_rgba_5x5 = 55,
    texture_format_astc_rgba_6x6 = 56,
    texture_format_astc_rgba_8x8 = 57,
    texture_format_astc_rgba_10x10 = 58,
    texture_format_astc_rgba_12x12 = 59,
};

class CTexture : public CObject {
};

class CTexture3D : public CTexture {
};

class CTexture2D : public CTexture {
public:
    static CTexture2D* getWhiteTexture() noexcept;
    static void ctor(CTexture2D* thiz, const int32_t& w, const int32_t& h, const texture_format& format, bool mipChain = true) noexcept;

    array_t<color_t>* getPixels() const noexcept;
    void setPixels(const array_t<color_t>* const& pixels) noexcept;
    void setPixel(const uint32_t& x, const uint32_t& y, const color_t& color) noexcept;
    void apply() noexcept;
};