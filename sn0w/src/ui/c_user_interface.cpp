#include "c_user_interface.hpp"
#include "../globals.hpp"

void CUserInterface::init() noexcept {
    this->style = &ImGui::GetStyle();

    ImGui::StyleColorsDark();

    this->style->ScrollbarRounding = 0.f;
    this->style->GrabMinSize = 0;

    this->style->Colors[ImGuiCol_WindowBg]          = ImColor(20, 20, 20, 255);
    this->style->Colors[ImGuiCol_ChildBg]           = ImColor(16, 16, 16, 255);
    this->style->Colors[ImGuiCol_FrameBg]           = style->Colors[ImGuiCol_WindowBg];
    this->style->Colors[ImGuiCol_Border]            = ImColor(0, 0, 0, 255);
    this->style->Colors[ImGuiCol_Header]            = ImColor(255, 255, 255, 0);
    this->style->Colors[ImGuiCol_HeaderHovered]     = ImColor(255, 255, 255, 0);
    this->style->Colors[ImGuiCol_HeaderActive]      = ImColor(255, 255, 255, 0);
    this->style->Colors[ImGuiCol_Button]            = style->Colors[ImGuiCol_WindowBg];
    this->style->Colors[ImGuiCol_ButtonHovered]     = ImColor(16, 16, 16, 255);
    this->style->Colors[ImGuiCol_ButtonActive]      = ImColor(14, 14, 14, 255);
    this->style->Colors[ImGuiCol_PopupBg]           = style->Colors[ImGuiCol_WindowBg];
    this->style->Colors[ImGuiCol_TextSelectedBg]    = ImColor(255, 255, 255, 20);
    this->style->Colors[ImGuiCol_ResizeGrip]        = ImColor(40, 40, 40, 255);
    this->style->Colors[ImGuiCol_ResizeGripActive]  = ImColor(40, 40, 40, 255);
    this->style->Colors[ImGuiCol_ResizeGripHovered] = ImColor(40, 40, 40, 255);
}

void CUserInterface::handleTouches() noexcept {
    ImGuiIO& io = ImGui::GetIO();
    if(g.hooks.orig.engine.getTouchCount() > 0) {
        const touch_t touch = touch_t::getTouch(0);
        io.MousePos = ImVec2(touch.m_vecCoords.x, g.window.m_iHeight - touch.m_vecCoords.y);
        if(touch.m_phase == touch_phase_began || touch.m_phase == touch_phase_stationary) {
            io.MouseDown[0] = true;
        } else if(touch.m_phase == touch_phase_canceled || touch.m_phase == touch_phase_ended) {
            io.MouseDown[0] = false;
        }
    } else {
        io.MouseDown[0] = false;
    }
}


void CUserInterface::beginWindow(const char* const& szName, const ImRect& bounds, ImGuiWindowFlags flags) noexcept {
    //const ImVec2 step {5.f, 50.f};

    ImGui::SetNextWindowSizeConstraints(bounds.Min, bounds.Max);
    ImGui::Begin(szName, NULL, flags);

    /*const ImVec2 curPos = ImGui::GetWindowPos();
    const ImVec2 curSize = ImGui::GetWindowSize();
    ImDrawList* pDrawlist = ImGui::GetWindowDrawList();
    for(uint32_t i=0;i<curSize.x / step.x;++i) {
        pDrawlist->AddLine(ImVec2(curPos.x + (step.x * i), curPos.y), ImVec2(curPos.x + (step.x * i), curPos.y + curSize.y), ImColor(0.f, 0.f, 0.f, 0.3f));
    }*/
    /*for(uint32_t i=0;i<curSize.y / step.y;++i) {
        pDrawlist->AddLine(ImVec2(curPos.x, curPos.y + (step.y * i)), ImVec2(curPos.x + curSize.x, curPos.y + (step.y * i)), ImColor(0.f, 0.f, 0.f, 0.2f));
    }*/
}

void CUserInterface::endWindow() noexcept {
    ImGui::End();
}

//FUCK THIS SHIT NEED RECODE
void CUserInterface::border(ImDrawList* const pDrawlist) noexcept {
    const uint8_t iBorderSize = 7;
    const float fOutlineThick = 1.f;
    const ImVec2 vecMenuSize = ImGui::GetWindowSize();
    const ImVec2 vecMenu = ImGui::GetWindowPos();
    const ImColor borderColLight(180.f / 255, 180.f / 255, 180.f / 255, ((110.f / 255) - (1.f - this->style->Alpha)));
    const ImColor borderCol(0.f, 0.f, 0.f, this->style->Alpha);
    const ImColor outlineCol(0.f, 0.f, 0.f, this->style->Alpha);
    const ImColor alphaCol(0.f, 0.f, 0.f, .1f - (1.f - this->style->Alpha));

    const ImVec2 vecLeftUpper = vecMenu;
    const ImVec2 vecLeftLower = vecLeftUpper + ImVec2(0, vecMenuSize.y);
    const ImVec2 vecRightUpper = vecLeftUpper + ImVec2(vecMenuSize.x, 0);
    const ImVec2 vecRightLower = vecRightUpper + ImVec2(0, vecMenuSize.y);

    //border
    pDrawlist->AddRect(vecLeftUpper + ImVec2(iBorderSize / 2, iBorderSize / 2), vecRightLower - ImVec2(iBorderSize / 2, iBorderSize / 2), borderCol, 0, 0, iBorderSize);

    //border lighting
    pDrawlist->AddRectFilledMultiColor(vecLeftUpper + ImVec2(0, iBorderSize), vecLeftLower + ImVec2(iBorderSize, -iBorderSize), alphaCol, borderColLight, borderColLight, alphaCol);
    pDrawlist->AddRectFilledMultiColor(vecLeftUpper + ImVec2(iBorderSize, 0), vecRightUpper - ImVec2(iBorderSize, -iBorderSize), alphaCol, alphaCol, borderColLight, borderColLight);
    pDrawlist->AddRectFilledMultiColor(vecLeftLower + ImVec2(iBorderSize, -iBorderSize), vecRightLower - ImVec2(iBorderSize, 0), borderColLight, borderColLight, alphaCol, alphaCol);
    pDrawlist->AddRectFilledMultiColor(vecRightUpper - ImVec2(iBorderSize, -iBorderSize), vecRightLower - ImVec2(0, iBorderSize), borderColLight, alphaCol, alphaCol, borderColLight);

    pDrawlist->AddRectFilledMultiColor(vecLeftUpper + ImVec2(0, iBorderSize), vecLeftLower + ImVec2(iBorderSize, -iBorderSize), borderColLight, alphaCol, alphaCol, borderColLight);
    pDrawlist->AddRectFilledMultiColor(vecLeftUpper + ImVec2(iBorderSize, 0), vecRightUpper - ImVec2(iBorderSize, -iBorderSize), borderColLight, borderColLight, alphaCol, alphaCol);
    pDrawlist->AddRectFilledMultiColor(vecLeftLower + ImVec2(iBorderSize, -iBorderSize), vecRightLower - ImVec2(iBorderSize, 0), alphaCol, alphaCol, borderColLight, borderColLight);
    pDrawlist->AddRectFilledMultiColor(vecRightUpper - ImVec2(iBorderSize, -iBorderSize), vecRightLower - ImVec2(0, iBorderSize), alphaCol, borderColLight, borderColLight, alphaCol);

    //angles

    pDrawlist->AddRectFilledMultiColor(vecLeftUpper, vecLeftUpper + ImVec2(iBorderSize, iBorderSize), borderColLight, borderColLight, alphaCol, borderColLight);
    pDrawlist->AddRectFilledMultiColor(vecRightUpper, vecRightUpper - ImVec2(iBorderSize, -iBorderSize), borderColLight, borderColLight, alphaCol, borderColLight);
    pDrawlist->AddRectFilledMultiColor(vecRightLower - ImVec2(iBorderSize, iBorderSize), vecRightLower, alphaCol, borderColLight, borderColLight, borderColLight);
    pDrawlist->AddRectFilledMultiColor(vecLeftLower + ImVec2(iBorderSize, -iBorderSize), vecLeftLower, alphaCol, borderColLight, borderColLight, borderColLight);

    pDrawlist->AddRectFilledMultiColor(vecLeftUpper, vecLeftUpper + ImVec2(iBorderSize, iBorderSize), alphaCol, alphaCol, borderColLight, alphaCol);
    pDrawlist->AddRectFilledMultiColor(vecRightUpper, vecRightUpper - ImVec2(iBorderSize, -iBorderSize), alphaCol, alphaCol, borderColLight, alphaCol);
    pDrawlist->AddRectFilledMultiColor(vecRightLower, vecRightLower - ImVec2(iBorderSize, iBorderSize), alphaCol, alphaCol, borderColLight, alphaCol);
    pDrawlist->AddRectFilledMultiColor(vecLeftLower, vecLeftLower + ImVec2(iBorderSize, -iBorderSize), alphaCol, alphaCol, borderColLight, alphaCol);

    //outline
    pDrawlist->AddRect(vecLeftUpper, vecRightLower, outlineCol);
    pDrawlist->AddRect(vecLeftUpper + ImVec2(iBorderSize, iBorderSize), vecRightLower - ImVec2(iBorderSize, iBorderSize), outlineCol, 0, 0, fOutlineThick);
}

void CUserInterface::beginChild(const char* const& szLabel, const ImVec2& vecSize, ImGuiChildFlags childFlags, ImGuiWindowFlags windowFlags) noexcept {
    const bool bShowLabel = szLabel[0] != '#' && szLabel[1] != '#';
	ImDrawList* const pDrawlist = ImGui::GetWindowDrawList();

	const ImVec2 vecCursor = ImGui::GetCursorPos();
	const ImVec2 vecMenu = ImGui::GetWindowPos();
	const ImVec2 vecMenuSize = ImVec2(vecSize.x <= 0 ? ImGui::GetContentRegionAvail().x : vecSize.x, vecSize.y <= 0 ? ImGui::GetContentRegionAvail().y : vecSize.y);
	const ImColor childBg = (ImColor)(this->style->Colors[ImGuiCol_ChildBg] - ImVec4(0.f, 0.f, 0.f, 1.f - this->style->Alpha));
	const ImColor borderCol = (ImColor)(this->style->Colors[ImGuiCol_Border] - ImVec4(0.f, 0.f, 0.f, 1.f - this->style->Alpha));

    if (bShowLabel) 
	    pDrawlist->AddRectFilled(vecMenu + vecCursor, vecMenu + vecCursor + vecMenuSize, childBg);/*background*/
    
    //pDrawlist->AddRectFilledMultiColor(vecMenu + vecCursor, vecMenu + vecCursor + ImVec2(vecMenuSize.x, 20.f), ImColor(0.f, 0.f, 0.f, 0.25f), ImColor(0.f, 0.f, 0.f, 0.25f), ImColor(0,0,0,0), ImColor(0,0,0,0));

    if(childFlags & ImGuiChildFlags_Border)
        pDrawlist->AddRect(vecMenu + vecCursor, vecMenu + vecCursor + vecMenuSize, borderCol);/*outline*/

    if (bShowLabel) {
        ImGui::PushFont(::g.renderer.imgui->m_fonts.ui.verdana_bold_child);
        const ImVec2 vecLabelSize = ImGui::CalcTextSize(szLabel);
        pDrawlist->AddText(vecMenu + vecCursor + ImVec2(20, -vecLabelSize.y / 2), ImColor(1.f, 1.f, 1.f, this->style->Alpha), szLabel);
    }

    ImGui::BeginChild(szLabel, vecSize, childFlags, (bShowLabel ? ImGuiWindowFlags_NoBackground : ImGuiWindowFlags_None) | windowFlags);
    if (bShowLabel)
        ImGui::PopFont();
}

void CUserInterface::endChild() noexcept {
    ImGui::EndChild();
}

void CUserInterface::checkbox(const char* const& szLabel, bool* const& pVar) noexcept {
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return;

    ImGuiContext& g = *GImGui;
    const ImGuiID id = window->GetID(szLabel);
    const ImVec2 label_size = ImGui::CalcTextSize(szLabel, NULL, true);

    const float square_sz = (label_size.y / 2);
    const ImVec2 pos = window->DC.CursorPos;
    const ImRect total_bb(pos, pos + ImVec2(g.Style.WindowPadding.y + square_sz + label_size.x, label_size.y));

    //ImGui::GetForegroundDrawList()->AddRect(total_bb.Min, total_bb.Max, ImColor(255, 255, 255));

    ImGui::ItemSize(total_bb, 0);
    if (!ImGui::ItemAdd(total_bb, id))
    {
        IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | (*v ? ImGuiItemStatusFlags_Checked : 0));
        return;
    }

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);
    if (pressed)
    {
        *pVar = !(*pVar);
        ImGui::MarkItemEdited(id);
    }

    const ImRect check_bb(ImVec2(pos.x, pos.y + (label_size.y / 2 - square_sz / 2)), ImVec2(pos.x + square_sz, pos.y + (label_size.y / 2 + square_sz / 2)));

    ImColor check_colorUpper{};
    ImColor check_colorLower{};

    if (*pVar) {
        check_colorUpper = { this->m_accent[0], this->m_accent[1], this->m_accent[2], this->style->Alpha };
        check_colorLower = { this->m_accent[0] - 15.f / 255, this->m_accent[1] - 15.f / 255, this->m_accent[2] - 15.f / 255, this->style->Alpha };
    }
    else {
        check_colorUpper = { ImGui::GetColorU32(this->style->Colors[ImGuiCol_FrameBg]) };
        check_colorLower = { ImGui::GetColorU32(this->style->Colors[ImGuiCol_FrameBg] - ImVec4(2.f / 255,2.f / 255,2.f / 255,0)) };
    }

    window->DrawList->AddRectFilledMultiColor(check_bb.Min, check_bb.Max, check_colorUpper, check_colorUpper, check_colorLower, check_colorLower);
    window->DrawList->AddRect(check_bb.Min - ImVec2(1, 1), check_bb.Max + ImVec2(1, 1), ImColor(0.f, 0.f, 0.f, this->style->Alpha));

    //window->DrawList->AddRect(total_bb.Min, total_bb.Max, ImColor(255, 0, 0));
    //window->DrawList->AddRect(check_bb.Min, ImVec2(total_bb.Max.x, check_bb.Max.y), ImColor(0, 0, 255));

    ImVec2 label_pos(pos + ImVec2(this->style->WindowPadding.x, -(square_sz / 6)));

    if (label_size.x > 0.0f)
        ImGui::RenderText(label_pos, szLabel);

    IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | (*v ? ImGuiItemStatusFlags_Checked : 0));
    return;
}

void CUserInterface::sliderscalar(const char* const& szLabel, const ImGuiDataType& dataType, void* pData, void* pMin, void* pMax, const char* szFormat, ImGuiSliderFlags flags) noexcept {
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return;

    ImGuiContext& g = *GImGui;
    const ImGuiID id = window->GetID(szLabel);

    const ImVec2 label_size = (szLabel[0] == '#' && szLabel[1] == '#' ? ImVec2(0, 0) : ImGui::CalcTextSize(szLabel, NULL, true));
    const ImVec2 label_size2 = ImGui::CalcTextSize(szLabel, NULL, true);
    const float slider_width = ImGui::CalcItemWidth();
    const float slider_height = label_size2.y / 2;
    const ImRect total_bb(window->DC.CursorPos + ImVec2(this->style->WindowPadding.x, 0), window->DC.CursorPos + ImVec2(slider_width, slider_height + label_size.y));
    const ImRect frame_bb(ImVec2(total_bb.Min.x, total_bb.Max.y - slider_height), total_bb.Max);

    //ImGui::GetForegroundDrawList()->AddRect(total_bb.Min, total_bb.Max, ImColor(255, 0, 0));
    //ImGui::GetForegroundDrawList()->AddRect(frame_bb.Min, frame_bb.Max, ImColor(0, 0, 255));

    const bool temp_input_allowed = (flags & ImGuiSliderFlags_NoInput) == 0;
    ImGui::ItemSize(total_bb, 0);
    if (!ImGui::ItemAdd(total_bb, id, &frame_bb, temp_input_allowed ? ImGuiItemFlags_Inputable : 0))
        return;

    // Default format string when passing NULL
    if (szFormat == NULL)
        szFormat = ImGui::DataTypeGetInfo(dataType)->PrintFmt;

    const bool hovered = ImGui::ItemHoverable(frame_bb, id, ImGuiItemFlags_None);
    bool temp_input_is_active = temp_input_allowed && ImGui::TempInputIsActive(id);
    if (!temp_input_is_active)
    {
        // Tabbing or CTRL-clicking on Slider turns it into an input box
        const bool clicked = hovered && ImGui::IsMouseClicked(0, ImGuiInputFlags_None, id);
        const bool make_active = (clicked || g.NavActivateId == id);
        if (make_active && clicked)
            ImGui::SetKeyOwner(ImGuiKey_MouseLeft, id);
        if (make_active && temp_input_allowed)
            if ((clicked && g.IO.KeyCtrl) || (g.NavActivateId == id && (g.NavActivateFlags & ImGuiActivateFlags_PreferInput)))
                temp_input_is_active = true;

        if (make_active && !temp_input_is_active)
        {
            ImGui::SetActiveID(id, window);
            ImGui::SetFocusID(id, window);
            ImGui::FocusWindow(window);
            g.ActiveIdUsingNavDirMask |= (1 << ImGuiDir_Left) | (1 << ImGuiDir_Right);
        }
    }

    if (temp_input_is_active)
    {
        // Only clamp CTRL+Click input when ImGuiSliderFlags_AlwaysClamp is set
        const bool is_clamp_input = (flags & ImGuiSliderFlags_AlwaysClamp) != 0;
        ImGui::TempInputScalar(frame_bb, id, szLabel, dataType, pData, szFormat, is_clamp_input ? pMin : NULL, is_clamp_input ? pMax : NULL);
        return;
    }

    // Slider behavior
    ImRect grab_bb;
    const bool value_changed = ImGui::SliderBehavior(frame_bb, id, dataType, pData, pMin, pMax, szFormat, flags, &grab_bb);
    if (value_changed)
        ImGui::MarkItemEdited(id);

    ImColor slider_colUpper = { this->m_accent[0], this->m_accent[1], this->m_accent[2], this->style->Alpha };
    ImColor slider_colLower = { this->m_accent[0] - 15.f / 255, this->m_accent[1] - 15.f / 255, this->m_accent[2] - 15.f / 255, this->style->Alpha };

    window->DrawList->AddRect(frame_bb.Min - ImVec2(1, 1), frame_bb.Max + ImVec2(1, 1), ImColor(0.f, 0.f, 0.f, this->style->Alpha));
    //window->DrawList->AddRectFilledMultiColor(frame_bb.Min, frame_bb.Max, ImColor(15.f / 255, 15.f / 255, 15.f / 255, style->Alpha), ImColor(15.f / 255, 15.f / 255, 15.f / 255, style->Alpha), ImColor(12.f / 255, 12.f / 255, 12.f / 255, style->Alpha), ImColor(12.f / 255, 12.f / 255, 12.f / 255, style->Alpha));
    window->DrawList->AddRectFilledMultiColor(frame_bb.Min, frame_bb.Max, ImGui::GetColorU32(this->style->Colors[ImGuiCol_FrameBg]), ImGui::GetColorU32(this->style->Colors[ImGuiCol_FrameBg]), ImGui::GetColorU32(this->style->Colors[ImGuiCol_FrameBg] - ImVec4(2.f / 255, 2.f / 255, 2.f / 255, 0)), ImGui::GetColorU32(this->style->Colors[ImGuiCol_FrameBg] - ImVec4(2.f / 255, 2.f / 255, 2.f / 255, 0)));

    window->DrawList->AddRectFilledMultiColor(frame_bb.Min, ImVec2(grab_bb.Max.x + 2.f, frame_bb.Max.y), slider_colUpper, slider_colUpper, slider_colLower, slider_colLower);

    // Display value using user-provided display format so user can add prefix/suffix/decorations to the value.
    ImGui::PushFont(::g.renderer.imgui->m_fonts.ui.verdana_bold_slider);

    char value_buf[64];
    const char* value_buf_end = value_buf + ImGui::DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), dataType, pData, szFormat);
    if (g.LogEnabled)
        ImGui::LogSetNextTextDecoration("{", "}");

    ::g.renderer.imgui->text(window->DrawList, ImVec2(frame_bb.Max.x - ImGui::CalcTextSize(value_buf).x, frame_bb.Min.y - (ImGui::CalcTextSize(value_buf).y + 3)), ImColor(1.f, 1.f, 1.f, this->style->Alpha), value_buf);

    ImGui::PopFont();

    if (label_size.x > 0.0f)
        ImGui::RenderText(ImVec2(frame_bb.Min.x, total_bb.Min.y - 3), szLabel);

    IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags | (temp_input_allowed ? ImGuiItemStatusFlags_Inputable : 0));
    return;
}

void CUserInterface::sliderint(const char* const& szLabel, int32_t* const& pVar, const int32_t& iMin, const int32_t& iMax, const char* szFormat) noexcept {
    this->sliderscalar(szLabel, ImGuiDataType_S32, pVar, (void*)&iMin, (void*)&iMax, szFormat, ImGuiSliderFlags_None);
}

void CUserInterface::slideruint8(const char* const& szLabel, uint8_t* const& pVar, const uint8_t& uMin, const uint8_t& uMax, const char* szFormat) noexcept {
    this->sliderscalar(szLabel, ImGuiDataType_U8, pVar, (void*)&uMin, (void*)&uMax, szFormat, ImGuiSliderFlags_None);
}

void CUserInterface::sliderint16(const char* const& szLabel, int16_t* const& pVar, const int16_t& iMin, const int16_t& iMax, const char* szFormat) noexcept {
    this->sliderscalar(szLabel, ImGuiDataType_S16, pVar, (void*)&iMin, (void*)&iMax, szFormat, ImGuiSliderFlags_None);
}

void CUserInterface::slideruint16(const char* const& szLabel, uint16_t* const& pVar, const uint16_t& uMin, const uint16_t& uMax, const char* szFormat) noexcept {
    this->sliderscalar(szLabel, ImGuiDataType_U16, pVar, (void*)&uMin, (void*)&uMax, szFormat, ImGuiSliderFlags_None);
}

void CUserInterface::sliderfloat(const char* const& szLabel, float* const& pVar, const float& fMin, const float& fMax, const char* szFormat) noexcept {
    this->sliderscalar(szLabel, ImGuiDataType_Float, pVar, (void*)&fMin, (void*)&fMax, szFormat, ImGuiSliderFlags_None);
}

bool CUserInterface::button(const char* const& szLabel, const ImVec2& vecSize, ImGuiButtonFlags flags) noexcept {
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(szLabel);
    ImGui::PushFont(::g.renderer.imgui->m_fonts.ui.verdana_bold_button);
    const ImVec2 label_size = ImGui::CalcTextSize(szLabel, NULL, true);

    ImVec2 pos = window->DC.CursorPos;
    if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
        pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
    ImVec2 size = ImGui::CalcItemSize(vecSize, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

    const ImRect bb(pos + ImVec2(style.WindowPadding.x, 0), pos + ImVec2(style.WindowPadding.x, 0) + size);
    ImGui::ItemSize(size, style.FramePadding.y);
    if (!ImGui::ItemAdd(bb, id))
        return false;

    bool bHovered{}, bHeld{};
    bool bPressed = ImGui::ButtonBehavior(bb, id, &bHovered, &bHeld, flags);

    // Render
    ImColor col = (bHeld && bHovered) ? style.Colors[ImGuiCol_ButtonActive] : bHovered ? style.Colors[ImGuiCol_ButtonHovered] - ImVec4(0.f, 0.f, 0.f, 1.f - style.Alpha) : style.Colors[ImGuiCol_Button] - ImVec4(0.f, 0.f, 0.f, 1.f - style.Alpha);
    ImColor col2 = (bHeld && bHovered) ? ((ImVec4)style.Colors[ImGuiCol_ButtonActive] - ImVec4(2.f / 255, 2.f / 255, 2.f / 255, 1.f - style.Alpha)) : bHovered ? ((ImVec4)style.Colors[ImGuiCol_ButtonHovered] - ImVec4(2.f / 255, 2.f / 255, 2.f / 255, 1.f - style.Alpha)) : ((ImVec4)style.Colors[ImGuiCol_Button] - ImVec4(2.f / 255, 2.f / 255, 2.f / 255, 1.f - style.Alpha));
    ImGui::RenderNavHighlight(bb, id);
    window->DrawList->AddRectFilledMultiColor(bb.Min, bb.Max, col, col, col2, col2);
    window->DrawList->AddRect(bb.Min - ImVec2(1, 1), bb.Max + ImVec2(1, 1), ImGui::GetColorU32(style.Colors[ImGuiCol_Border]));

    if (g.LogEnabled)
        ImGui::LogSetNextTextDecoration("[", "]");

    ImGui::RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding, szLabel, NULL, &label_size, style.ButtonTextAlign, &bb);
    ImGui::PopFont();

    // Automatically close popups
    //if (pressed && !(flags & ImGuiButtonFlags_DontClosePopups) && (window->Flags & ImGuiWindowFlags_Popup))
    //    CloseCurrentPopup();

    IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags);
    return bPressed;
}

bool CUserInterface::page(const char* const& szLabel, const bool& bSelected, ImVec4& srcCol, const ImVec4& dstCol, bool bLine, bool bVerdanaBold, ImVec2 vecSize, ImGuiSelectableFlags flags) noexcept {
    bool ret{};
    srcCol = ImLerp(srcCol, bSelected ? dstCol : ImVec4(1.f, 1.f, 1.f, 0.25f), ImGui::GetIO().DeltaTime * 10);
    if (bSelected) {
        if (bLine) {
            const float fLineWidth = 3.f;
            const ImVec2 vecPos1 = ImGui::GetWindowPos() + ImGui::GetCursorPos() + ImVec2(ImGui::GetContentRegionAvail().x - fLineWidth, 0);
            const ImVec2 vecPos2 = ImGui::GetWindowPos() + ImGui::GetCursorPos() + ImVec2(ImGui::GetContentRegionAvail().x, ImGui::CalcTextSize(szLabel).y);
            ImGui::GetWindowDrawList()->AddRectFilled(vecPos1, vecPos2, (ImColor)srcCol, 100.f);
            ::g.renderer.imgui->glow(ImGui::GetWindowDrawList(), vecPos1, vecPos2, ImColor(srcCol.x, srcCol.y, srcCol.z, 0.25f), fLineWidth * 2);
        }
        if(bVerdanaBold)
            ImGui::PushFont(::g.renderer.imgui->m_fonts.ui.verdana_bold);
    }
    ImGui::PushStyleColor(ImGuiCol_Text, srcCol);
    ret = ImGui::Selectable(szLabel, bSelected, flags, vecSize);
    ImGui::PopStyleColor();
    if (bSelected && bVerdanaBold) {
        ImGui::PopFont();
    }
    return ret;
}

bool CUserInterface::page(ui::page_t* const page, const bool& bSelected, const ImVec4& dstCol, bool bLine, bool bVerdanaBold, ImVec2 vecSize, ImGuiSelectableFlags flags) noexcept {
    return this->page(page->m_szLabel, bSelected, page->m_color, dstCol, bLine, bVerdanaBold, vecSize, flags);
}

bool CUserInterface::beginCombo(const char* const& szLabel, const char* const& szPreviewValue, ImGuiComboFlags flags) noexcept {
    ImGuiContext& g = *GImGui;
    ImGuiWindow* window = ImGui::GetCurrentWindow();

    ImGuiNextWindowDataFlags backup_next_window_data_flags = g.NextWindowData.Flags;
    g.NextWindowData.ClearFlags(); // We behave like Begin() and need to consume those values
    if (window->SkipItems)
        return false;

    const ImGuiID id = window->GetID(szLabel);
    IM_ASSERT((flags & (ImGuiComboFlags_NoArrowButton | ImGuiComboFlags_NoPreview)) != (ImGuiComboFlags_NoArrowButton | ImGuiComboFlags_NoPreview)); // Can't use both flags together
    if (flags & ImGuiComboFlags_WidthFitPreview)
        IM_ASSERT((flags & (ImGuiComboFlags_NoPreview | (ImGuiComboFlags)ImGuiComboFlags_CustomPreview)) == 0);

    const float arrow_size = (flags & ImGuiComboFlags_NoArrowButton) ? 0.0f : ImGui::GetFrameHeight() / 2;
    const ImVec2 label_size = (szLabel[0] == '#' && szLabel[1] == '#' ? ImVec2(0, 0) : ImGui::CalcTextSize(szLabel, NULL, true));
    const ImVec2 label_size2 = ImGui::CalcTextSize(szLabel, NULL, true);
    const ImVec2 preview_size = ImGui::CalcTextSize(szPreviewValue);
    const float preview_width = ((flags & ImGuiComboFlags_WidthFitPreview) && (szPreviewValue != NULL)) ? ImGui::CalcTextSize(szPreviewValue, NULL, true).x : 0.0f;
    const float w = ImGui::CalcItemWidth();
    const float h = label_size2.y * 1.35f;
    const ImRect bb(window->DC.CursorPos + ImVec2(this->style->WindowPadding.x, 0), window->DC.CursorPos + ImVec2(w, h));
    const ImRect frame_bb(bb.Min + ImVec2(0, label_size.y > 0 ? label_size.y + label_size2.y / 4 : 0), ImVec2(bb.Max.x, bb.Max.y + label_size.y + label_size.y / 4));
    const ImRect total_bb(bb.Min, bb.Max + ImVec2(0, label_size.y + label_size.y / 4));
    ImGui::ItemSize(total_bb, 0);
    if (!ImGui::ItemAdd(total_bb, id, &bb))
        return false;

    // Open on click
    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(frame_bb, id, &hovered, &held);
    const ImGuiID popup_id = ImHashStr("##ComboPopup", 0, id);
    bool popup_open = ImGui::IsPopupOpen(popup_id, ImGuiPopupFlags_None);
    if (pressed && !popup_open)
    {
        ImGui::OpenPopupEx(popup_id, ImGuiPopupFlags_None);
        popup_open = true;
    }

    // Render shape
    const float value_x2 = ImMax(bb.Min.x, bb.Max.x - arrow_size);
    ImGui::RenderNavHighlight(bb, id);
    if (!(flags & ImGuiComboFlags_NoPreview)) {
        window->DrawList->AddRect(frame_bb.Min - ImVec2(1, 1), frame_bb.Max + ImVec2(1, 1), ImColor(0.f, 0.f, 0.f, this->style->Alpha));
        window->DrawList->AddRectFilledMultiColor(frame_bb.Min, frame_bb.Max, ImGui::GetColorU32(this->style->Colors[ImGuiCol_FrameBg]), ImGui::GetColorU32(this->style->Colors[ImGuiCol_FrameBg]), ImGui::GetColorU32(this->style->Colors[ImGuiCol_FrameBg] - ImVec4(2.f / 255, 2.f / 255, 2.f / 255, 0)), ImGui::GetColorU32(this->style->Colors[ImGuiCol_FrameBg] - ImVec4(2.f / 255, 2.f / 255, 2.f / 255, 0)));
    }

    // Custom preview
    if (flags & ImGuiComboFlags_CustomPreview)
    {
        g.ComboPreviewData.PreviewRect = ImRect(bb.Min.x, bb.Min.y, value_x2, bb.Max.y);
        IM_ASSERT(szPreviewValue == NULL || szPreviewValue[0] == 0);
        //szPreviewValue = NULL;
    }

    // Render preview and label
    if (szPreviewValue != NULL && !(flags & ImGuiComboFlags_NoPreview))
    {
        //ImGui::PushFont(g_verdanaBold_combo);
        //ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(g_menu.m_accent[0], g_menu.m_accent[1], g_menu.m_accent[2], style->Alpha));
        if (g.LogEnabled)
            ImGui::LogSetNextTextDecoration("{", "}");
        ImGui::RenderTextClipped(frame_bb.Min + ImVec2(4, 4), ImVec2(frame_bb.Max.x - (arrow_size * 2), frame_bb.Max.y), szPreviewValue, (const char*)0, &preview_size);
        //window->DrawList->AddRectFilledMultiColor(frame_bb.Min, frame_bb.Max, ImColor(0, 0, 0, 0), ImColor(0.f, 0.f, 0.f, 80.f/255 - (1.f - style->Alpha)), ImColor(0.f, 0.f, 0.f, 80.f / 255 - (1.f - style->Alpha)), ImColor(0, 0, 0, 0));
        //ImGui::PopStyleColor();
        //ImGui::PopFont();
    }

    if (label_size.x > 0)
        ImGui::RenderText(bb.Min, szLabel);

    if (!(flags & ImGuiComboFlags_NoArrowButton))
    {
        const ImVec2 p1(frame_bb.Max.x - (arrow_size + label_size2.y / 3), frame_bb.Min.y + label_size2.y / 2);
        const ImVec2 p2(frame_bb.Max.x - label_size2.y / 3, frame_bb.Min.y + label_size2.y / 2);
        const ImVec2 p3(frame_bb.Max.x - arrow_size, frame_bb.Max.y - label_size2.y / 2);

        window->DrawList->AddTriangleFilled(p1, p2, p3, ImColor(1.f, 1.f, 1.f, this->style->Alpha));
    }

    if (!popup_open)
        return false;

    g.NextWindowData.Flags = backup_next_window_data_flags;
    return ImGui::BeginComboPopup(popup_id, frame_bb, flags);
}

void CUserInterface::endCombo() noexcept {
    ImGui::EndCombo();
}

void CUserInterface::multiCombo(const char* const& szLabel, ui::page_t* const& aPages, const uint16_t& nSize) noexcept {
    std::string sPreview = oxorany("off");

    for (uint16_t i = 0; i < nSize; ++i) {
        if ((*aPages[i].m_pVar)) {
            if (sPreview != oxorany("off")) {
                sPreview.append(",");
                sPreview.append(aPages[i].m_szLabel);
            }
            else {
                sPreview = aPages[i].m_szLabel;
            }
        }
    }

    if (this->beginCombo(szLabel, sPreview.c_str())) {
        for (uint8_t i = 0; i < nSize; ++i) {
            if (this->page(&aPages[i], (*aPages[i].m_pVar), float3toimvec4(this->m_accent), false, true, ImVec2{}, ImGuiSelectableFlags_DontClosePopups)) {
                (*aPages[i].m_pVar) = !(*aPages[i].m_pVar);
            }
        }
        this->endCombo();
    }
}

void CUserInterface::colorpick4(const char* const& szLabel, float* const& faCol, bool sameLine, ImGuiColorEditFlags flags) noexcept {
    if(sameLine)
        ImGui::SameLine();
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return;

    ImGuiContext& g = *GImGui;
    const ImGuiID id = window->GetID(szLabel);
    const float default_size = ImGui::GetFrameHeight() / 2;
    const ImVec2 size(default_size * 2, default_size);
    const ImVec2& cursor_pos = window->DC.CursorPos;
    const ImRect bb(cursor_pos + ImVec2(ImGui::GetContentRegionAvail().x - this->style->WindowPadding.x, size.y/4), cursor_pos + ImVec2(ImGui::GetContentRegionAvail().x, size.y*1.25f));
    ImGui::ItemSize(bb, 0);
    if (!ImGui::ItemAdd(bb, id))
        return;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held);

    const bool bColorPick3 = flags & ImGuiColorEditFlags_NoAlpha;

    if (bColorPick3)
        flags &= ~(ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_AlphaPreviewHalf);
    else
        flags |= ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_AlphaPreview;

    ImVec4 col_rgb = (bColorPick3 ? float3toimvec4(faCol) : float4toimvec4(faCol));
    if (flags & ImGuiColorEditFlags_InputHSV)
        ImGui::ColorConvertHSVtoRGB(col_rgb.x, col_rgb.y, col_rgb.z, col_rgb.x, col_rgb.y, col_rgb.z);

    ImVec4 col_rgb_without_alpha(col_rgb.x, col_rgb.y, col_rgb.z, 1.0f);
    float grid_step = ImMin(size.x, size.y) / 2.99f;
    float rounding = ImMin(g.Style.FrameRounding, grid_step * 0.5f);
    ImRect bb_inner(bb);
    float off = 0.0f;
    if ((flags & ImGuiColorEditFlags_NoBorder) == 0)
    {
        off = -0.75f; // The border (using Col_FrameBg) tends to look off when color is near-opaque and rounding is enabled. This offset seemed like a good middle ground to reduce those artifacts.
        bb_inner.Expand(off);
    }
    if ((flags & ImGuiColorEditFlags_AlphaPreviewHalf) && col_rgb.w < 1.0f)
    {
        float mid_x = IM_ROUND((bb_inner.Min.x + bb_inner.Max.x) * 0.5f);
        ImGui::RenderColorRectWithAlphaCheckerboard(window->DrawList, ImVec2(bb_inner.Min.x + grid_step, bb_inner.Min.y), bb_inner.Max, ImGui::GetColorU32(col_rgb), grid_step, ImVec2(-grid_step + off, off), rounding, ImDrawFlags_RoundCornersRight);
        window->DrawList->AddRectFilled(bb_inner.Min, ImVec2(mid_x, bb_inner.Max.y), ImGui::GetColorU32(col_rgb_without_alpha), rounding, ImDrawFlags_RoundCornersLeft);
    }
    else
    {
        // Because GetColorU32() multiplies by the global style Alpha and we don't want to display a checkerboard if the source code had no alpha
        ImVec4 col_source = (flags & ImGuiColorEditFlags_AlphaPreview) ? col_rgb : col_rgb_without_alpha;
        if (col_source.w < 1.0f)
            ImGui::RenderColorRectWithAlphaCheckerboard(window->DrawList, bb_inner.Min, bb_inner.Max, ImGui::GetColorU32(col_source), grid_step, ImVec2(off, off), rounding);
        else
            window->DrawList->AddRectFilled(bb_inner.Min, bb_inner.Max, ImGui::GetColorU32(col_source), rounding);
    }
    ImGui::RenderNavHighlight(bb, id);
    if ((flags & ImGuiColorEditFlags_NoBorder) == 0)
    {
        window->DrawList->AddRect(bb.Min, bb.Max, ImColor(0.f, 0.f, 0.f, this->style->Alpha)); // Color button are often in need of some sort of border
    }

    // Drag and Drop Source
    // NB: The ActiveId test is merely an optional micro-optimization, BeginDragDropSource() does the same test.
    if (g.ActiveId == id && !(flags & ImGuiColorEditFlags_NoDragDrop) && ImGui::BeginDragDropSource())
    {
        if (flags & ImGuiColorEditFlags_NoAlpha)
            ImGui::SetDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_3F, &col_rgb, sizeof(float) * 3, ImGuiCond_Once);
        else
            ImGui::SetDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_4F, &col_rgb, sizeof(float) * 4, ImGuiCond_Once);
        ImGui::ColorButton(szLabel, (bColorPick3 ? float3toimvec4(faCol) : float4toimvec4(faCol)), flags);
        ImGui::SameLine();
        ImGui::TextEx("Color");
        ImGui::EndDragDropSource();
    }

    const ImVec2 vecLabel = ImGui::CalcTextSize(szLabel);

    if (szLabel[0] != '#' && szLabel[1] != '#')
        ImGui::RenderText(cursor_pos + ImVec2(this->style->WindowPadding.x, -vecLabel.y), szLabel);

    if (pressed) 
        ImGui::OpenPopup(szLabel);

    if (ImGui::BeginPopup(szLabel, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize)) {
        ImGui::ColorPicker4(szLabel, faCol, flags | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoSidePreview);
        ImGui::EndPopup();
    }
}

void CUserInterface::colorpick3(const char* const& szLabel, float* const& faCol, bool sameLine, ImGuiColorEditFlags flags) noexcept {
    flags |= ImGuiColorEditFlags_NoAlpha;
    this->colorpick4(szLabel, faCol, sameLine, flags);
}

void CUserInterface::inputText(const char* const& szLabel, char* pBuffer, const uint32_t& nBuffer, ImGuiInputTextFlags flags) noexcept {
    const float& fPadding = this->style->WindowPadding.x;
    ImGui::Indent(fPadding);
    const ImVec2 vecPos1 = ImGui::GetWindowPos() + ImGui::GetCursorPos();
    const ImVec2 vecPos2 = vecPos1 + ImVec2(ImGui::CalcItemWidth(), ImGui::CalcTextSize(szLabel).y + this->style->FramePadding.y * 2);
    ImGui::InputText(szLabel, pBuffer, nBuffer, flags);
    ImGui::GetWindowDrawList()->AddRect(vecPos1 - ImVec2(1,1), vecPos2 + ImVec2(1, 1), ImColor(0.f, 0.f, 0.f, this->style->Alpha));
    ImGui::Indent(-fPadding);
}

void CUserInterface::horPad() noexcept {
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, this->style->WindowPadding);
	ImGui::SameLine();
	ImGui::PopStyleVar();
}

void CUserInterface::verPad() noexcept {
    ImGui::Dummy(ImVec2(0, this->style->WindowPadding.y/2));
}

void CUserInterface::render() noexcept {
    static bool inited{};
    if(!inited) {
        g.sn0w.ui->init();
        inited = true;
    }
    g.sn0w.ui->main();
    g.sn0w.ui->line();
}

void CUserInterface::update() noexcept {
    this->m_accent[3] = this->style->Alpha;

    this->style->WindowPadding = ImVec2(30 * this->m_dpiScale, 30 * this->m_dpiScale);
    this->style->ItemSpacing   = ImVec2(10 * this->m_dpiScale, 5 * this->m_dpiScale);
    this->style->ScrollbarSize = 25.f * this->m_dpiScale;

    this->m_bounds.Min = { 1200 * this->m_dpiScale, 700 * this->m_dpiScale };
    this->m_bounds.Max = { 1500 * this->m_dpiScale, 850 * this->m_dpiScale };
    g.renderer.imgui->m_fonts.ui.verdana->Scale             = 0.55f * this->m_dpiScale;
    g.renderer.imgui->m_fonts.ui.verdana_pages->Scale       = 0.60f * this->m_dpiScale;
    g.renderer.imgui->m_fonts.ui.verdana_bold->Scale        = 0.55f * this->m_dpiScale;
    g.renderer.imgui->m_fonts.ui.verdana_bold_child->Scale  = 0.50f * this->m_dpiScale;
    g.renderer.imgui->m_fonts.ui.verdana_bold_slider->Scale = 0.40f * this->m_dpiScale;
    g.renderer.imgui->m_fonts.ui.verdana_bold_button->Scale = 0.45f * this->m_dpiScale;
    g.renderer.imgui->m_fonts.ui.undefeated->Scale          = 0.75f * this->m_dpiScale;
    g.renderer.imgui->m_fonts.ui.undefeated_pages->Scale    = 0.75f * this->m_dpiScale;
}

void CUserInterface::main() noexcept {
    this->update();

    if(!this->m_bOpen)
        return;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    this->beginWindow(oxorany("##main"), this->m_bounds, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    {
        ImGui::PopStyleVar();
        this->m_currentSize = ImGui::GetWindowSize();
        
        ImDrawList* const pDrawlist = ImGui::GetWindowDrawList();
        const ImVec2 vecPos = ImGui::GetWindowPos();
        const ImVec2 vecSize = ImGui::GetWindowSize();

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0,2});
        this->beginChild(oxorany("##info"), ImVec2(0, 40.f * this->m_dpiScale), false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
        {
            ImGui::PushFont(g.renderer.imgui->m_fonts.ui.verdana_bold_child);

            ImGui::Indent(vecSize.x / 2 - ImGui::CalcTextSize(oxorany("sn0w")).x/2);
            ImGui::Dummy(ImVec2(0, ImGui::CalcTextSize(oxorany("sn0w")).y / 3));

            //g.renderer.imgui->glow(pDrawlist, vecPos + ImVec2(-15 * this->m_dpiScale, 7), vecPos + ImVec2(vecSize.x + (15 * this->m_dpiScale), 7), ImColor(this->m_accent[0], this->m_accent[1], this->m_accent[2], 0.15f - (1.f - this->style->Alpha)), 35.f * this->m_dpiScale, true);

            ImGui::TextColored(float4toimvec4(this->m_accent), "%s", oxorany("sn0w"));

            ImGui::PopFont();
        }
        this->endChild();
        ImGui::PopStyleVar();

        pDrawlist->AddLine(vecPos + ImVec2(7, 40.f * this->m_dpiScale), vecPos + ImVec2(vecSize.x, 40.f * this->m_dpiScale), ImColor(0.f, 0.f, 0.f, this->style->Alpha), 1.f);

        static uint8_t nCurPage{};

        this->beginChild(oxorany("##pages"), ImVec2(180 * this->m_dpiScale, 0), false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
        {
            ImGui::Indent(this->style->WindowPadding.x);
            ImGui::Dummy(ImVec2(0, this->style->WindowPadding.y/4));

            ImGui::PushFont(g.renderer.imgui->m_fonts.ui.verdana_pages);

            for (uint8_t i = 0; i < IM_ARRAYSIZE(this->m_pages); ++i) {
                if (this->page(this->m_pages[i].m_szLabel, nCurPage == i, this->m_pages[i].m_color, float4toimvec4(this->m_accent))) {
                    nCurPage = i;
                }
            }

            ImGui::PopFont();

        }
        this->endChild();

        pDrawlist->AddLine(vecPos + ImVec2(this->style->WindowPadding.x + ((150 + 1.f) * this->m_dpiScale), 40.f * this->m_dpiScale), vecPos + ImVec2(this->style->WindowPadding.x + ((150 + 1.f) * this->m_dpiScale), vecSize.y - 7), ImColor(17.f / 255, 17.f / 255, 17.f / 255, this->style->Alpha), 1.f);
        pDrawlist->AddLine(vecPos + ImVec2(this->style->WindowPadding.x + (150 * this->m_dpiScale), 40.f * this->m_dpiScale), vecPos + ImVec2(this->style->WindowPadding.x + (150 * this->m_dpiScale), vecSize.y - 7), ImColor(0.f, 0.f, 0.f, this->style->Alpha), 1.f);

        ImGui::SameLine((150 * this->m_dpiScale) + this->style->WindowPadding.x);

        this->beginChild(oxorany("##main_child"), ImGui::GetContentRegionAvail() - this->style->WindowPadding, false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground);
        {
            ImGui::Indent(this->style->WindowPadding.x);
            ImGui::Dummy(ImVec2(0, this->style->WindowPadding.y/1.25f));
            
            switch (nCurPage) {
                case 0: {
                    this->ragebot();
                    break;
                }
                case 1: {
                    this->exploits();
                    break;
                }
                case 2: {
                    this->legitbot();
                    break;
                }
                case 3: {
                    this->visuals();
                    break;
                }
                case 4: {
                    this->misc();
                    break;
                }
                case 5: {
                    this->changer();
                    break;
                }
                case 6: {
                    this->config();
                    break;
                }
                default: {
                    //this->debug();
                    break;
                }
            }

        }
        this->endChild();
        this->border(pDrawlist);
        g.renderer.imgui->glow(ImGui::GetBackgroundDrawList(), vecPos, vecPos + vecSize, ImColor(0.f, 0.f, 0.f, 60.f / 255 - (1.f - this->style->Alpha)), 10.f);
    }
    this->endWindow();
}

void CUserInterface::line() noexcept {
    static bool isClosing{};
    const float widthRatio = (float)g.window.m_iWidth / (float)g.screen.m_iWidth;
    const ImVec2 lineSize = {500 * widthRatio, 10};
    const ImRect rect = {
        ImVec2{(g.window.m_iWidth / 2) - (lineSize.x / 2), g.window.m_iHeight - (lineSize.y + 10)},
        ImVec2{(g.window.m_iWidth / 2) + (lineSize.x / 2), (float)g.window.m_iHeight - 10},
    };

	ImGui::SetNextWindowPos(rect.Min - ImVec2{30 * widthRatio, 50 * widthRatio});
	ImGui::SetNextWindowSize(lineSize + ImVec2{60 * widthRatio, 100 * widthRatio});
	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1.f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{});
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{});
	ImGui::Begin(oxorany("##bottom_bar"), NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);
	{
		if (ImGui::InvisibleButton(".", ImGui::GetWindowSize())) isClosing = !isClosing;
	}
	ImGui::End();
	ImGui::PopStyleVar(3);

    g.renderer.imgui->boxFilled(ImGui::GetForegroundDrawList(), rect.Min, rect.Max, ImColor(1.f,1.f,1.f,0.25f), 20.f);

    const float dstAlpha = (isClosing ? 0.1f : 1.f);
    this->style->Alpha = ImLerp(this->style->Alpha, dstAlpha, ImGui::GetIO().DeltaTime * 12);
    this->style->Alpha = ImClamp<float>(this->style->Alpha, 0.1f, 1.f);
    this->m_bOpen = this->style->Alpha > 0.2f;
}

void CUserInterface::ragebot() noexcept {
    static ui::page_t hitboxes[] {
        ui::page_t(&g.config.rage.aimbot.hitbox[0], oxorany("head")),
        ui::page_t(&g.config.rage.aimbot.hitbox[1], oxorany("chest")),
        ui::page_t(&g.config.rage.aimbot.hitbox[2], oxorany("arms")),
        ui::page_t(&g.config.rage.aimbot.hitbox[3], oxorany("hip")),
        ui::page_t(&g.config.rage.aimbot.hitbox[4], oxorany("legs"))
    };
    static ui::page_t exploits[] {
        ui::page_t(&g.config.rage.aimbot.exploits[0], oxorany("double tap")),
        ui::page_t(&g.config.rage.aimbot.exploits[1], oxorany("hide shots [-]")),
        ui::page_t(&g.config.rage.aimbot.exploits[2], oxorany("force psilent"))
    };
    static ui::page_t yaws[] {
        ui::page_t(NULL, oxorany("local view")),
        ui::page_t(NULL, oxorany("right")),
        ui::page_t(NULL, oxorany("left")),
        ui::page_t(NULL, oxorany("backwards")),
    };
    static ui::page_t pitches[] {
        ui::page_t(NULL, oxorany("local view")),
        ui::page_t(NULL, oxorany("zero")),
        ui::page_t(NULL, oxorany("up")),
        ui::page_t(NULL, oxorany("down")),
    };
    static ui::page_t modes[] {
        ui::page_t(NULL, oxorany("static")),
        ui::page_t(NULL, oxorany("jitter")),
        ui::page_t(NULL, oxorany("spin")),
        ui::page_t(NULL, oxorany("random flick")),
    };

    //бляяяя
    static char yaw[12]{};
    static char pitch[12]{};
    switch(g.config.rage.antiaim.yaw) {
        case 0: {
            memcpy(yaw, yaws[0].m_szLabel, 12);
            break;
        }
        case -90: {
            memcpy(yaw, yaws[1].m_szLabel, 12);
            break;
        }
        case 90: {
            memcpy(yaw, yaws[2].m_szLabel, 12);
            break;
        }
        case 180: {
            memcpy(yaw, yaws[3].m_szLabel, 12);
            break;
        }
        default: {
            memcpy(yaw, oxorany("unknown"), 12);
            break;
        }
    };
    switch(g.config.rage.antiaim.pitch) {
        case -1: {
            memcpy(pitch, pitches[0].m_szLabel, 12);
            break;
        }
        case 0: {
            memcpy(pitch, pitches[1].m_szLabel, 12);
            break;
        }
        case -70: {
            memcpy(pitch, pitches[2].m_szLabel, 12);
            break;
        }
        case 70: {
            memcpy(pitch, pitches[3].m_szLabel, 12);
            break;
        }
        default: {
            memcpy(pitch, oxorany("unknown"), 12);
            break;
        }
    }

    this->beginChild(oxorany("aimbot"), ImVec2(ImGui::GetContentRegionAvail().x/2 - this->style->WindowPadding.x/2, 0), true);
	{
		this->checkbox(oxorany("enabled##aimbot"), &g.config.rage.aimbot.enabled);
		this->sliderfloat(oxorany("maximum fov"), &g.config.rage.aimbot.max_fov, 5, 180, (const char*)u8"%.1f°%");
		this->multiCombo(oxorany("hitbox"), hitboxes, IM_ARRAYSIZE(hitboxes));
        this->multiCombo(oxorany("exploits"), exploits, IM_ARRAYSIZE(exploits));
        //this->slideruint8(oxorany("hitchance"), &g.config.rage.aimbot.hitchance, 1, 100, (const char*)u8"%u%%");
        //this->slideruint8(oxorany("minimum damage"), &g.config.rage.aimbot.min_damage, 1, 100);
        this->checkbox(oxorany("auto stop"), &g.config.rage.aimbot.autostop);
        this->sliderfloat(oxorany("speed mult"), &g.config.rage.aimbot.autostop_mult, 3, 15, "%.1f");
        this->sliderfloat(oxorany("peek factor"), &g.config.rage.aimbot.autostop_peek_factor, 1.f, 5.f, "%.1f");
        this->checkbox(oxorany("auto fire"), &g.config.rage.aimbot.autofire);
        //this->checkbox(oxorany("auto wall"), &g.config.rage.aimbot.autowall);
		this->checkbox(oxorany("auto scope"), &g.config.rage.aimbot.autoscope);
        this->checkbox(oxorany("body if lethal"), &g.config.rage.aimbot.baim);
	}
	this->endChild(); 

	this->horPad();

	this->beginChild(oxorany("anti-aim"), ImVec2(0, 0), true);
	{
		this->checkbox(oxorany("enabled##aimbot"), &g.config.rage.antiaim.enabled);
        if(this->beginCombo(oxorany("yaw"), yaw)) {
            if(this->page(&yaws[0], g.config.rage.antiaim.yaw == 0, float4toimvec4(this->m_accent), false)) {
                g.config.rage.antiaim.yaw = 0;
            }
            if(this->page(&yaws[1], g.config.rage.antiaim.yaw == -90, float4toimvec4(this->m_accent), false)) {
                g.config.rage.antiaim.yaw = -90;
            }
            if(this->page(&yaws[2], g.config.rage.antiaim.yaw == 90, float4toimvec4(this->m_accent), false)) {
                g.config.rage.antiaim.yaw = 90;
            }
            if(this->page(&yaws[3], g.config.rage.antiaim.yaw == 180, float4toimvec4(this->m_accent), false)) {
                g.config.rage.antiaim.yaw = 180;
            }
            this->endCombo();
        }
        if(this->beginCombo(oxorany("pitch"), pitch)) {
            if(this->page(&pitches[0], g.config.rage.antiaim.pitch == -1, float4toimvec4(this->m_accent), false)) {
                g.config.rage.antiaim.pitch = -1;
            }
            if(this->page(&pitches[1], g.config.rage.antiaim.pitch == 0, float4toimvec4(this->m_accent), false)) {
                g.config.rage.antiaim.pitch = 0;
            }
            if(this->page(&pitches[2], g.config.rage.antiaim.pitch == -70, float4toimvec4(this->m_accent), false)) {
                g.config.rage.antiaim.pitch = -70;
            }
            if(this->page(&pitches[3], g.config.rage.antiaim.pitch == 70, float4toimvec4(this->m_accent), false)) {
                g.config.rage.antiaim.pitch = 70;
            }
            this->endCombo();
        }
        if(this->beginCombo(oxorany("mode"), modes[g.config.rage.antiaim.mode].m_szLabel)) {
            if(this->page(&modes[0], g.config.rage.antiaim.mode == 0, float4toimvec4(this->m_accent), false)) {
                g.config.rage.antiaim.mode = 0;
            }
            if(this->page(&modes[1], g.config.rage.antiaim.mode == 1, float4toimvec4(this->m_accent), false)) {
                g.config.rage.antiaim.mode = 1;
            }
            if(this->page(&modes[2], g.config.rage.antiaim.mode == 2, float4toimvec4(this->m_accent), false)) {
                g.config.rage.antiaim.mode = 2;
            }
            if(this->page(&modes[3], g.config.rage.antiaim.mode == 3, float4toimvec4(this->m_accent), false)) {
                g.config.rage.antiaim.mode = 3;
            }
            this->endCombo();
        }

        switch(g.config.rage.antiaim.mode) {
            case 1: {
                this->slideruint8(oxorany("range"), &g.config.rage.antiaim.jitter_range, 1, 40, (const char*)u8"%u°%");
                break;
            }
            case 2: {
                this->slideruint8(oxorany("speed"), &g.config.rage.antiaim.spin_speed, 1, 45);
                break;
            }
            case 3: {
                this->slideruint16(oxorany("rate"), &g.config.rage.antiaim.flick_rate, 100, 1000, (const char*)u8"%ums%");
                break;
            }
            default: {
                break;
            }
        }

        //this->checkbox(oxorany("at targets"), &g.config.rage.antiaim.at_targets);
        this->checkbox(oxorany("defensive"), &g.config.rage.antiaim.defensive);
	}
	this->endChild();
}

void CUserInterface::exploits() noexcept {
    this->beginChild(oxorany("general"), ImVec2{}, true);
    {
        this->checkbox(oxorany("rapid fire"), &g.config.exploits.rapid_fire);
        this->checkbox(oxorany("infinity ammo"), &g.config.exploits.infinity_ammo);
        this->checkbox(oxorany("wallshot"), &g.config.exploits.wallshot);
        this->checkbox(oxorany("ignore freeze time"), &g.config.exploits.ignore_freeze_time);
        //this->checkbox(oxorany("air jump"), &g.config.exploits.air_jump);
        //this->checkbox(oxorany("noclip"), &g.config.exploits.noclip);
    }
    this->endChild();
}

void CUserInterface::legitbot() noexcept {
    static ui::page_t weapons[] {
        ui::page_t(NULL, oxorany("G")),
        ui::page_t(NULL, oxorany("W")),
        ui::page_t(NULL, oxorany("P")),
        ui::page_t(NULL, oxorany("d")),
        ui::page_t(NULL, oxorany("f")),
        ui::page_t(NULL, oxorany("a"))
    };
    static ui::page_t hitboxes[][3] {
        {
            ui::page_t(&g.config.legit.configs[0].m_bones[0].m_bEnabled, oxorany("head")),
            ui::page_t(&g.config.legit.configs[0].m_bones[1].m_bEnabled, oxorany("chest")),
            ui::page_t(&g.config.legit.configs[0].m_bones[2].m_bEnabled, oxorany("hip"))
        },
        {
            ui::page_t(&g.config.legit.configs[1].m_bones[0].m_bEnabled, oxorany("head")),
            ui::page_t(&g.config.legit.configs[1].m_bones[1].m_bEnabled, oxorany("chest")),
            ui::page_t(&g.config.legit.configs[1].m_bones[2].m_bEnabled, oxorany("hip"))
        },
        {
            ui::page_t(&g.config.legit.configs[2].m_bones[0].m_bEnabled, oxorany("head")),
            ui::page_t(&g.config.legit.configs[2].m_bones[1].m_bEnabled, oxorany("chest")),
            ui::page_t(&g.config.legit.configs[2].m_bones[2].m_bEnabled, oxorany("hip"))
        },
        {
            ui::page_t(&g.config.legit.configs[3].m_bones[0].m_bEnabled, oxorany("head")),
            ui::page_t(&g.config.legit.configs[3].m_bones[1].m_bEnabled, oxorany("chest")),
            ui::page_t(&g.config.legit.configs[3].m_bones[2].m_bEnabled, oxorany("hip"))
        },
        {
            ui::page_t(&g.config.legit.configs[4].m_bones[0].m_bEnabled, oxorany("head")),
            ui::page_t(&g.config.legit.configs[4].m_bones[1].m_bEnabled, oxorany("chest")),
            ui::page_t(&g.config.legit.configs[4].m_bones[2].m_bEnabled, oxorany("hip"))
        },
        {
            ui::page_t(&g.config.legit.configs[5].m_bones[0].m_bEnabled, oxorany("head")),
            ui::page_t(&g.config.legit.configs[5].m_bones[1].m_bEnabled, oxorany("chest")),
            ui::page_t(&g.config.legit.configs[5].m_bones[2].m_bEnabled, oxorany("hip"))
        }
    };
    static uint8_t nCurrent{};

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(this->style->WindowPadding.x/2, 5));
    this->beginChild(oxorany("weapon"), ImVec2{0.f, 70.f * this->m_dpiScale}, true);
    {
        ImGui::PushFont(g.renderer.imgui->m_fonts.ui.undefeated_pages);
        ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(.5f, .5f));
        for(uint8_t i=0;i<IM_ARRAYSIZE(weapons);++i) {
            if(this->page(&weapons[i], nCurrent == i, float4toimvec4(this->m_accent), false, false, ImVec2(ImGui::CalcTextSize(weapons[i].m_szLabel).x + 5, ImGui::GetContentRegionAvail().y))) {
                nCurrent = i;
            }
            ImGui::SameLine();
        }
        ImGui::PopStyleVar();
        ImGui::PopFont();
    }
    this->endChild();
    ImGui::PopStyleVar();

    this->verPad();

    this->beginChild(oxorany("configuration"), ImVec2{}, true);
    {
        if(!g.config.rage.aimbot.enabled && !g.config.rage.antiaim.enabled) {
            for(uint8_t i=0;i<IM_ARRAYSIZE(g.config.legit.configs);++i) {
                if(i == nCurrent) {
                    legitbot_config_t& cfg = g.config.legit.configs[i];
                    this->checkbox(oxorany("enabled##legit"), &cfg.m_bEnabled);
                    this->sliderfloat(oxorany("maximum fov"), &cfg.m_fMaxFOV, 5.f, 10.f, (const char*)u8"%.1f°%");
                    //this->checkbox(oxorany("dynamic fov"), &cfg.m_bDynamicFOV);
                    this->multiCombo(oxorany("hitboxes"), hitboxes[i], IM_ARRAYSIZE(hitboxes[i]));
                    this->sliderfloat(oxorany("yaw smoothness"), &cfg.m_fYaw, 1, 10.f, "%.1f");
                    this->sliderfloat(oxorany("pitch smoothness"), &cfg.m_fPitch, 1.f, 10.f, "%.1f");
                    this->sliderfloat(oxorany("yaw smoothness in fire"), &cfg.m_fYawFire, 1.f, 10.f, "%.1f");
                    this->sliderfloat(oxorany("pitch smoothness in fire"), &cfg.m_fPitchFire, 1.f, 10.f, "%.1f");
                    this->checkbox(oxorany("recoil control"), &cfg.m_bRCS);
                    //this->checkbox(oxorany("shoot delay"), &cfg.m_bShootDelay);
                }
            }
        } else {
            ImGui::Indent(this->style->WindowPadding.x);
            ImGui::Text("%s", oxorany("disable ragebot."));
            ImGui::Indent(-this->style->WindowPadding.x);
        }
    }
    this->endChild();
}

void CUserInterface::visuals() noexcept {
    static ui::page_t tabs[] {
        ui::page_t(NULL, oxorany("esp")),
        ui::page_t(NULL, oxorany("chams")),
        ui::page_t(NULL, oxorany("world"))
    };
    static ui::page_t box_types[] {
        ui::page_t(NULL, oxorany("rectangle")),
        ui::page_t(NULL, oxorany("corners"))
    };
    static ui::page_t health_types[] {
        ui::page_t(NULL, oxorany("solid")),
        ui::page_t(NULL, oxorany("health-based"))
    };
    static ui::page_t weapon_types[] {
        ui::page_t(&g.config.visuals.esp.weapons[0], oxorany("text")),
        ui::page_t(&g.config.visuals.esp.weapons[1], oxorany("icon"))
    };
    static ui::page_t flags[] {
        ui::page_t(&g.config.visuals.esp.flags_a[0], oxorany("armor")),
        ui::page_t(&g.config.visuals.esp.flags_a[1], oxorany("bomb/kits")),
        ui::page_t(&g.config.visuals.esp.flags_a[2], oxorany("scope")),
        ui::page_t(&g.config.visuals.esp.flags_a[3], oxorany("reload")),
        ui::page_t(&g.config.visuals.esp.flags_a[4], oxorany("plant/defuse"))
    };
    static ui::page_t mats[] {
        ui::page_t(NULL, oxorany("solid")),
        ui::page_t(NULL, oxorany("glow")),
        ui::page_t(NULL, oxorany("flat")),
        ui::page_t(NULL, oxorany("glass"))
    };

    static uint8_t nCurrent{};
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(this->style->WindowPadding.x, 5));
    this->beginChild(oxorany("##categories"), ImVec2{0.f, 70.f * this->m_dpiScale}, true);
    {
        ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(.5f, .5f));
        for(uint8_t i=0;i<IM_ARRAYSIZE(tabs);++i) {
            if(this->page(&tabs[i], nCurrent == i, float4toimvec4(this->m_accent), false, true, ImVec2(ImGui::CalcTextSize(tabs[i].m_szLabel).x + 10, ImGui::GetContentRegionAvail().y))) {
                nCurrent = i;
            }
            ImGui::SameLine();
        }
        ImGui::PopStyleVar();
    }
    this->endChild();
    ImGui::PopStyleVar();

    this->verPad();

    switch(nCurrent) {
        case 0: {
            this->beginChild(oxorany("player"), ImVec2{ImGui::GetContentRegionAvail().x / 2 - (this->style->WindowPadding.x / 2), 0.f}, true);
            {
                this->checkbox(oxorany("enabled##esp"), &g.config.visuals.esp.enabled);
                this->checkbox(oxorany("teammates"), &g.config.visuals.esp.teammates);
                this->checkbox(oxorany("box"), &g.config.visuals.esp.box);
                this->colorpick4(oxorany("##box_color"), g.config.visuals.esp.box_color);
                if(this->beginCombo(oxorany("##box_type"), box_types[g.config.visuals.esp.box_type].m_szLabel)) {
                    if(this->page(&box_types[0], g.config.visuals.esp.box_type == 0, float4toimvec4(this->m_accent), false))
                        g.config.visuals.esp.box_type = 0;
                    if(this->page(&box_types[1], g.config.visuals.esp.box_type == 1, float4toimvec4(this->m_accent), false))
                        g.config.visuals.esp.box_type = 1;
                    this->endCombo();
                }
                this->checkbox(oxorany("health"), &g.config.visuals.esp.health);
                this->colorpick4(oxorany("##health_solid_color"), g.config.visuals.esp.health_color);
                if(this->beginCombo(oxorany("##health_type"), health_types[g.config.visuals.esp.health_type].m_szLabel)) {
                    if(this->page(&health_types[0], g.config.visuals.esp.health_type == 0, float4toimvec4(this->m_accent), false))
                        g.config.visuals.esp.health_type = 0;
                    if(this->page(&health_types[1], g.config.visuals.esp.health_type == 1, float4toimvec4(this->m_accent), false))
                        g.config.visuals.esp.health_type = 1;
                    this->endCombo();
                }
                this->checkbox(oxorany("skeleton"), &g.config.visuals.esp.skeleton);
                this->colorpick4(oxorany("##skeleton_color"), g.config.visuals.esp.skeleton_color);
                //this->checkbox(oxorany("hit skeleton"), &g.config.visuals.esp.skeleton_hit);
                //this->colorpick4(oxorany("##hit_skeleton_color"), g.config.visuals.esp.skeleton_hit_color);
                this->checkbox(oxorany("nick"), &g.config.visuals.esp.nick);
                this->colorpick4(oxorany("##nick_color"), g.config.visuals.esp.nick_color);
                this->checkbox(oxorany("weapon"), &g.config.visuals.esp.weapon);
                this->colorpick4(oxorany("##weapon_color"), g.config.visuals.esp.weapon_color);
                this->multiCombo(oxorany("##weapon_types"), weapon_types, IM_ARRAYSIZE(weapon_types));
                this->checkbox(oxorany("ammo"), &g.config.visuals.esp.ammo);
                this->colorpick4(oxorany("##ammo_color"), g.config.visuals.esp.ammo_color);
                this->checkbox(oxorany("flags"), &g.config.visuals.esp.flags);
                this->colorpick4(oxorany("##flags_color"), g.config.visuals.esp.flags_color);
                this->multiCombo(oxorany("##flags_"), flags, IM_ARRAYSIZE(flags));
            }
            this->endChild();

            this->horPad();

            this->beginChild(oxorany("object"), ImVec2{}, true);
            {
                this->checkbox(oxorany("bomb"), &g.config.visuals.esp.bomb);
                this->colorpick4(oxorany("##bomb_color"), g.config.visuals.esp.bomb_color);
                this->checkbox(oxorany("dropped weapon"), &g.config.visuals.esp.dropped_weapon);
                this->colorpick4(oxorany("##dropped_weapon_color"), g.config.visuals.esp.dropped_weapon_color);
                this->checkbox(oxorany("dropped grenade"), &g.config.visuals.esp.dropped_grenade);
                this->colorpick4(oxorany("##dropped_grenade_color"), g.config.visuals.esp.dropped_grenade_color);
            }
            this->endChild();
            break;
        }
        case 1: {
            this->beginChild(oxorany("player"), ImVec2{ImGui::GetContentRegionAvail().x / 2 - (this->style->WindowPadding.x / 2), 0.f}, true);
            {
                this->checkbox(oxorany("local"), &g.config.visuals.chams.local);
                this->colorpick4(oxorany("##local_color"), g.config.visuals.chams.local_color);
                if(this->beginCombo(oxorany("##local_mat"), mats[g.config.visuals.chams.local_mat].m_szLabel)) {
                    for(uint8_t i=0;i<IM_ARRAYSIZE(mats);++i) {
                        if(this->page(&mats[i], g.config.visuals.chams.local_mat == i, float4toimvec4(this->m_accent), false))
                            g.config.visuals.chams.local_mat = i;
                    }
                    this->endCombo();
                }
                this->checkbox(oxorany("enemy"), &g.config.visuals.chams.enemy);
                this->colorpick4(oxorany("##enemy_color"), g.config.visuals.chams.enemy_color);
                if(this->beginCombo(oxorany("##enemy_mat"), mats[g.config.visuals.chams.enemy_mat].m_szLabel)) {
                    for(uint8_t i=0;i<IM_ARRAYSIZE(mats);++i) {
                        if(this->page(&mats[i], g.config.visuals.chams.enemy_mat == i, float4toimvec4(this->m_accent), false))
                            g.config.visuals.chams.enemy_mat = i;
                    }
                    this->endCombo();
                }
                this->checkbox(oxorany("teammate"), &g.config.visuals.chams.teammate);
                this->colorpick4(oxorany("##teammate_color"), g.config.visuals.chams.teammate_color);
                if(this->beginCombo(oxorany("##teammate_mat"), mats[g.config.visuals.chams.teammate_mat].m_szLabel)) {
                    for(uint8_t i=0;i<IM_ARRAYSIZE(mats);++i) {
                        if(this->page(&mats[i], g.config.visuals.chams.teammate_mat == i, float4toimvec4(this->m_accent), false))
                            g.config.visuals.chams.teammate_mat = i;
                    }
                    this->endCombo();
                }
            }
            this->endChild();

            this->horPad();

            this->beginChild(oxorany("other"), ImVec2{}, true);
            {
                this->checkbox(oxorany("arms"), &g.config.visuals.chams.arms);
                this->colorpick4(oxorany("##arms_color"), g.config.visuals.chams.arms_color);
                if(this->beginCombo(oxorany("##arms_mat"), mats[g.config.visuals.chams.arms_mat].m_szLabel)) {
                    for(uint8_t i=0;i<IM_ARRAYSIZE(mats);++i) {
                        if(this->page(&mats[i], g.config.visuals.chams.arms_mat == i, float4toimvec4(this->m_accent), false))
                            g.config.visuals.chams.arms_mat = i;
                    }
                    this->endCombo();
                }
                this->checkbox(oxorany("gloves"), &g.config.visuals.chams.gloves);
                this->colorpick4(oxorany("##gloves_color"), g.config.visuals.chams.gloves_color);
                if(this->beginCombo(oxorany("##gloves_mat"), mats[g.config.visuals.chams.gloves_mat].m_szLabel)) {
                    for(uint8_t i=0;i<IM_ARRAYSIZE(mats);++i) {
                        if(this->page(&mats[i], g.config.visuals.chams.gloves_mat == i, float4toimvec4(this->m_accent), false))
                            g.config.visuals.chams.gloves_mat = i;
                    }
                    this->endCombo();
                }
                this->checkbox(oxorany("weapon"), &g.config.visuals.chams.weapon);
                this->colorpick4(oxorany("##weapon_color"), g.config.visuals.chams.weapon_color);
                if(this->beginCombo(oxorany("##weapon_mat"), mats[g.config.visuals.chams.weapon_mat].m_szLabel)) {
                    for(uint8_t i=0;i<IM_ARRAYSIZE(mats);++i) {
                        if(this->page(&mats[i], g.config.visuals.chams.weapon_mat == i, float4toimvec4(this->m_accent), false))
                            g.config.visuals.chams.weapon_mat = i;
                    }
                    this->endCombo();
                }
            }
            this->endChild();
            break;
        }
        default: {
            this->beginChild(oxorany("environment"), ImVec2{ImGui::GetContentRegionAvail().x / 2 - (this->style->WindowPadding.x / 2), 0.f}, true);
            {   
                
                this->checkbox(oxorany("world color"), &g.config.visuals.world.env.world_color);
                this->colorpick4(oxorany("##world_color_color"), g.config.visuals.world.env.world_color_color);
                this->checkbox(oxorany("solid"), &g.config.visuals.world.env.world_color_solid);
                if(this->button(oxorany("update"), ImVec2{})) {
                    if(g.config.visuals.world.env.world_color) {
                        g.config.visuals.world.env.world_color_update = true;
                    }
                }
                this->checkbox(oxorany("sky color"), &g.config.visuals.world.env.sky_color);
                this->colorpick4(oxorany("##sky_color_color"), g.config.visuals.world.env.sky_color_color);
                /*this->checkbox(oxorany("fog"), &g.config.visuals.world.env.fog);
                this->colorpick4(oxorany("##fog_color"), g.config.visuals.world.env.fog_color);
                this->sliderfloat(oxorany("start"), &g.config.visuals.world.env.fog_start, 0.5f, 15.f, "%.1f");
                this->sliderfloat(oxorany("end"), &g.config.visuals.world.env.fog_end, 5.f, 50.f, "%.1f");
                this->sliderfloat(oxorany("density"), &g.config.visuals.world.env.fog_density, 0.5f, 5.f, "%.1f");*/
            }
            this->endChild();

            this->horPad();

            this->beginChild(oxorany("render"), ImVec2{}, true);
            {
                this->checkbox(oxorany("bullet tracer"), &g.config.visuals.world.render.bullet_tracer);
                this->colorpick4(oxorany("##bullet_tracer_color"), g.config.visuals.world.render.bullet_tracer_color);
                //this->checkbox(oxorany("bullet impacts"), &g.config.visuals.world.render.bullet_impacts);
                //this->colorpick4(oxorany("##bullet_impacts_color"), g.config.visuals.world.render.bullet_impacts_color);
                this->checkbox(oxorany("hit marker"), &g.config.visuals.world.render.hit_marker);
                this->colorpick4(oxorany("#hit_marker_color"), g.config.visuals.world.render.hit_marker_color);
            }
            this->endChild();
            break;
        }
    }
}

void CUserInterface::misc() noexcept {
    static ui::page_t removals[] {
        ui::page_t(&g.config.misc.general.removals[0], oxorany("flashbang")),
        ui::page_t(&g.config.misc.general.removals[1], oxorany("smoke")),
        ui::page_t(&g.config.misc.general.removals[2], oxorany("scope")),
        ui::page_t(&g.config.misc.general.removals[3], oxorany("aim punch")),
        ui::page_t(&g.config.misc.general.removals[4], oxorany("scope zoom")),
        ui::page_t(&g.config.misc.general.removals[5], oxorany("arms")),
        ui::page_t(&g.config.misc.general.removals[6], oxorany("weapon"))
    };

    this->beginChild(oxorany("general"), ImVec2{ImGui::GetContentRegionAvail().x / 2 - (this->style->WindowPadding.x / 2), 0}, true);
    {
        this->slideruint8(oxorany("camera fov"), &g.config.misc.general.fov, 30, 150);
        this->slideruint16(oxorany("aspect ratio"), &g.config.misc.general.aspect_ratio_w, 0, 100);
        g.config.misc.general.aspect_ratio_update = !ImGui::IsItemActive();
        this->multiCombo(oxorany("removals"), removals, IM_ARRAYSIZE(removals));
        //this->checkbox(oxorany("left hand"), &g.config.misc.general.left_hand);
        //this->checkbox(oxorany("hitsound"), &g.config.misc.general.hitsound);
        this->checkbox(oxorany("thirdperson"), &g.config.misc.general.thirdperson);
        this->sliderfloat(oxorany("##thirdperson_distance"), &g.config.misc.general.thirdperson_distance, 1.f, 3.f, "%.1fm%");
    }
    this->endChild();

    this->horPad();

    const ImVec2 nextChildPos = ImGui::GetCursorPos() + ImVec2(0.f, ImGui::GetContentRegionAvail().y / 2);

    this->beginChild(oxorany("movement"), ImVec2{0.f, ImGui::GetContentRegionAvail().y / 2 - (this->style->WindowPadding.y)}, true);
    {
        this->checkbox(oxorany("air strafes"), &g.config.misc.movement.air_strafes);
        this->sliderfloat(oxorany("##air_strafes_speed"), &g.config.misc.movement.air_strafes_speed, 2.f, 10.f, "%.1f");
        this->checkbox(oxorany("fast stop"), &g.config.misc.movement.fast_stop);
    }
    this->endChild();

    ImGui::SetCursorPos(nextChildPos);

    this->beginChild(oxorany("viewmodel"), ImVec2{}, true);
    {   
        /*
        this->checkbox(oxorany("enabled"), &g.config.misc.general.viewmodel);
        this->sliderfloat(oxorany("x offset"), &g.config.misc.general.viewmodel_pos.x, -5.f, 5.f, "%.1f");
        this->sliderfloat(oxorany("y offset"), &g.config.misc.general.viewmodel_pos.y, -5.f, 5.f, "%.1f");
        this->sliderfloat(oxorany("z offset"), &g.config.misc.general.viewmodel_pos.z, -5.f, 5.f, "%.1f");
        */
    }
    this->endChild();
}

void CUserInterface::changer() noexcept {
    this->beginChild(oxorany("item"), ImVec2{ImGui::GetContentRegionAvail().x / 2 - (this->style->WindowPadding.x / 2), 0}, true);
    {
        
    }
    this->endChild();

    this->horPad();

    this->beginChild(oxorany("skin"), ImVec2{}, true);
    {
        
    }
    this->endChild();
}

void CUserInterface::config() noexcept {
    static ui::page_t configs[16]{};

    this->beginChild(oxorany("general"), ImVec2{ImGui::GetContentRegionAvail().x / 2 - (this->style->WindowPadding.x / 2), 0.f}, true);
    {
        this->colorpick3(oxorany("accent"), this->m_accent, false);
        this->sliderfloat(oxorany("dpi scale"), &this->m_dpiScale, 0.8f, 1.5f, "%.2f");
    }
    this->endChild();

    this->horPad();

    this->beginChild(oxorany("configs"), ImVec2{}, true);
    {
        static char input[32]{};

        static bool update{};
        if(!update) {
            g.config.update();
            strcpy(input, oxorany("sn0w"));
            for(uint8_t i=0;i<g.config.configsNum;++i) {
                strcpy(configs[i].m_szLabel, g.config.array[i].c_str());
            }
            update = true;
        }
        
        const float width = ImGui::GetContentRegionAvail().x - (this->style->WindowPadding.x * 2);
        
        ImGui::SetNextItemWidth(width);
        this->inputText(oxorany("##new_config_name"), input, sizeof(input));

        if(this->button(oxorany("update"), ImVec2{width, ImGui::GetFrameHeight() * 1.25f})) {
            g.config.update();
            for(uint8_t i=0;i<g.config.configsNum;++i) {
                strcpy(configs[i].m_szLabel, g.config.array[i].c_str());
            }
        }

        if(this->button(oxorany("create and save"), ImVec2{width, ImGui::GetFrameHeight() * 1.25f})) {
            g.config.create(input);
            g.config.update();
            for(uint8_t i=0;i<g.config.configsNum;++i) {
                strcpy(configs[i].m_szLabel, g.config.array[i].c_str());
            }
        }
        if(this->button(oxorany("save"), ImVec2{width, ImGui::GetFrameHeight() * 1.25f})) {
            g.config.save(g.config.currentIndex);
        }
        if(this->button(oxorany("load"), ImVec2{width, ImGui::GetFrameHeight() * 1.25f})) {
            g.config.load(g.config.currentIndex);
        }
        if(this->button(oxorany("delete"), ImVec2{width, ImGui::GetFrameHeight() * 1.25f})) {
            g.config.remove(g.config.currentIndex);
            g.config.update();
        }
        
        ImGui::SetNextItemWidth(width + (ImGui::GetFrameHeight() - 2.f)); // eto pizdec
        if(this->beginCombo(oxorany("##configs"), g.config.array[g.config.currentIndex].empty() ? oxorany("none") : g.config.array[g.config.currentIndex].c_str())) {
            for(uint8_t i=0;i<g.config.configsNum;++i) {
                if(this->page(&configs[i], g.config.currentIndex == i, float4toimvec4(this->m_accent), false)) {
                    g.config.currentIndex = i;
                }
            }
            this->endCombo();
        }
    }
    this->endChild();
}

void CUserInterface::debug() noexcept {
    this->beginChild(oxorany("general"), ImVec2{}, true);
    {
        for(uint8_t i=0;i<8;++i) {
            char name[32]{};
            snprintf(name, sizeof(name), "bool_%u", i);
            this->checkbox(name, &g.config.test.bools[i]);
        }
        this->sliderfloat(oxorany("width"), &g.config.test.floats[0], 1000, 3000);
        this->sliderfloat(oxorany("height"), &g.config.test.floats[1], 800, 2000);
    }
    this->endChild();
}