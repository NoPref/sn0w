#pragma once
#include "../singleton.hpp"
#include "../includes/imgui/include.h"
#include "../includes/oxorany/include.h"

namespace ui {
    struct page_t {
    public:
        bool* m_pVar;
        ImVec4 m_color;
        char m_szLabel[256];

        page_t() = default;
        ~page_t() = default;

        page_t(bool* _var, const char* _label) noexcept {
            this->m_pVar = _var;
            this->m_color = {1.f, 1.f, 1.f, 0.25f};
            strcpy(this->m_szLabel, _label);
        }
    };
};

class CUserInterface : public CSingleton<CUserInterface> {
private:
    bool m_bInited{};
    ImRect m_bounds{{1200, 700}, {1500, 850}};
    ImVec2 m_currentSize{};

    ui::page_t m_pages[7] {
        ui::page_t(NULL, oxorany("ragebot")),
        ui::page_t(NULL, oxorany("exploits")),
        ui::page_t(NULL, oxorany("legitbot")),
        ui::page_t(NULL, oxorany("visuals")),
        ui::page_t(NULL, oxorany("misc")),
        ui::page_t(NULL, oxorany("changer")),
        ui::page_t(NULL, oxorany("config"))
        //ui::page_t(NULL, oxorany("debug"))
    };
    
public:
    bool m_bOpen = true;
    float m_dpiScale = 1.f;
	float m_accent[4] = { 1.f, 1.f, 1.f, 1.f };
    ImGuiStyle* style{};

    void init() noexcept;
    static void handleTouches() noexcept;
    static void render() noexcept;

    void beginWindow(const char* const& szName, const ImRect& bounds, ImGuiWindowFlags flags = ImGuiWindowFlags_None) noexcept;
    void endWindow() noexcept;
    void border(ImDrawList* const pDrawlist) noexcept;
	void beginChild(const char* const& szLabel, const ImVec2& vecSize, ImGuiChildFlags childFlags = ImGuiChildFlags_None, ImGuiWindowFlags windowFlags = ImGuiWindowFlags_None) noexcept;
	void endChild() noexcept;
    void checkbox(const char* const& szLabel, bool* const& pVar) noexcept;
    void sliderscalar(const char* const& szLabel, const ImGuiDataType& dataType, void* pData, void* pMin, void* pMax, const char* szFormat, ImGuiSliderFlags flags = ImGuiSliderFlags_None) noexcept;
    void sliderint(const char* const& szLabel, int32_t* const& pVar, const int32_t& iMin, const int32_t& iMax, const char* szFormat = "%d") noexcept;
    void slideruint8(const char* const& szLabel, uint8_t* const& pVar, const uint8_t& uMin, const uint8_t& uMax, const char* szFormat = "%u") noexcept;
    void sliderint16(const char* const& szLabel, int16_t* const& pVar, const int16_t& iMin, const int16_t& iMax, const char* szFormat = "%d") noexcept;
    void slideruint16(const char* const& szLabel, uint16_t* const& pVar, const uint16_t& uMin, const uint16_t& uMax, const char* szFormat = "%u") noexcept;
    void sliderfloat(const char* const& szLabel, float* const& pVar, const float& fMin, const float& fMax, const char* szFormat = "%.1f") noexcept;
    bool button(const char* const& szLabel, const ImVec2& vecSize, ImGuiButtonFlags flags = ImGuiButtonFlags_None) noexcept;
    bool page(const char* const& szLabel, const bool& bSelected, ImVec4& srcCol, const ImVec4& dstCol, bool bLine = true, bool bVerdanaBold = true, ImVec2 vecSize = ImVec2(0,0), ImGuiSelectableFlags flags = ImGuiSelectableFlags_None) noexcept;
    bool page(ui::page_t* const page, const bool& bSelected, const ImVec4& dstCol, bool bLine = true, bool bVerdanaBold = true, ImVec2 vecSize = ImVec2(0,0), ImGuiSelectableFlags flags = ImGuiSelectableFlags_None) noexcept;
    bool beginCombo(const char* const& szLabel, const char* const& szPreviewValue, ImGuiComboFlags flags = ImGuiComboFlags_None) noexcept;
    void endCombo() noexcept;
    void multiCombo(const char* const& szLabel, ui::page_t* const& aPages, const uint16_t& nSize) noexcept;
    void colorpick4(const char* const& szLabel, float* const& faCol, bool sameLine = true, ImGuiColorEditFlags flags = ImGuiColorEditFlags_None) noexcept;
    void colorpick3(const char* const& szLabel, float* const& faCol, bool sameLine = true, ImGuiColorEditFlags flags = ImGuiColorEditFlags_None) noexcept;
    void inputText(const char* const& szLabel, char* pBuffer, const uint32_t& nBuffer, ImGuiInputTextFlags flags = ImGuiInputTextFlags_None) noexcept;
    void horPad() noexcept;
    void verPad() noexcept;
    
    void update() noexcept;
    void main() noexcept;
    void line() noexcept;
    void ragebot() noexcept;
    void exploits() noexcept;
    void legitbot() noexcept;
    void visuals() noexcept;
    void misc() noexcept;
    void changer() noexcept;
    void config() noexcept;
    void debug() noexcept;
};