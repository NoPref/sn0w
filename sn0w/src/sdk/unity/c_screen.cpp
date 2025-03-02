#include "c_screen.h"
#include "../globals.hpp"

resolution_t CScreen::getResolution() noexcept {
    static resolution_t(*func)();
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Screen"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("get_currentResolution"), 0)->methodPointer;
    return func();
}

void CScreen::setResolution(const int32_t& w, const int32_t& h) noexcept {
    static void(*func)(int32_t,int32_t,bool);
    if(func == NULL)
        func = (decltype(func))g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("Screen"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")), oxorany("SetResolution"), 3)->methodPointer;
    func(w, h, true);
}

void CScreen::setResolution(const resolution_t& res) noexcept {
    CScreen::setResolution(res.m_iWidth, res.m_iHeight);
}