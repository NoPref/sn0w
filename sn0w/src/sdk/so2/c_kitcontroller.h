#pragma once
#include "c_weaponcontroller.h"

enum defuse_kit_state : uint8_t {
	defuse_kit_state_none     = 0,
	defuse_kit_state_defusing = 1,
};

#pragma pack(1)
class CDefuseKitController : public CWeaponController {
public:
    float m_fProgress;
    defuse_kit_state m_state;
    defuse_kit_state m_oldState;
    char pad7[0x2];
    void* m_soundController;
};
#pragma pack()