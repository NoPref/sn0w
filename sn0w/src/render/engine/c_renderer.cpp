#include "c_renderer.hpp"
#include "../globals.hpp"

void CEngineRenderer::init() noexcept {
    //OnGUI hook
    MethodInfo* pOnGUI = g.il2cpp.getMethod(g.il2cpp.getClass(oxorany("PhotonLagSimulationGui"), oxorany(""), oxorany("Assembly-CSharp.dll")), oxorany("OnGUI"), 0);
    pOnGUI->methodPointer = (Il2CppMethodPointer)&g.hooks.engine.onGUI;

    //new texture for rendering
    this->m_mainTexture = CTexture2D::getWhiteTexture();

    //new obj for OnGUI hook
    this->m_object = (CGameObject*)g.il2cpp.object_new(g.il2cpp.getClass(oxorany("GameObject"), oxorany("UnityEngine"), oxorany("UnityEngine.CoreModule.dll")));
    this->m_object->create(oxorany("_"));
    this->m_object->addComponent(type_t::find(oxorany("PhotonLagSimulationGui, Assembly-CSharp.dll")));
    this->m_object->dontDestroyOnLoad();
}

void CEngineRenderer::line(const vec2_t& vecStart, const vec2_t& vecEnd, const color_t& color, float thickness) {

}

void CEngineRenderer::rect(const vec2_t& vecMin, const vec2_t& vecMax, const color_t& color, float thickness, float roundness) {
    CGUI::drawTexture(rect_t{vecMin.x, vecMin.y, vecMax.x - vecMin.x, vecMax.y - vecMin.y}, this->m_mainTexture, 0, true, 1.f, color, thickness, roundness);
}

void CEngineRenderer::rectFilled(const vec2_t& vecMin, const vec2_t& vecMax, const color_t& color) {
    CGUI::setColor(color);
    CGUI::drawTexture(rect_t{vecMin.x, vecMin.y, vecMax.x - vecMin.x, vecMax.y - vecMin.y}, this->m_mainTexture);
}

void CEngineRenderer::circle(const vec2_t& vecCoords, const float& radius, const color_t& color, float thickness) {
    CGUI::drawTexture(rect_t{vecCoords.x - (radius / 2), vecCoords.y - (radius / 2), radius, radius}, this->m_mainTexture, 0, true, 1.f, color, thickness, 90.f);
}

void CEngineRenderer::text(const vec2_t& vecMin, const vec2_t& vecSize, const color_t& color, const string_t* u16str) {
    CGUI::setColor(color);
    CGUI::drawLabel(rect_t{vecMin.x, vecMin.y, vecSize.x, vecSize.y}, u16str);
}
void CEngineRenderer::text(const vec2_t& vecMin, const vec2_t& vecSize, const color_t& color, const char* const& szText) {
    this->text(vecMin, vecSize, color, string_t::create(szText));
}

void CEngineRenderer::text(const vec2_t& vecCoords, const color_t& color, const string_t* u16str) {
    // this->text(vecCoords, vec2_t{g.window.m_iWidth, g.window.m_iHeight}, color, u16str);
}

void CEngineRenderer::text(const vec2_t& vecCoords, const color_t& color, const char* const& szText) {
    this->text(vecCoords, color, string_t::create(szText));
}