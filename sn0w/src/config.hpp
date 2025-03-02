#pragma once
#include <stdint.h>
#include <string>
#include "sdk/so2/common/enums.h"
#include "sdk/unity/common/t_vec2.h"
#include "sdk/unity/common/t_vec3.h"

struct hitbox_config_t {
public:
    bool m_bEnabled;
    bip m_bip;

    hitbox_config_t() = default;
    hitbox_config_t(bip _bip) {
        this->m_bEnabled = false;
        this->m_bip = _bip;
    }
};

struct legitbot_config_t {
public:
    bool m_bEnabled;
    float m_fMaxFOV;
    hitbox_config_t m_bones[3];
    float m_fYaw;
    float m_fPitch;
    float m_fYawFire;
    float m_fPitchFire;
    bool m_bRCS;
    bool m_bDynamicFOV;
    bool m_bShootDelay;
    float m_fReactionTime;
    weapon_type m_weaponType;

    legitbot_config_t(const weapon_type& _weaponType) {
        this->m_bEnabled = false;
        this->m_fMaxFOV = 5.f;
        this->m_bones[0] = hitbox_config_t(bip_head);
        this->m_bones[1] = hitbox_config_t(bip_spine2);
        this->m_bones[2] = hitbox_config_t(bip_hip);
        this->m_fYaw = 5.f;
        this->m_fPitch = 5.f;
        this->m_fYawFire = 3.f;
        this->m_fPitchFire = 3.f;
        this->m_bRCS = true;
        this->m_bDynamicFOV = false;
        this->m_bShootDelay = false;
        this->m_fReactionTime = 0.f;
        this->m_weaponType = _weaponType;
    }
    ~legitbot_config_t() = default;
};

struct config_t {
    struct rage {
        struct aimbot {
            bool 
                enabled{},
                autofire{},
                autowall{},
                autoscope{},
                autostop{},
                baim{},
                hitbox[5]{}, //head, chest, arms, hip, legs
                exploits[3]{}; //double tap, hide shots, force psilent

            float
                max_fov = 180.f,
                autostop_mult = 10.f,
                autostop_peek_factor = 2.f;
            
            uint8_t
                min_damage = 100,
                hitchance = 100,
                multipoint[5]{}; 

        } aimbot;
        struct antiaim {
            bool 
                enabled{},
                at_targets{},
                crooked{},
                defensive{};
            
            int16_t 
                yaw{},
                pitch{-1},
                roll{},
                lby{};
            
            uint8_t
                mode{},
                jitter_range{1},
                spin_speed{1};
            
            uint16_t
                flick_rate = 500;
            
        } antiaim;
        struct extra {
            bool
                fake_lags{};
            
            uint8_t
                fake_lags_rate = 1;

        } extra;
    } rage;
    struct exploits {
        bool
            rapid_fire{},
            infinity_ammo{},
            wallshot{},
            ignore_freeze_time{},
            air_jump{},
            noclip{};
    } exploits;
    struct legit {
        legitbot_config_t configs[6]{
            legitbot_config_t(weapon_type_pistol),
            legitbot_config_t(weapon_type_rifle),
            legitbot_config_t(weapon_type_smg),
            legitbot_config_t(weapon_type_shotgun),
            legitbot_config_t(weapon_type_heavy),
            legitbot_config_t(weapon_type_sniper)
        };
    } legit;
    struct visuals {
        struct esp {
            bool
                enabled{},
                teammates{},
                box{},
                health{},
                nick{},
                weapon{},
                weapons[2]{}, //text, icon
                skeleton{},
                skeleton_hit{},
                flags{},
                flags_a[5]{}, //armor, bomb/kits, scope, reload, plant/defuse
                ammo{},
                bomb{},
                dropped_weapon{},
                dropped_grenade{};

            uint8_t
                box_type{},
                health_type{};
            
            float
                box_color[4]{1.f, 1.f, 1.f, 1.f},
                health_color[4]{0.58f, 1.f, 0.39f, 1.f},
                nick_color[4]{1.f, 1.f, 1.f, 1.f},
                weapon_color[4]{1.f, 1.f, 1.f, 1.f},
                skeleton_color[4]{1.f, 1.f, 1.f, 1.f},
                skeleton_hit_color[4]{1.f, 1.f, 1.f, 0.5f},
                flags_color[4]{1.f, 1.f, 1.f, 1.f},
                ammo_color[4]{0.39f, 0.47f, 1.f, 1.f},
                bomb_color[4]{0.86f, 0.47f, 0.62f, 1.f},
                dropped_weapon_color[4]{1.f, 1.f, 1.f, 1.f},
                dropped_grenade_color[4]{1.f, 0.39f, 0.39f, 1.f};
                
        } esp;
        struct chams {
            bool
                enemy{},
                teammate{},
                local{},
                arms{},
                gloves{},
                weapon{};
            
            uint8_t
                enemy_mat{},
                teammate_mat{},
                local_mat{},
                arms_mat{},
                gloves_mat{},
                weapon_mat{};
            
            float
                enemy_color[4]{0.74f, 1.f, 0.39f, 1.f},
                enemy_color_hidden[4]{0.39f, 0.39f, 1.f, 1.f},
                teammate_color[4]{0.5f, 0.39f, 1.f, 1.f},
                teammate_color_hidden[4]{0.5f, 0.39f, 1.f, 1.f},
                local_color[4]{1.f, 0.52f, 0.98f, 1.f},
                arms_color[4]{0.58f, 0.66f, 1.f, 1.f},
                gloves_color[4]{0.58f, 0.86f, 1.f, 1.f},
                weapon_color[4]{0.58f, 1.f, 0.86f, 1.f};

        } chams;
        struct world {
            struct env {
                bool
                    world_color{},
                    world_color_solid{},
                    world_color_update{},
                    sky_color{},
                    fog{};
                
                float
                    world_color_color[4]{0.19f, 0.19f, 0.31f, 1.f},
                    sky_color_color[4]{1.f, 1.f, 1.f, 1.f},
                    fog_color[4]{0.54f, 0.54f, 0.78f, 1.f},
                    fog_start = 3.f,
                    fog_end = 6.f,
                    fog_density = 2.f;
                    
            } env;
            struct render {
                bool
                    bullet_tracer{},
                    bullet_impacts{},
                    hit_marker{};
                
                float
                    bullet_tracer_color[4]{1.f, 1.f, 1.f, 1.f},
                    bullet_impacts_color[4]{0.86f, 0.43f, 0.78f, 1.f},
                    hit_marker_color[4]{1.f, 0.23f, 0.23f, 1.f};

            } render;
        } world;
    } visuals;
    struct misc {
        struct general {
            bool
                hitsound{},
                thirdperson{},
                viewmodel{},
                left_hand{},
                removals[7]{}, //flashbang, smoke, scope, aim punch, scope zoom, arms, weapon
                aspect_ratio_update{};
            
            float
                thirdperson_distance = 2.5f;
            
            uint8_t
                fov = 60;
            
            uint16_t
                aspect_ratio_w{};
            
            vec3_t
                viewmodel_pos{1.f, 1.f, 1.f};

        } general;
        struct movement {
            bool
                air_strafes{},
                fast_stop{},
                anti_rollback{};
            
            float
                air_strafes_speed = 6.f;

        } movement;
    } misc;
    struct test {
        bool
            bools[32]{};
        
        float 
            floats[32]{};
    } test;

    std::string array[16]{};
    int8_t configsNum{};
    int8_t currentIndex{};
    void update() noexcept;
    void create(const char* const& szName) noexcept;
    void save(const uint8_t& index) noexcept;
    void load(const uint8_t& index) noexcept;
    void remove(const uint8_t& index) noexcept;
};