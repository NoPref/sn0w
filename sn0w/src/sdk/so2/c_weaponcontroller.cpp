#include "c_weaponcontroller.h"
#include "../includes/il2cpp/il2cpp-api.h"
#include "../globals.hpp"

weapon_type CWeaponController::getType() const noexcept {
    return this->m_parameters->getType();
}

std::string CWeaponController::getName() const noexcept {
    return std::move(this->m_parameters->getName());
}

char CWeaponController::getIcon() const noexcept {
    return this->m_parameters->getIcon();
}

weapon_type CWeaponParameters::getType() const noexcept {
    weapon_type ret = weapon_type_none;
    weapon_id id = this->m_id;

    if(id >= weapon_id_g22 && id <= weapon_id_berettas) 
        ret = weapon_type_pistol;

    if(id >= weapon_id_ump45 && id <= weapon_id_mac10) 
        ret = weapon_type_smg;

    if(id >= weapon_id_val && id <= weapon_id_fnfal) 
        ret = weapon_type_rifle;

    if(id == weapon_id_fabm || id == weapon_id_sm1014 || id == weapon_id_spas) 
        ret = weapon_type_shotgun;

    if(id == weapon_id_m60) 
        ret = weapon_type_heavy;

    if(id >= weapon_id_awm && id <= weapon_id_m110)
        ret = weapon_type_sniper;
    
    if(id >= weapon_id_grenade_he && id <= weapon_id_grenade_incendiary)
        ret = weapon_type_grenade;
    
    if(id >= weapon_id_knife && id <= weapon_id_knife_sting)
        ret = weapon_type_knife;

    return ret;
}

std::string CWeaponParameters::getName() const noexcept {
    return std::move(this->m_sDisplayName->toUTF8());
}

char CWeaponParameters::getIcon() const noexcept {
    char ret;

    switch(this->m_id) {
        case weapon_id_g22: {
            ret = 'D';
            break;
        }
        case weapon_id_usp: {
            ret = 'G';
            break;
        }
        case weapon_id_p350: {
            ret = 'F';
            break;
        }
        case weapon_id_deagle: {
            ret = 'A';
            break;
        }
        case weapon_id_tec9: {
            ret = 'H';
            break;
        }
        case weapon_id_fiveseven: {
            ret = 'C';
            break;
        }
        case weapon_id_berettas: {
            ret = 'B';
            break;
        }
        case weapon_id_ump45: {
            ret = 'L';
            break;
        }
        case weapon_id_mp7: {
            ret = 'N';
            break;
        }
        case weapon_id_p90: {
            ret = 'P';
            break;
        }
        case weapon_id_mp5: {
            ret = 'M';
            break;
        }
        case weapon_id_mac10: {
            ret = 'K';
            break;
        }
        case weapon_id_val: {
            ret = 'W';
            break;
        }
        case weapon_id_m4a1: {
            ret = 'T';
            break;
        }
        case weapon_id_akr: {
            ret = 'W';
            break;
        }
        case weapon_id_akr12: {
            ret = 'V';
            break;
        }
        case weapon_id_m4: {
            ret = 'S';
            break;
        }
        case weapon_id_m16: {
            ret = 'U';
            break;
        }
        case weapon_id_famas: {
            ret = 'R';
            break;
        }
        case weapon_id_fnfal: {
            ret = 'Q';
            break;
        }
        case weapon_id_awm: {
            ret = 'Z';
            break;
        }
        case weapon_id_m40: {
            ret = 'a';
            break;
        }
        case weapon_id_m110: {
            ret = 'Y';
            break;
        }
        case weapon_id_sm1014: {
            ret = 'b';
            break;
        }
        case weapon_id_fabm: {
            ret = 'e';
            break;
        }
        case weapon_id_spas: {
            ret = 'e';
            break;
        }
        case weapon_id_m60: {
            ret = 'f';
            break;
        }
        case weapon_id_knife: {
            ret = '[';
            break;
        }
        case weapon_id_knife_bayonet: {
            ret = '5';
            break;
        }
        case weapon_id_knife_karambit: {
            ret = '4';
            break;
        }
        case weapon_id_knife_jkommando: {
            ret = '0';
            break;
        }
        case weapon_id_knife_tanto: {
            ret = '7';
            break;
        }
        case weapon_id_knife_daggers: {
            ret = '9';
            break;
        }
        case weapon_id_knife_fang: {
            ret = '0';
            break;
        }
        case weapon_id_knife_butterfly: {
            ret = '8';
            break;
        }
        case weapon_id_knife_flip: {
            ret = '2';
            break;
        }
        case weapon_id_knife_kunai: {
            ret = '6';
            break;
        }
        case weapon_id_knife_scorpion: {
            ret = '3';
            break;
        }
        case weapon_id_grenade_he: {
            ret = 'j';
            break;
        }
        case weapon_id_grenade_smoke: {
            ret = 'k';
            break;
        }
        case weapon_id_grenade_flash: {
            ret = 'i';
            break;
        }
        case weapon_id_grenade_molotov: {
            ret = 'l';
            break;
        }
        case weapon_id_grenade_incendiary: {
            ret = 'n';
            break;
        }
        case weapon_id_bomb: {
            ret = 'o';
            break;
        }
        default: {
            ret = ' ';
            break;
        }
    }
    
    return ret;
}