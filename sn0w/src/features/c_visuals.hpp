#pragma once
#include "../singleton.hpp"
#include "../sdk/so2/common/enums.h"
#include "../sdk/unity/common/t_vec3.h"

namespace visuals {
    struct bullet_hit_t {
        static constexpr float maxTime = 5.f;
        vec3_t m_vecSrc{};
        vec3_t m_vecDst{};
        float m_fLocalTime{};

        bullet_hit_t() = default;
        ~bullet_hit_t() = default;

        bullet_hit_t(const vec3_t& _src, const vec3_t& _dst) noexcept {
            this->m_vecSrc = _src;
            this->m_vecDst = _dst;
            this->m_fLocalTime = this->maxTime;
        }
    };
    struct player_hit_t {
        static constexpr float maxTime = 5.f;
        vec3_t m_vecHit{};
        int32_t m_iDamage{};
        bip m_bip{};
        float m_fLocalTime{};

        player_hit_t() = default;
        ~player_hit_t() = default;
    
        player_hit_t(const vec3_t& _hit, const int32_t& _damage, const bip& _bip) noexcept {
            this->m_vecHit = _hit;
            this->m_iDamage = _damage;
            this->m_bip = _bip;
            this->m_fLocalTime = this->maxTime;
        }
    };
};

class CVisuals : public CSingleton<CVisuals> {
public:
    visuals::bullet_hit_t m_aBulletTracers[30]{};
    visuals::player_hit_t m_aHits[30]{};

    CVisuals() = default;
    ~CVisuals() = default;

    void bulletTracers() noexcept;
    void bulletTracersR() noexcept;
    void hitmarkers() noexcept;
    void hitmarkersR() noexcept;
    void worldColor() noexcept;
    void skyColor() noexcept;
    void fog() noexcept;

    static void render() noexcept;
    static void update() noexcept;
};