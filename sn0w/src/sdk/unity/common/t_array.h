#pragma once
#include <stdint.h>
#include <vector>

template <typename T>
struct array_t {
char pad[sizeof(void*)*2];
public:
    void* m_bounds;
    int32_t m_iCapacity;
    T m_aItems[0]; 

    T& get(const uint32_t& index) noexcept {
        return this->m_aItems[index];
    }

    const T& get(const uint32_t& index) const noexcept {
        return this->m_aItems[index];
    }


    bool isValid() const noexcept {
        if(this->m_iCapacity > 0) {
            return this->m_aItems != NULL;
        }
        return false;
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