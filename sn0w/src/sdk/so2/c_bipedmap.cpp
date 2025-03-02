#include "c_bipedmap.h"

CTransform* CBipedMap::getBone(const bip& num) noexcept {
    return this->m_data[num];
}