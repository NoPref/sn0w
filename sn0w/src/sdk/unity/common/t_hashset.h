#pragma once
#include <stdint.h>
#include <vector>
#include "t_array.h"

template<typename T>
struct hashset_t {
    
struct slot_t {
    int32_t m_iHashcode;
    int32_t m_iNext;
    T m_value;

    slot_t() = default;
    ~slot_t() = default;
};

char pad[sizeof(void*)*2];
public:
    array_t<int>* m_aBuckets;
    array_t<slot_t>* m_aSlots;
    int32_t m_iCount;
    int32_t m_iLastIndex;
    int32_t m_iFreeList;
    void* m_comparer;
    int32_t m_iVersion;
    void* m_info;

    slot_t& get(const uint32_t& index) noexcept {
        return this->m_aSlots->get(index);
    }

    const slot_t& get(const uint32_t& index) const noexcept {
        return this->m_aSlots->get(index);
    }

    bool isValid() const noexcept {
        if(this->m_iCount > 0) {
            if(this->m_aSlots != NULL) {
                return this->m_aSlots->isValid();
            }
        }
        return false;
    }

    uint32_t getSize() const noexcept {
        if(this->isValid()) {
            return this->m_aSlots->m_iCapacity;
        }
        return 0;
    }

    std::vector<T> toVector() const noexcept {
        std::vector<T> ret{};
        if(this->isValid()) {
            for(uint32_t i=0;i<this->getSize();++i) {
                ret.emplace_back(this->get(i).m_value);
            }
        }
        return std::move(ret);
    }

};