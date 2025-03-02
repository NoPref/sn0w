#pragma once
#include <stdint.h>
#include "../includes/oxorany/include.h"

#define ofs(n) (g.offsets.n)

struct offsets_t {
    struct engine {
        const unsigned long long wnd_ctx  = oxorany(0x1266888);
        const unsigned long long raycast  = oxorany(0x538E6F8);
        const unsigned long long touches  = oxorany(0x538DED0);
        const uint16_t wnd_post_callback  = oxorany(0xB0);
        const unsigned long long get_render_settings = oxorany(0x9ABD24);
        const unsigned long long use_fog = oxorany(0x9B22D0);
    } engine;
    struct render_settings {
        const uint16_t fog_enabled        = oxorany(0x160);
        const uint16_t fog_start_distance = oxorany(0x178);
        const uint16_t fog_end_distance   = oxorany(0x17c);
        const uint16_t fog_density        = oxorany(0x180);
        const uint16_t fog_color          = oxorany(0x168);
        const uint16_t fog_mode           = oxorany(0x15c);
    } render_settings;
    struct game_controller {
        const uint16_t controls          = oxorany(0x278);
    } game_controller;
    struct player_controls {
        const uint16_t touch             = oxorany(0x38);
        const uint16_t hud               = oxorany(0xb0);
        const uint16_t create_move       = oxorany(0xb8);
    } player_controls;
    struct touch_con {
        const uint16_t aiming_area       = oxorany(0x28);
        const uint16_t joystick          = oxorany(0x50);
        const uint16_t shoot             = oxorany(0x60);
        const uint16_t jump              = oxorany(0x70);
        const uint16_t aim               = oxorany(0x78);
        const uint16_t inputs            = oxorany(0xb8);
    } touch_con;
    struct aiming_area {
        const uint16_t axis              = oxorany(0xc0);
    } aiming_area;
    struct joystick {
        const uint16_t radius            = oxorany(0xa0);
        const uint16_t pos               = oxorany(0xc4);
        const uint16_t cur_pos           = oxorany(0xdc);
    } joystick;
    struct i_button {
        const uint16_t pressed           = oxorany(0x88);
    } i_button;
    struct hud_view {
        const uint16_t aim               = oxorany(0x30);
    } hud_view;
    struct aim_view {
        const uint16_t default_sight     = oxorany(0x48);
        const uint16_t sniper_sight      = oxorany(0x50);
        const uint16_t collimator_sight  = oxorany(0x58);
    } aim_view;
    struct delegate {
        const uint16_t ptr               = oxorany(0x18);
    } delegate;
    struct networking_peer {
        const uint16_t localplayer       = oxorany(0x168);
        const uint16_t photonview_list   = oxorany(0x1e0);
        const uint16_t photonplayer_list = oxorany(0x1c0);
    } networking_peer;
    struct player_manager {
        const uint16_t players_d         = oxorany(0x28);
        const uint16_t localplayer       = oxorany(0x70);
    } player_manager;
    struct grenade_manager {
        const uint16_t dropped           = oxorany(0x30);
    } grenade_manager;
    struct weapon_drop_manager {
        const uint16_t dropped           = oxorany(0x30);
    } weapon_drop_manager;
    struct grenade_effect_emitter {
        const uint16_t effects           = oxorany(0x38);
    } grenade_effect_emitter;
    struct flashbang_effect_controller {
        const uint16_t progress          = oxorany(0x64);
    } flashbang_effect_controller;
    struct smoke_effect_controller {
        const uint16_t progress          = oxorany(0x54);
    } smoke_effect_controller;
    struct bomb_manager {
        const uint16_t planted           = oxorany(0x98);
    } bomb_manager;
    struct inventory_service {
        const uint16_t definitions       = oxorany(0xe8);
        const uint16_t items             = oxorany(0xf0);
    } inventory_service;
    struct inventory_item_definition {
        const uint16_t id                = oxorany(0x10);
        const uint16_t name              = oxorany(0x18);
    } inventory_item_definition;
    struct player_hit_controller {
        const uint16_t on_hit            = oxorany(0xc0);
    } player_hit_controller;
};