#include "c_player_list.h"
#include "c_localplayer.h"
#include "../includes/il2cpp/il2cpp-api.h"
#include "../photonengine/c_photonplayer.h"
#include "../so2/c_playercontroller.h"
#include "../offsets.hpp"
#include "../globals.hpp"

bool CPlayerList::isEmpty() const noexcept {
    if(this->m_data != NULL) {
        return !this->m_data->isValid();
    }
    return true;
}

uint32_t CPlayerList::getSize() const noexcept {
    if(this->m_data != NULL) {
        return this->m_data->getSize();
    }
    return 0;
}

CPlayerController*& CPlayerList::operator[](const uint32_t& index) const noexcept {
    return this->m_data->get(index).m_value;
}

CPlayerController*& CPlayerList::get(const uint32_t& index) const noexcept {
    return this->m_data->get(index).m_value;
}