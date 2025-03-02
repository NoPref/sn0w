#pragma once
#include <stdint.h>
#include <vector>
#include "t_array.h"

template <typename T>
struct list_t {
char pad[sizeof(void*)*2];
public:
    array_t<T>* m_aItems;
    int32_t m_iSize;
    int32_t m_iVersion;

    T& get(const uint32_t& index) noexcept {
        return this->m_aItems->get(index);
    }

    const T& get(const uint32_t& index) const noexcept {
        return this->m_aItems->get(index);
    }

    bool isValid() const noexcept {
        if(this->m_iSize > 0) {
            if(this->m_aItems != NULL) {
                return this->m_aItems->isValid();
            }
        }
        return false;
    }

    uint32_t getSize() const noexcept {
        if(this->isValid()) {
            return this->m_aItems->m_iCapacity;
        }
        return 0;
    }

    std::vector<T> toVector() const noexcept {
        std::vector<T> ret{};
        if(this->isValid()) {
            for(uint32_t i=0;i<this->getSize();++i) {
                ret.emplace_back(this->get(i));
            }
        }
        return std::move(ret);
    }
};