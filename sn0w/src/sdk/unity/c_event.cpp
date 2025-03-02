#include "c_event.h"
#include "../globals.hpp"

event_type CEvent::getType() const noexcept {
    static event_type(*func)(const CEvent*);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Event"), oxorany("UnityEngine"), oxorany("UnityEngine.IMGUIModule.dll")), oxorany("get_rawType"), 0)->methodPointer;
    return func(this);
}

CEvent* CEvent::getCurrent() noexcept {
    static CEvent*(*func)();
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Event"), oxorany("UnityEngine"), oxorany("UnityEngine.IMGUIModule.dll")), oxorany("get_current"), 0)->methodPointer;
    return func();
}