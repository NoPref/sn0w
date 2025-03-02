#include "c_renderer.hpp"

void CGlobalRenderer::init() noexcept {
    this->engine = CEngineRenderer::inst();
    //this->engine->init()
    this->imgui = CImGuiRenderer::inst();
    //this->imgui->init();
}