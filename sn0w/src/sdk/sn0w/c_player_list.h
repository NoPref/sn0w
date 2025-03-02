#pragma once
#include <stdint.h>
#include "../unity/common/t_dictionary.h"

class CPlayerController;
class CLocalPlayer;
class CPhotonPlayer;
class CPhotonView;

class CPlayerList {
public:
    dictionary_t<int32_t, CPlayerController*>* m_data;
    CPhotonPlayer* m_localPhoton;
    CLocalPlayer* m_local;
    
    CPlayerList() = default;
    ~CPlayerList() = default;

    bool isEmpty() const noexcept;
    uint32_t getSize() const noexcept;
    CPlayerController*& operator[](const uint32_t& index) const noexcept;
    CPlayerController*& get(const uint32_t& index) const noexcept;
};