#pragma once
#include <stdint.h>
#include <vector>
#include "t_array.h"

template<typename K, typename V>
struct dictionary_t {

struct entry_t {
    int32_t m_iHashCode;
    int32_t m_iNext;
    K m_key;
    V m_value;

    entry_t() = default;
    ~entry_t() = default;
};

char pad[sizeof(void*)*2];
public:
    array_t<int32_t>* m_aBuckets;
    array_t<entry_t>* m_aEntries;
    int32_t m_iCount;
    int32_t m_iVersion;
    int32_t m_iFreeList;
    int32_t m_iFreeCount;
    void* m_compare;
    array_t<K>* m_aKeys;
    array_t<V>* m_aValues;
    void* m_syncRoot;

    entry_t& get(const uint32_t& index) noexcept {
        return this->m_aEntries->get(index);
    }

    const entry_t& get(const uint32_t& index) const noexcept {
        return this->m_aEntries->get(index);
    }

    bool isValid() const noexcept {
        if(this->m_iCount > 0) {
            if(this->m_aEntries != NULL) {
                return this->m_aEntries->isValid();
            }
        }
        return false;
    }

    uint32_t getSize() const noexcept {
        if(this->isValid()) {
            return this->m_aEntries->m_iCapacity;
        }
        return 0;
    }

    V& tryGetValue(const K& key) const noexcept {
        for(uint32_t i=0;i<this->getSize();++i) {
            if(key == this->get(i).m_key)
                return this->get(i).m_value;
        }
        return {};
    }

    std::vector<V> toVector() const noexcept {
        std::vector<V> ret{};
        if(this->isValid()) {
            for(uint32_t i=0;i<this->getSize();++i) {
                ret.emplace_back(this->get(i).m_value);
            }
        }
        return std::move(ret);
    }

};