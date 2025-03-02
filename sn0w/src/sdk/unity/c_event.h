#pragma once
#include <stdint.h>

enum event_type : uint8_t {
    event_type_mouse_down         = 0,
	event_type_mouse_up           = 1,
	event_type_mouse_move         = 2,
	event_type_mouse_drag         = 3,
	event_type_key_down           = 4,
	event_type_key_up             = 5,
	event_type_scroll_wheel       = 6,
	event_type_repaint            = 7,
	event_type_layout             = 8,
	event_type_drag_updated       = 9,
	event_type_drag_perform       = 10,
	event_type_drag_exited        = 15,
	event_type_ignore             = 11,
	event_type_used               = 12,
	event_type_validate_command   = 13,
	event_type_execute_command    = 14,
	event_type_context_click      = 16,
	event_type_mouse_enter_window = 20,
	event_type_mouse_leave_window = 21,
	event_type_touch_down         = 30,
	event_type_touch_up           = 31,
	event_type_touch_move         = 32,
	event_type_touch_enter        = 33,
	event_type_touch_leave        = 34,
	event_type_touch_stationary   = 35,
};

class CEvent {
public:
    event_type getType() const noexcept;
    static CEvent* getCurrent() noexcept;
};