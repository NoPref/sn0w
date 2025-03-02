#pragma once
#include <stdint.h>
#include "../singleton.hpp"
#include "../sdk/unity/common/include.h"

class C_Changer : public CSingleton<C_Changer> {
public:
    C_Changer() = default;
    ~C_Changer() = default;
};