#include "t_touch.h"
#include "../globals.hpp"

touch_t touch_t::getTouch(const uint8_t& index) noexcept {
    static touch_t(*func)(uint8_t);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Input"), oxorany("UnityEngine"), oxorany("UnityEngine.InputLegacyModule.dll")), oxorany("GetTouch"), 1)->methodPointer;
    return func(index);
}