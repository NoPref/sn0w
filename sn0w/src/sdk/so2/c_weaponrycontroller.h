#pragma once
#include <stdint.h>
#include "../unity/common/include.h"
#include "common/include.h"

class CPlayerController;
class CMecanimController;
class CWeaponController;
class CDefuseKitController;

#pragma pack(1)
class CWeaponryController {
char pad[0x58];
public:
    dictionary_t<uint8_t, CWeaponController*>* m_dWeaponSlots;
    list_t<CWeaponController*>* m_lWeapons;
    list_t<void*>* m_list1;
    CPlayerController* m_player;
    CMecanimController* m_mecanim;
    uint8_t m_iCurrentSlot;
    bool m_bFPSView;
    char pad3[0x6];
    void* m_pickUpController;
    CDefuseKitController* m_kit;
    CWeaponController* m_currentWeapon;
    bool m_bool1;
    bool m_bool2;
    char pad4[0x2];
    float m_fLocalTime;
    float m_fDeltaTime;
    char pad5[0x4];
    void* m_weaponManager;

    bool hasWeapon(const weapon_id& id) const noexcept;

};
#pragma pack()