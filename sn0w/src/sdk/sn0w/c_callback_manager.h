#pragma once
#include <stdint.h>
#include <vector>

enum callback_event : uint8_t {
    callback_event_main        = 0, //deprecated
    callback_event_late_update = 1, //calling after every frame
    callback_event_create_move = 2, //calling every tick
    callback_event_render      = 3, //calling every frame (egl) 
    callback_event_game_frame  = 4, //calling every frame (get_touchCount)
    callback_event_hit         = 5, //calling after hit player (server)
    callback_event_gui         = 6, //calling every frame (OnGUI)
    callback_event_gui_repaint = 7, //calling every frame when need to repaint (OnGUI)
};

namespace callbacks {
    struct callback_t {
        const void* m_pFunc;
        callback_event m_event;

        callback_t() = default;
        ~callback_t() = default;

        callback_t(const void* const& ptr, const callback_event& event) noexcept {
            this->m_pFunc = ptr;
            this->m_event = event;
        }
    };
};

class C_CallbackManager {
private:
    std::vector<callbacks::callback_t> m_callbacks{};
public:
    C_CallbackManager() = default;
    ~C_CallbackManager() = default;

    void init() noexcept;
    
    bool add(const void* const& pFunc, const callback_event& event, bool bIgnoreChecks = false) noexcept;
    void remove(const void* const& pFunc, const callback_event& event) noexcept;
    
    void call(const callback_event& event) noexcept;
};