#include "c_photonplayer.h"
#include "../globals.hpp"

int CPhotonPlayer::getHealth() const noexcept {
    return this->getProperty<int>(oxorany("health"));
}

int CPhotonPlayer::getArmor() const noexcept {
    return this->getProperty<int>(oxorany("armor"));
}

team CPhotonPlayer::getTeam() const noexcept {
    return this->getProperty<team>(oxorany("team"));
}

bool CPhotonPlayer::getHasHelmet() const noexcept {
    return this->getProperty<bool>(oxorany("helmet"));
}

bool CPhotonPlayer::getIsUntouchable() const noexcept {
    return this->getProperty<bool>(oxorany("untouchable"));
}