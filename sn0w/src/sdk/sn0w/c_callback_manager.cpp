#include "c_callback_manager.h"
#include "../globals.hpp"

void C_CallbackManager::init() noexcept {
    this->add((void*)&g.vars.update,             callback_event_game_frame,  true);
    this->add((void*)&g.hooks.game.update,       callback_event_game_frame,  true);

    this->add((void*)&g.sn0w.render,             callback_event_render,      true);
    this->add((void*)&g.sn0w.createMove,         callback_event_create_move, true);
    this->add((void*)&g.sn0w.lateUpdate,         callback_event_late_update, true);
    this->add((void*)&g.sn0w.update,             callback_event_game_frame,  true);
    this->add((void*)&g.sn0w.hit,                callback_event_hit,         true);
    //this->add((void*)&g.sn0w.gui,                callback_event_gui,         true);
    //this->add((void*)&g.sn0w.repaint,            callback_event_gui_repaint, true);
}

bool C_CallbackManager::add(const void* const& pFunc, const callback_event& event, bool bIgnoreChecks) noexcept {
    if(pFunc != NULL) {
        if(!bIgnoreChecks) {
            if(!this->m_callbacks.empty()) {
                for(uint16_t i=0;i<this->m_callbacks.size();++i) {
                    if(pFunc == this->m_callbacks[i].m_pFunc)
                        return false;
                }

            }
        }
        this->m_callbacks.emplace_back(callbacks::callback_t{pFunc, event});
        return true;
    }
    return false;
}

void C_CallbackManager::remove(const void* const& pFunc, const callback_event& event) noexcept {
    if(pFunc != NULL) {
        if(!this->m_callbacks.empty()) {
            for(uint16_t i=0;i<this->m_callbacks.size();++i) {
                if(this->m_callbacks[i].m_pFunc == pFunc)
                    this->m_callbacks.erase(this->m_callbacks.begin() + i);
            }
        }
    }
}

void C_CallbackManager::call(const callback_event& event) noexcept {
    if(!this->m_callbacks.empty()) {
        for(uint16_t i=0;i<this->m_callbacks.size();++i) {
            void(*func)() = (decltype(func))this->m_callbacks[i].m_pFunc;
            if(func != NULL && this->m_callbacks[i].m_event == event) {
                func();
            }
        }
    }
}