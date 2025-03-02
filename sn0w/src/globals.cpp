#include <dlfcn.h>
#include <unistd.h>
#include <android/log.h>
#include "globals.hpp"

void globals_t::entry() {
    this->hi = CHideImports::inst();
    if(!this->hi->init())
        return;
    if(!this->hi->loadSym())
        return;
    this->hooks.libc.init();
    this->callbacks.init();
    this->renderer.init();
    this->sn0w.init();
}

void globals_t::libUnityEntry() {
}

void globals_t::libil2cppEntry() {
    g.il2cpp.init();
    g.hooks.engine.init();
}

void globals_t::gameEntry() {
    this->screen = CScreen::getResolution();
    this->hooks.engine.initRender();
    this->hooks.game.initLateUpdate();
    this->sn0w.chams->init();
}