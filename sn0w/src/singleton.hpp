#pragma once
#include <stdint.h>
#include <stddef.h>

template<typename T>
class CSingleton {
public:
    static T* m_obj;

    static T* inst() noexcept {
        if(CSingleton::m_obj == NULL) {
            static T obj;
            CSingleton::m_obj = &obj;
        }
        return CSingleton::m_obj;
    }
};

template<typename T>
T* CSingleton<T>::m_obj = NULL;