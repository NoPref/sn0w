#include <dirent.h>
#include <fstream>
#include <array>
#include "../globals.hpp"

#define __config_path (oxorany("/storage/emulated/0/Android/data/com.axlebolt.standoff2/files/"))
#define __config_ext (oxorany(".sc"))

#define float3tosarray(arr) {arr[0], arr[1], arr[2]}
#define float4tosarray(arr) {arr[0], arr[1], arr[2], arr[3]}
#define jsonarray3(var,json) var[0] = json[0].get<float>(); \
                             var[1] = json[1].get<float>(); \
                             var[2] = json[2].get<float>()

#define jsonarray4(var,json) var[0] = json[0].get<float>(); \
                             var[1] = json[1].get<float>(); \
                             var[2] = json[2].get<float>(); \
                             var[3] = json[3].get<float>() 

void config_t::update() noexcept {
    DIR* dir = opendir(__config_path);
    if(dir == NULL)
        return;
    this->currentIndex = 0;
    this->configsNum = 0;
    uint32_t iter{};
    while(dirent* entry = readdir(dir)) {
        const char* fileName = entry->d_name;
        if(fileName == NULL)
            continue;
        if(strnlen(fileName, 4) < 4)
            continue;
        const char* extension = strchr(fileName, '.');
        if(extension == NULL)
            continue;
        if(strcmp(extension, __config_ext) != 0)
            continue;
        if(this->configsNum >= 16)
            break;
        this->array[this->configsNum] = std::string(fileName);
        ++this->configsNum;
    }
    closedir(dir);
}

void config_t::create(const char* const& szName) noexcept {
    std::string path = __config_path; path+=szName; path+=__config_ext;
    std::ofstream file(path);
    file.close();
}

void config_t::save(const uint8_t& index) noexcept {
    if(this->array[index].empty())
        return;
    
    std::string path = __config_path; path+=this->array[index];
    std::ofstream file(path);
    if(!file.is_open())
        return;
    
    nlohmann::ordered_json json{};

    json[oxorany("ui")][oxorany("accent")] = (std::array<float, 3>)float3tosarray(g.sn0w.ui->m_accent);
    json[oxorany("ui")][oxorany("dpi")] = g.sn0w.ui->m_dpiScale;
    
    json[oxorany("ragebot")][oxorany("aimbot")][oxorany("enabled")] = this->rage.aimbot.enabled;
    json[oxorany("ragebot")][oxorany("aimbot")][oxorany("auto fire")] = this->rage.aimbot.autofire;
    json[oxorany("ragebot")][oxorany("aimbot")][oxorany("auto wall")] = this->rage.aimbot.autowall;
    json[oxorany("ragebot")][oxorany("aimbot")][oxorany("auto scope")] = this->rage.aimbot.autoscope;
    json[oxorany("ragebot")][oxorany("aimbot")][oxorany("auto stop")] = this->rage.aimbot.autostop;
    json[oxorany("ragebot")][oxorany("aimbot")][oxorany("baim")] = this->rage.aimbot.baim;
    json[oxorany("ragebot")][oxorany("aimbot")][oxorany("head")] = this->rage.aimbot.hitbox[0];
    json[oxorany("ragebot")][oxorany("aimbot")][oxorany("chest")] = this->rage.aimbot.hitbox[1];
    json[oxorany("ragebot")][oxorany("aimbot")][oxorany("arms")] = this->rage.aimbot.hitbox[2];
    json[oxorany("ragebot")][oxorany("aimbot")][oxorany("hip")] = this->rage.aimbot.hitbox[3];
    json[oxorany("ragebot")][oxorany("aimbot")][oxorany("legs")] = this->rage.aimbot.hitbox[4];
    json[oxorany("ragebot")][oxorany("aimbot")][oxorany("double tap")] = this->rage.aimbot.exploits[0];
    json[oxorany("ragebot")][oxorany("aimbot")][oxorany("hide shots")] = this->rage.aimbot.exploits[1];
    json[oxorany("ragebot")][oxorany("aimbot")][oxorany("perfect silent")] = this->rage.aimbot.exploits[2];
    json[oxorany("ragebot")][oxorany("aimbot")][oxorany("max fov")] = this->rage.aimbot.max_fov;
    json[oxorany("ragebot")][oxorany("aimbot")][oxorany("min damage")] = this->rage.aimbot.min_damage;
    json[oxorany("ragebot")][oxorany("aimbot")][oxorany("hitchance")] = this->rage.aimbot.hitchance;
    json[oxorany("ragebot")][oxorany("aimbot")][oxorany("multipoint head")] = this->rage.aimbot.multipoint[0];
    json[oxorany("ragebot")][oxorany("aimbot")][oxorany("multipoint chest")] = this->rage.aimbot.multipoint[1];
    json[oxorany("ragebot")][oxorany("aimbot")][oxorany("multipoint arms")] = this->rage.aimbot.multipoint[2];
    json[oxorany("ragebot")][oxorany("aimbot")][oxorany("multipoint hip")] = this->rage.aimbot.multipoint[3];
    json[oxorany("ragebot")][oxorany("aimbot")][oxorany("multipoint legs")] = this->rage.aimbot.multipoint[4];

    json[oxorany("ragebot")][oxorany("anti-aim")][oxorany("enabled")] = this->rage.antiaim.enabled;
    json[oxorany("ragebot")][oxorany("anti-aim")][oxorany("at targets")] = this->rage.antiaim.at_targets;
    json[oxorany("ragebot")][oxorany("anti-aim")][oxorany("crooked")] = this->rage.antiaim.crooked;
    json[oxorany("ragebot")][oxorany("anti-aim")][oxorany("defensive")] = this->rage.antiaim.defensive;
    json[oxorany("ragebot")][oxorany("anti-aim")][oxorany("yaw")] = this->rage.antiaim.yaw;
    json[oxorany("ragebot")][oxorany("anti-aim")][oxorany("pitch")] = this->rage.antiaim.pitch;
    json[oxorany("ragebot")][oxorany("anti-aim")][oxorany("roll")] = this->rage.antiaim.roll;
    json[oxorany("ragebot")][oxorany("anti-aim")][oxorany("lby")] = this->rage.antiaim.lby;
    json[oxorany("ragebot")][oxorany("anti-aim")][oxorany("mode")] = this->rage.antiaim.mode;
    json[oxorany("ragebot")][oxorany("anti-aim")][oxorany("jitter range")] = this->rage.antiaim.jitter_range;
    json[oxorany("ragebot")][oxorany("anti-aim")][oxorany("spin speed")] = this->rage.antiaim.spin_speed;
    json[oxorany("ragebot")][oxorany("anti-aim")][oxorany("flick rate")] = this->rage.antiaim.flick_rate;

    json[oxorany("ragebot")][oxorany("extra")][oxorany("fake lags")] = this->rage.extra.fake_lags;
    json[oxorany("ragebot")][oxorany("extra")][oxorany("fake lags rate")] = this->rage.extra.fake_lags_rate;

    json[oxorany("exploits")][oxorany("rapid fire")] = this->exploits.rapid_fire;
    json[oxorany("exploits")][oxorany("infinity ammo")] = this->exploits.infinity_ammo;
    json[oxorany("exploits")][oxorany("wallshot")] = this->exploits.wallshot;
    json[oxorany("exploits")][oxorany("ignore freeze time")] = this->exploits.ignore_freeze_time;
    json[oxorany("exploits")][oxorany("air jump")] = this->exploits.air_jump;

    for(uint8_t i=0;i<(sizeof(this->legit.configs)/sizeof(this->legit.configs[0]));++i) {
        const std::string curIteration = std::to_string(i);
        json[oxorany("legit")][curIteration][oxorany("enabled")] = this->legit.configs[i].m_bEnabled;
        json[oxorany("legit")][curIteration][oxorany("max fov")] = this->legit.configs[i].m_fMaxFOV;
        json[oxorany("legit")][curIteration][oxorany("head")] = this->legit.configs[i].m_bones[0].m_bEnabled;
        json[oxorany("legit")][curIteration][oxorany("chest")] = this->legit.configs[i].m_bones[1].m_bEnabled;
        json[oxorany("legit")][curIteration][oxorany("hip")] = this->legit.configs[i].m_bones[2].m_bEnabled;
        json[oxorany("legit")][curIteration][oxorany("yaw")] = this->legit.configs[i].m_fYaw;
        json[oxorany("legit")][curIteration][oxorany("pitch")] = this->legit.configs[i].m_fPitch;
        json[oxorany("legit")][curIteration][oxorany("yaw fire")] = this->legit.configs[i].m_fYawFire;
        json[oxorany("legit")][curIteration][oxorany("pitch fire")] = this->legit.configs[i].m_fPitchFire;
        json[oxorany("legit")][curIteration][oxorany("rcs")] = this->legit.configs[i].m_bRCS;
        json[oxorany("legit")][curIteration][oxorany("dynamic fov")] = this->legit.configs[i].m_bDynamicFOV;
        json[oxorany("legit")][curIteration][oxorany("shoot delay")] = this->legit.configs[i].m_bShootDelay;
        json[oxorany("legit")][curIteration][oxorany("reaction time")] = this->legit.configs[i].m_fReactionTime;
    }

    json[oxorany("visuals")][oxorany("esp")][oxorany("enabled")] = this->visuals.esp.enabled;
    json[oxorany("visuals")][oxorany("esp")][oxorany("teammates")] = this->visuals.esp.teammates;
    json[oxorany("visuals")][oxorany("esp")][oxorany("box")] = this->visuals.esp.box;
    json[oxorany("visuals")][oxorany("esp")][oxorany("health")] = this->visuals.esp.health;
    json[oxorany("visuals")][oxorany("esp")][oxorany("nick")] = this->visuals.esp.nick;
    json[oxorany("visuals")][oxorany("esp")][oxorany("weapon")] = this->visuals.esp.weapon;
    json[oxorany("visuals")][oxorany("esp")][oxorany("weapon text")] = this->visuals.esp.weapons[0];
    json[oxorany("visuals")][oxorany("esp")][oxorany("weapon icon")] = this->visuals.esp.weapons[1];
    json[oxorany("visuals")][oxorany("esp")][oxorany("skeleton")] = this->visuals.esp.skeleton;
    json[oxorany("visuals")][oxorany("esp")][oxorany("skeleton hit")] = this->visuals.esp.skeleton_hit;
    json[oxorany("visuals")][oxorany("esp")][oxorany("flags")] = this->visuals.esp.flags;
    json[oxorany("visuals")][oxorany("esp")][oxorany("flag_armor")] = this->visuals.esp.flags_a[0];
    json[oxorany("visuals")][oxorany("esp")][oxorany("flag_bk")] = this->visuals.esp.flags_a[1];
    json[oxorany("visuals")][oxorany("esp")][oxorany("flag_scope")] = this->visuals.esp.flags_a[2];
    json[oxorany("visuals")][oxorany("esp")][oxorany("flag_reload")] = this->visuals.esp.flags_a[3];
    json[oxorany("visuals")][oxorany("esp")][oxorany("flag_pd")] = this->visuals.esp.flags_a[4];
    json[oxorany("visuals")][oxorany("esp")][oxorany("ammo")] = this->visuals.esp.ammo;
    json[oxorany("visuals")][oxorany("esp")][oxorany("bomb")] = this->visuals.esp.bomb;
    json[oxorany("visuals")][oxorany("esp")][oxorany("dropped weapon")] = this->visuals.esp.dropped_weapon;
    json[oxorany("visuals")][oxorany("esp")][oxorany("dropped grenade")] = this->visuals.esp.dropped_grenade;
    json[oxorany("visuals")][oxorany("esp")][oxorany("box type")] = this->visuals.esp.box_type;
    json[oxorany("visuals")][oxorany("esp")][oxorany("health type")] = this->visuals.esp.health_type;

    json[oxorany("visuals")][oxorany("esp")][oxorany("box color")] = (std::array<float, 4>)float4tosarray(this->visuals.esp.box_color);
    json[oxorany("visuals")][oxorany("esp")][oxorany("health color")] = (std::array<float, 4>)float4tosarray(this->visuals.esp.health_color);
    json[oxorany("visuals")][oxorany("esp")][oxorany("nick color")] = (std::array<float, 4>)float4tosarray(this->visuals.esp.nick_color);
    json[oxorany("visuals")][oxorany("esp")][oxorany("weapon color")] = (std::array<float, 4>)float4tosarray(this->visuals.esp.weapon_color);
    json[oxorany("visuals")][oxorany("esp")][oxorany("skeleton color")] = (std::array<float, 4>)float4tosarray(this->visuals.esp.skeleton_color);
    json[oxorany("visuals")][oxorany("esp")][oxorany("skeleton hit color")] = (std::array<float, 4>)float4tosarray(this->visuals.esp.skeleton_hit_color);
    json[oxorany("visuals")][oxorany("esp")][oxorany("flags color")] = (std::array<float, 4>)float4tosarray(this->visuals.esp.flags_color);
    json[oxorany("visuals")][oxorany("esp")][oxorany("ammo color")] = (std::array<float, 4>)float4tosarray(this->visuals.esp.ammo_color);
    json[oxorany("visuals")][oxorany("esp")][oxorany("bomb color")] = (std::array<float, 4>)float4tosarray(this->visuals.esp.bomb_color);
    json[oxorany("visuals")][oxorany("esp")][oxorany("dropped weapon color")] = (std::array<float, 4>)float4tosarray(this->visuals.esp.dropped_weapon_color);
    json[oxorany("visuals")][oxorany("esp")][oxorany("dropped grenade color")] = (std::array<float, 4>)float4tosarray(this->visuals.esp.dropped_grenade_color);

    json[oxorany("visuals")][oxorany("chams")][oxorany("enemy")] = this->visuals.chams.enemy;
    json[oxorany("visuals")][oxorany("chams")][oxorany("teammate")] = this->visuals.chams.teammate;
    json[oxorany("visuals")][oxorany("chams")][oxorany("local")] = this->visuals.chams.local;
    json[oxorany("visuals")][oxorany("chams")][oxorany("arms")] = this->visuals.chams.arms;
    json[oxorany("visuals")][oxorany("chams")][oxorany("gloves")] = this->visuals.chams.gloves;
    json[oxorany("visuals")][oxorany("chams")][oxorany("weapon")] = this->visuals.chams.weapon;

    json[oxorany("visuals")][oxorany("chams")][oxorany("enemy mat")] = this->visuals.chams.enemy_mat;
    json[oxorany("visuals")][oxorany("chams")][oxorany("teammate mat")] = this->visuals.chams.teammate_mat;
    json[oxorany("visuals")][oxorany("chams")][oxorany("local mat")] = this->visuals.chams.local_mat;
    json[oxorany("visuals")][oxorany("chams")][oxorany("arms mat")] = this->visuals.chams.arms_mat;
    json[oxorany("visuals")][oxorany("chams")][oxorany("gloves mat")] = this->visuals.chams.gloves_mat;
    json[oxorany("visuals")][oxorany("chams")][oxorany("weapon mat")] = this->visuals.chams.weapon_mat;

    json[oxorany("visuals")][oxorany("chams")][oxorany("enemy color")] = float4tosarray(this->visuals.chams.enemy_color);
    json[oxorany("visuals")][oxorany("chams")][oxorany("enemy color hidden")] = float4tosarray(this->visuals.chams.enemy_color_hidden);
    json[oxorany("visuals")][oxorany("chams")][oxorany("teammate color")] = float4tosarray(this->visuals.chams.teammate_color);
    json[oxorany("visuals")][oxorany("chams")][oxorany("teammate color hidden")] = float4tosarray(this->visuals.chams.teammate_color_hidden);
    json[oxorany("visuals")][oxorany("chams")][oxorany("local color")] = float4tosarray(this->visuals.chams.local_color);
    json[oxorany("visuals")][oxorany("chams")][oxorany("arms color")] = float4tosarray(this->visuals.chams.arms_color);
    json[oxorany("visuals")][oxorany("chams")][oxorany("gloves color")] = float4tosarray(this->visuals.chams.gloves_color);
    json[oxorany("visuals")][oxorany("chams")][oxorany("weapon color")] = float4tosarray(this->visuals.chams.weapon_color);

    json[oxorany("visuals")][oxorany("world")][oxorany("environment")][oxorany("world color")] =this->visuals.world.env.world_color;
    json[oxorany("visuals")][oxorany("world")][oxorany("environment")][oxorany("world color solid")] = this->visuals.world.env.world_color_solid;
    json[oxorany("visuals")][oxorany("world")][oxorany("environment")][oxorany("fog")] =this->visuals.world.env.fog;
    json[oxorany("visuals")][oxorany("world")][oxorany("environment")][oxorany("world color_c")] = float4tosarray(this->visuals.world.env.world_color_color);
    json[oxorany("visuals")][oxorany("world")][oxorany("environment")][oxorany("fog color")] = float4tosarray(this->visuals.world.env.fog_color);
    json[oxorany("visuals")][oxorany("world")][oxorany("environment")][oxorany("fog start")] = this->visuals.world.env.fog_start;
    json[oxorany("visuals")][oxorany("world")][oxorany("environment")][oxorany("fog end")] = this->visuals.world.env.fog_end;
    json[oxorany("visuals")][oxorany("world")][oxorany("environment")][oxorany("fog density")] = this->visuals.world.env.fog_density;

    json[oxorany("visuals")][oxorany("world")][oxorany("render")][oxorany("bullet tracer")] = this->visuals.world.render.bullet_tracer;
    json[oxorany("visuals")][oxorany("world")][oxorany("render")][oxorany("bullet impacts")] = this->visuals.world.render.bullet_impacts;
    json[oxorany("visuals")][oxorany("world")][oxorany("render")][oxorany("hit marker")] = this->visuals.world.render.hit_marker;

    json[oxorany("visuals")][oxorany("world")][oxorany("render")][oxorany("bullet tracer color")] = float4tosarray(this->visuals.world.render.bullet_tracer_color);
    json[oxorany("visuals")][oxorany("world")][oxorany("render")][oxorany("bullet impacts color")] = float4tosarray(this->visuals.world.render.bullet_impacts_color);
    json[oxorany("visuals")][oxorany("world")][oxorany("render")][oxorany("hit marker color")] = float4tosarray(this->visuals.world.render.hit_marker_color);

    json[oxorany("misc")][oxorany("general")][oxorany("hitsound")] = this->misc.general.hitsound;
    json[oxorany("misc")][oxorany("general")][oxorany("thirdperson")] = this->misc.general.thirdperson;
    json[oxorany("misc")][oxorany("general")][oxorany("viewmodel")] = this->misc.general.viewmodel;
    json[oxorany("misc")][oxorany("general")][oxorany("remove flashbang")] = this->misc.general.removals[0];
    json[oxorany("misc")][oxorany("general")][oxorany("remove smoke")] = this->misc.general.removals[1];
    json[oxorany("misc")][oxorany("general")][oxorany("remove scope")] = this->misc.general.removals[2];
    json[oxorany("misc")][oxorany("general")][oxorany("remove aim punch")] = this->misc.general.removals[3];
    json[oxorany("misc")][oxorany("general")][oxorany("remove scope zoom")] = this->misc.general.removals[4];
    json[oxorany("misc")][oxorany("general")][oxorany("arms")] = this->misc.general.removals[5];
    json[oxorany("misc")][oxorany("general")][oxorany("weapon")] = this->misc.general.removals[6];

    json[oxorany("misc")][oxorany("general")][oxorany("thirdperson distance")] = this->misc.general.thirdperson_distance;
    json[oxorany("misc")][oxorany("general")][oxorany("camera fov")] = this->misc.general.fov;
    json[oxorany("misc")][oxorany("general")][oxorany("aspect ratio")] = this->misc.general.aspect_ratio_w;
    json[oxorany("misc")][oxorany("general")][oxorany("viewmodel x")] = this->misc.general.viewmodel_pos.x;
    json[oxorany("misc")][oxorany("general")][oxorany("viewmodel y")] = this->misc.general.viewmodel_pos.y;
    json[oxorany("misc")][oxorany("general")][oxorany("viewmodel z")] = this->misc.general.viewmodel_pos.z;

    json[oxorany("misc")][oxorany("movement")][oxorany("air strafes")] = this->misc.movement.air_strafes;
    json[oxorany("misc")][oxorany("movement")][oxorany("fast stop")] = this->misc.movement.fast_stop;
    json[oxorany("misc")][oxorany("movement")][oxorany("anti rollback")] = this->misc.movement.anti_rollback;

    json[oxorany("misc")][oxorany("movement")][oxorany("air strafes speed")] = this->misc.movement.air_strafes_speed;

    file << json.dump(4);
    file.flush();
    file.close();
}

void config_t::load(const uint8_t& index) noexcept {
    if(this->array[index].empty())
        return;
    
    std::string path = __config_path; path+=this->array[index];
    std::ifstream file(path);
    if(!file.is_open())
        return;

    nlohmann::ordered_json json{};
    file >> json;

    jsonarray3(g.sn0w.ui->m_accent, json[oxorany("ui")][oxorany("accent")]);
    g.sn0w.ui->m_dpiScale = json[oxorany("ui")][oxorany("dpi")].get<float>();

    this->rage.aimbot.enabled = json[oxorany("ragebot")][oxorany("aimbot")][oxorany("enabled")].get<bool>();
    this->rage.aimbot.autofire = json[oxorany("ragebot")][oxorany("aimbot")][oxorany("auto fire")].get<bool>();
    this->rage.aimbot.autowall = json[oxorany("ragebot")][oxorany("aimbot")][oxorany("auto wall")].get<bool>();
    this->rage.aimbot.autoscope = json[oxorany("ragebot")][oxorany("aimbot")][oxorany("auto scope")].get<bool>();
    this->rage.aimbot.autostop = json[oxorany("ragebot")][oxorany("aimbot")][oxorany("auto stop")].get<bool>();
    this->rage.aimbot.baim = json[oxorany("ragebot")][oxorany("aimbot")][oxorany("baim")].get<bool>();
    this->rage.aimbot.hitbox[0] = json[oxorany("ragebot")][oxorany("aimbot")][oxorany("head")].get<bool>();
    this->rage.aimbot.hitbox[1] = json[oxorany("ragebot")][oxorany("aimbot")][oxorany("chest")].get<bool>();
    this->rage.aimbot.hitbox[2] = json[oxorany("ragebot")][oxorany("aimbot")][oxorany("arms")].get<bool>();
    this->rage.aimbot.hitbox[3] = json[oxorany("ragebot")][oxorany("aimbot")][oxorany("hip")].get<bool>();
    this->rage.aimbot.hitbox[4] = json[oxorany("ragebot")][oxorany("aimbot")][oxorany("legs")].get<bool>();
    this->rage.aimbot.exploits[0] = json[oxorany("ragebot")][oxorany("aimbot")][oxorany("double tap")].get<bool>();
    this->rage.aimbot.exploits[1] = json[oxorany("ragebot")][oxorany("aimbot")][oxorany("hide shots")].get<bool>();
    this->rage.aimbot.exploits[2] = json[oxorany("ragebot")][oxorany("aimbot")][oxorany("perfect silent")].get<bool>();
    this->rage.aimbot.max_fov = json[oxorany("ragebot")][oxorany("aimbot")][oxorany("max fov")].get<float>();
    this->rage.aimbot.min_damage = json[oxorany("ragebot")][oxorany("aimbot")][oxorany("min damage")].get<int>();
    this->rage.aimbot.hitchance = json[oxorany("ragebot")][oxorany("aimbot")][oxorany("hitchance")].get<int>();
    this->rage.aimbot.multipoint[0] = json[oxorany("ragebot")][oxorany("aimbot")][oxorany("multipoint head")].get<int>();
    this->rage.aimbot.multipoint[1] = json[oxorany("ragebot")][oxorany("aimbot")][oxorany("multipoint chest")].get<int>();
    this->rage.aimbot.multipoint[2] = json[oxorany("ragebot")][oxorany("aimbot")][oxorany("multipoint arms")].get<int>();
    this->rage.aimbot.multipoint[3] = json[oxorany("ragebot")][oxorany("aimbot")][oxorany("multipoint hip")].get<int>();
    this->rage.aimbot.multipoint[4] = json[oxorany("ragebot")][oxorany("aimbot")][oxorany("multipoint legs")].get<int>();

    this->rage.antiaim.enabled = json[oxorany("ragebot")][oxorany("anti-aim")][oxorany("enabled")].get<bool>();
    this->rage.antiaim.at_targets = json[oxorany("ragebot")][oxorany("anti-aim")][oxorany("at targets")].get<bool>();
    this->rage.antiaim.crooked = json[oxorany("ragebot")][oxorany("anti-aim")][oxorany("crooked")].get<bool>();
    this->rage.antiaim.defensive = json[oxorany("ragebot")][oxorany("anti-aim")][oxorany("defensive")].get<bool>();
    this->rage.antiaim.yaw = json[oxorany("ragebot")][oxorany("anti-aim")][oxorany("yaw")].get<int>();
    this->rage.antiaim.pitch = json[oxorany("ragebot")][oxorany("anti-aim")][oxorany("pitch")].get<int>();
    this->rage.antiaim.roll = json[oxorany("ragebot")][oxorany("anti-aim")][oxorany("roll")].get<int>();
    this->rage.antiaim.lby = json[oxorany("ragebot")][oxorany("anti-aim")][oxorany("lby")].get<int>();
    this->rage.antiaim.mode = json[oxorany("ragebot")][oxorany("anti-aim")][oxorany("mode")].get<int>();
    this->rage.antiaim.jitter_range = json[oxorany("ragebot")][oxorany("anti-aim")][oxorany("jitter range")].get<int>();
    this->rage.antiaim.spin_speed = json[oxorany("ragebot")][oxorany("anti-aim")][oxorany("spin speed")].get<int>();
    this->rage.antiaim.flick_rate = json[oxorany("ragebot")][oxorany("anti-aim")][oxorany("flick rate")].get<int>();

    this->rage.extra.fake_lags = json[oxorany("ragebot")][oxorany("extra")][oxorany("fake lags")].get<bool>();
    this->rage.extra.fake_lags_rate = json[oxorany("ragebot")][oxorany("extra")][oxorany("fake lags rate")].get<int>();

    this->exploits.rapid_fire = json[oxorany("exploits")][oxorany("rapid fire")].get<bool>();
    this->exploits.infinity_ammo = json[oxorany("exploits")][oxorany("infinity ammo")].get<bool>();
    this->exploits.wallshot = json[oxorany("exploits")][oxorany("wallshot")].get<bool>();
    this->exploits.ignore_freeze_time = json[oxorany("exploits")][oxorany("ignore freeze time")].get<bool>();
    this->exploits.air_jump = json[oxorany("exploits")][oxorany("air jump")].get<bool>();

    for(uint8_t i=0;i<(sizeof(this->legit.configs)/sizeof(this->legit.configs[0]));++i) {
        const std::string curIteration = std::to_string(i);
        this->legit.configs[i].m_bEnabled = json[oxorany("legit")][curIteration][oxorany("enabled")].get<bool>();
        this->legit.configs[i].m_fMaxFOV = json[oxorany("legit")][curIteration][oxorany("max fov")].get<float>();
        this->legit.configs[i].m_bones[0].m_bEnabled = json[oxorany("legit")][curIteration][oxorany("head")].get<bool>();
        this->legit.configs[i].m_bones[1].m_bEnabled = json[oxorany("legit")][curIteration][oxorany("chest")].get<bool>();
        this->legit.configs[i].m_bones[2].m_bEnabled = json[oxorany("legit")][curIteration][oxorany("hip")].get<bool>();
        this->legit.configs[i].m_fYaw = json[oxorany("legit")][curIteration][oxorany("yaw")].get<float>();
        this->legit.configs[i].m_fPitch = json[oxorany("legit")][curIteration][oxorany("pitch")].get<float>();
        this->legit.configs[i].m_fYawFire = json[oxorany("legit")][curIteration][oxorany("yaw fire")].get<float>();
        this->legit.configs[i].m_fPitchFire = json[oxorany("legit")][curIteration][oxorany("pitch fire")].get<float>();
        this->legit.configs[i].m_bRCS = json[oxorany("legit")][curIteration][oxorany("rcs")].get<bool>();
        this->legit.configs[i].m_bDynamicFOV = json[oxorany("legit")][curIteration][oxorany("dynamic fov")].get<bool>();
        this->legit.configs[i].m_bShootDelay = json[oxorany("legit")][curIteration][oxorany("shoot delay")].get<bool>();
        this->legit.configs[i].m_fReactionTime = json[oxorany("legit")][curIteration][oxorany("reaction time")].get<float>();
    }

    this->visuals.esp.enabled = json[oxorany("visuals")][oxorany("esp")][oxorany("enabled")].get<bool>();
    this->visuals.esp.teammates = json[oxorany("visuals")][oxorany("esp")][oxorany("teammates")].get<bool>();
    this->visuals.esp.box = json[oxorany("visuals")][oxorany("esp")][oxorany("box")].get<bool>();
    this->visuals.esp.health = json[oxorany("visuals")][oxorany("esp")][oxorany("health")].get<bool>();
    this->visuals.esp.nick = json[oxorany("visuals")][oxorany("esp")][oxorany("nick")].get<bool>();
    this->visuals.esp.weapon = json[oxorany("visuals")][oxorany("esp")][oxorany("weapon")].get<bool>();
    this->visuals.esp.weapons[0] = json[oxorany("visuals")][oxorany("esp")][oxorany("weapon text")].get<bool>();
    this->visuals.esp.weapons[1] = json[oxorany("visuals")][oxorany("esp")][oxorany("weapon icon")].get<bool>();
    this->visuals.esp.skeleton = json[oxorany("visuals")][oxorany("esp")][oxorany("skeleton")].get<bool>();
    this->visuals.esp.skeleton_hit = json[oxorany("visuals")][oxorany("esp")][oxorany("skeleton hit")].get<bool>();
    this->visuals.esp.flags = json[oxorany("visuals")][oxorany("esp")][oxorany("flags")].get<bool>();
    this->visuals.esp.flags_a[0] = json[oxorany("visuals")][oxorany("esp")][oxorany("flag_armor")].get<bool>();
    this->visuals.esp.flags_a[1] = json[oxorany("visuals")][oxorany("esp")][oxorany("flag_bk")].get<bool>();
    this->visuals.esp.flags_a[2] = json[oxorany("visuals")][oxorany("esp")][oxorany("flag_scope")].get<bool>();
    this->visuals.esp.flags_a[3] = json[oxorany("visuals")][oxorany("esp")][oxorany("flag_reload")].get<bool>();
    this->visuals.esp.flags_a[4] = json[oxorany("visuals")][oxorany("esp")][oxorany("flag_pd")].get<bool>();
    this->visuals.esp.ammo = json[oxorany("visuals")][oxorany("esp")][oxorany("ammo")].get<bool>();
    this->visuals.esp.bomb = json[oxorany("visuals")][oxorany("esp")][oxorany("bomb")].get<bool>();
    this->visuals.esp.dropped_weapon = json[oxorany("visuals")][oxorany("esp")][oxorany("dropped weapon")].get<bool>();
    this->visuals.esp.dropped_grenade = json[oxorany("visuals")][oxorany("esp")][oxorany("dropped grenade")].get<bool>();
    this->visuals.esp.box_type = json[oxorany("visuals")][oxorany("esp")][oxorany("box type")].get<int>();
    this->visuals.esp.health_type = json[oxorany("visuals")][oxorany("esp")][oxorany("health type")].get<int>();

    jsonarray4(this->visuals.esp.box_color, json[oxorany("visuals")][oxorany("esp")][oxorany("box color")]);
    jsonarray4(this->visuals.esp.health_color, json[oxorany("visuals")][oxorany("esp")][oxorany("health color")]);
    jsonarray4(this->visuals.esp.nick_color, json[oxorany("visuals")][oxorany("esp")][oxorany("nick color")]);
    jsonarray4(this->visuals.esp.weapon_color, json[oxorany("visuals")][oxorany("esp")][oxorany("weapon color")]);
    jsonarray4(this->visuals.esp.skeleton_color, json[oxorany("visuals")][oxorany("esp")][oxorany("skeleton color")]);
    jsonarray4(this->visuals.esp.skeleton_hit_color, json[oxorany("visuals")][oxorany("esp")][oxorany("skeleton hit color")]);
    jsonarray4(this->visuals.esp.flags_color, json[oxorany("visuals")][oxorany("esp")][oxorany("flags color")]);
    jsonarray4(this->visuals.esp.ammo_color, json[oxorany("visuals")][oxorany("esp")][oxorany("ammo color")]);
    jsonarray4(this->visuals.esp.bomb_color, json[oxorany("visuals")][oxorany("esp")][oxorany("bomb color")]);
    jsonarray4(this->visuals.esp.dropped_weapon_color, json[oxorany("visuals")][oxorany("esp")][oxorany("dropped weapon color")]);
    jsonarray4(this->visuals.esp.dropped_grenade_color, json[oxorany("visuals")][oxorany("esp")][oxorany("dropped grenade color")]);

    this->visuals.chams.enemy = json[oxorany("visuals")][oxorany("chams")][oxorany("enemy")].get<bool>();
    this->visuals.chams.teammate = json[oxorany("visuals")][oxorany("chams")][oxorany("teammate")].get<bool>();
    this->visuals.chams.local = json[oxorany("visuals")][oxorany("chams")][oxorany("local")].get<bool>();
    this->visuals.chams.arms = json[oxorany("visuals")][oxorany("chams")][oxorany("arms")].get<bool>();
    this->visuals.chams.gloves = json[oxorany("visuals")][oxorany("chams")][oxorany("gloves")].get<bool>();
    this->visuals.chams.weapon = json[oxorany("visuals")][oxorany("chams")][oxorany("weapon")].get<bool>();

    this->visuals.chams.enemy_mat = json[oxorany("visuals")][oxorany("chams")][oxorany("enemy mat")].get<int>();
    this->visuals.chams.teammate_mat = json[oxorany("visuals")][oxorany("chams")][oxorany("teammate mat")].get<int>();
    this->visuals.chams.local_mat = json[oxorany("visuals")][oxorany("chams")][oxorany("local mat")].get<int>();
    this->visuals.chams.arms_mat = json[oxorany("visuals")][oxorany("chams")][oxorany("arms mat")].get<int>();
    this->visuals.chams.gloves_mat = json[oxorany("visuals")][oxorany("chams")][oxorany("gloves mat")].get<int>();
    this->visuals.chams.weapon_mat = json[oxorany("visuals")][oxorany("chams")][oxorany("weapon mat")].get<int>();

    jsonarray4(this->visuals.chams.enemy_color, json[oxorany("visuals")][oxorany("chams")][oxorany("enemy color")]);
    jsonarray4(this->visuals.chams.enemy_color_hidden, json[oxorany("visuals")][oxorany("chams")][oxorany("enemy color hidden")]);
    jsonarray4(this->visuals.chams.teammate_color, json[oxorany("visuals")][oxorany("chams")][oxorany("teammate color")]);
    jsonarray4(this->visuals.chams.teammate_color_hidden, json[oxorany("visuals")][oxorany("chams")][oxorany("teammate color hidden")]);
    jsonarray4(this->visuals.chams.local_color, json[oxorany("visuals")][oxorany("chams")][oxorany("local color")]);
    jsonarray4(this->visuals.chams.arms_color, json[oxorany("visuals")][oxorany("chams")][oxorany("arms color")]);
    jsonarray4(this->visuals.chams.gloves_color, json[oxorany("visuals")][oxorany("chams")][oxorany("gloves color")]);
    jsonarray4(this->visuals.chams.weapon_color, json[oxorany("visuals")][oxorany("chams")][oxorany("weapon color")]);

    this->visuals.world.env.world_color = json[oxorany("visuals")][oxorany("world")][oxorany("environment")][oxorany("world color")].get<bool>();
    this->visuals.world.env.world_color_solid = json[oxorany("visuals")][oxorany("world")][oxorany("environment")][oxorany("world color solid")].get<bool>();
    this->visuals.world.env.fog = json[oxorany("visuals")][oxorany("world")][oxorany("environment")][oxorany("fog")].get<bool>();
    jsonarray4(this->visuals.world.env.world_color_color, json[oxorany("visuals")][oxorany("world")][oxorany("environment")][oxorany("world color_c")]);
    jsonarray4(this->visuals.world.env.fog_color, json[oxorany("visuals")][oxorany("world")][oxorany("environment")][oxorany("fog color")]);
    this->visuals.world.env.fog_start = json[oxorany("visuals")][oxorany("world")][oxorany("environment")][oxorany("fog start")].get<float>();
    this->visuals.world.env.fog_end = json[oxorany("visuals")][oxorany("world")][oxorany("environment")][oxorany("fog end")].get<float>();
    this->visuals.world.env.fog_density = json[oxorany("visuals")][oxorany("world")][oxorany("environment")][oxorany("fog density")].get<float>();

    this->visuals.world.render.bullet_tracer = json[oxorany("visuals")][oxorany("world")][oxorany("render")][oxorany("bullet tracer")].get<bool>();
    this->visuals.world.render.bullet_impacts = json[oxorany("visuals")][oxorany("world")][oxorany("render")][oxorany("bullet impacts")].get<bool>();
    this->visuals.world.render.hit_marker = json[oxorany("visuals")][oxorany("world")][oxorany("render")][oxorany("hit marker")].get<bool>();

    jsonarray4(this->visuals.world.render.bullet_tracer_color, json[oxorany("visuals")][oxorany("world")][oxorany("render")][oxorany("bullet tracer color")]);
    jsonarray4(this->visuals.world.render.bullet_impacts_color, json[oxorany("visuals")][oxorany("world")][oxorany("render")][oxorany("bullet impacts color")]);
    jsonarray4(this->visuals.world.render.hit_marker_color, json[oxorany("visuals")][oxorany("world")][oxorany("render")][oxorany("hit marker color")]);

    this->misc.general.hitsound = json[oxorany("misc")][oxorany("general")][oxorany("hitsound")].get<bool>();
    this->misc.general.thirdperson = json[oxorany("misc")][oxorany("general")][oxorany("thirdperson")].get<bool>();
    this->misc.general.viewmodel = json[oxorany("misc")][oxorany("general")][oxorany("viewmodel")].get<bool>();
    this->misc.general.removals[0] = json[oxorany("misc")][oxorany("general")][oxorany("remove flashbang")].get<bool>();
    this->misc.general.removals[1] = json[oxorany("misc")][oxorany("general")][oxorany("remove smoke")].get<bool>();
    this->misc.general.removals[2] = json[oxorany("misc")][oxorany("general")][oxorany("remove scope")].get<bool>();
    this->misc.general.removals[3] = json[oxorany("misc")][oxorany("general")][oxorany("remove aim punch")].get<bool>();
    this->misc.general.removals[4] = json[oxorany("misc")][oxorany("general")][oxorany("remove scope zoom")].get<bool>();
    this->misc.general.removals[5] = json[oxorany("misc")][oxorany("general")][oxorany("arms")].get<bool>();
    this->misc.general.removals[6] = json[oxorany("misc")][oxorany("general")][oxorany("weapon")].get<bool>();

    this->misc.general.thirdperson_distance = json[oxorany("misc")][oxorany("general")][oxorany("thirdperson distance")].get<float>();
    this->misc.general.fov = json[oxorany("misc")][oxorany("general")][oxorany("camera fov")].get<int>();
    this->misc.general.aspect_ratio_w = json[oxorany("misc")][oxorany("general")][oxorany("aspect ratio")].get<int>();
    this->misc.general.viewmodel_pos.x = json[oxorany("misc")][oxorany("general")][oxorany("viewmodel x")].get<float>();
    this->misc.general.viewmodel_pos.y = json[oxorany("misc")][oxorany("general")][oxorany("viewmodel y")].get<float>();
    this->misc.general.viewmodel_pos.z = json[oxorany("misc")][oxorany("general")][oxorany("viewmodel z")].get<float>();

    this->misc.movement.air_strafes = json[oxorany("misc")][oxorany("movement")][oxorany("air strafes")].get<bool>();
    this->misc.movement.fast_stop = json[oxorany("misc")][oxorany("movement")][oxorany("fast stop")].get<bool>();
    this->misc.movement.anti_rollback = json[oxorany("misc")][oxorany("movement")][oxorany("anti rollback")].get<bool>();

    this->misc.movement.air_strafes_speed = json[oxorany("misc")][oxorany("movement")][oxorany("air strafes speed")].get<float>();

    this->misc.general.aspect_ratio_update = true;
    if(this->visuals.world.env.world_color)
        this->visuals.world.env.world_color_update = true;
}

void config_t::remove(const uint8_t& index) noexcept {
    if(this->array[index].empty())
        return;
    std::string path = __config_path; path+=this->array[index];
    std::remove(path.c_str());
    this->array[index].clear();
}