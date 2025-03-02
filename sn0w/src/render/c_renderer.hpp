#pragma once
#include <stdint.h>
#include "engine/c_renderer.hpp"
#include "imgui/c_renderer.hpp"
#include "../singleton.hpp"

class CGlobalRenderer {
public:
    CEngineRenderer* engine;
    CImGuiRenderer* imgui;

    CGlobalRenderer() = default;
    ~CGlobalRenderer() = default;

    void init() noexcept;
};