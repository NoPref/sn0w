#include "c_weaponrycontroller.h"
#include "c_weaponcontroller.h"
#include "../includes/il2cpp/il2cpp-api.h"

bool CWeaponryController::hasWeapon(const weapon_id& id) const noexcept {
    const dictionary_t<uint8_t, CWeaponController*>* dpSlots = this->m_dWeaponSlots;
    if(dpSlots != NULL) {
        if(dpSlots->isValid()) {
            for(uint8_t i=0;i<dpSlots->getSize();++i) {
                const CWeaponController* pWeapon = dpSlots->get(i).m_value;
                if(pWeapon != NULL) {
                    if(pWeapon->m_parameters != NULL) {
                        if(pWeapon->m_parameters->m_id == id) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}