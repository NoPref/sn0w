#include "c_renderer.hpp"
#include "../globals.hpp"
#include "../includes/imgui/fonts/include.h"

void imgui_fonts_t::init() noexcept {
    ImGuiIO& io = ImGui::GetIO();
    this->ui.verdana              = io.Fonts->AddFontFromMemoryTTF(__verdana,      sizeof(__verdana),      12.f * 4, NULL, io.Fonts->GetGlyphRangesCyrillic()); this->ui.verdana->Scale             = 0.55f;
    this->ui.verdana_pages        = io.Fonts->AddFontFromMemoryTTF(__verdana,      sizeof(__verdana),      12.f * 4, NULL, io.Fonts->GetGlyphRangesCyrillic()); this->ui.verdana_pages->Scale       = 0.60f;
    this->ui.verdana_bold         = io.Fonts->AddFontFromMemoryTTF(__verdana_bold, sizeof(__verdana_bold), 12.f * 4, NULL, io.Fonts->GetGlyphRangesCyrillic()); this->ui.verdana_bold->Scale        = 0.55f;
    this->ui.verdana_bold_child   = io.Fonts->AddFontFromMemoryTTF(__verdana_bold, sizeof(__verdana_bold), 12.f * 4, NULL, io.Fonts->GetGlyphRangesCyrillic()); this->ui.verdana_bold_child->Scale  = 0.50f;
    this->ui.verdana_bold_slider  = io.Fonts->AddFontFromMemoryTTF(__verdana_bold, sizeof(__verdana_bold), 12.f * 4, NULL, io.Fonts->GetGlyphRangesCyrillic()); this->ui.verdana_bold_slider->Scale = 0.40f;
    this->ui.verdana_bold_button  = io.Fonts->AddFontFromMemoryTTF(__verdana_bold, sizeof(__verdana_bold), 12.f * 4, NULL, io.Fonts->GetGlyphRangesCyrillic()); this->ui.verdana_bold_button->Scale = 0.45f;
    this->ui.undefeated           = io.Fonts->AddFontFromMemoryTTF(__undefeated,   sizeof(__undefeated),   12.f * 4, NULL); this->ui.undefeated->Scale       = 0.75f;
    this->ui.undefeated_pages     = io.Fonts->AddFontFromMemoryTTF(__undefeated,   sizeof(__undefeated),   12.f * 4, NULL); this->ui.undefeated_pages->Scale = 0.75f;

    this->esp.tahoma              = io.Fonts->AddFontFromMemoryTTF(__tahoma,       sizeof(__tahoma),       12.f * 2, NULL, io.Fonts->GetGlyphRangesCyrillic()); this->esp.tahoma->Scale             = 0.60f;
    this->esp.verdana_bold        = io.Fonts->AddFontFromMemoryTTF(__verdana_bold, sizeof(__verdana_bold), 12.f * 2, NULL, io.Fonts->GetGlyphRangesCyrillic()); this->esp.verdana_bold->Scale       = 0.45f;
    this->esp.verdana_bold_small  = io.Fonts->AddFontFromMemoryTTF(__verdana_bold, sizeof(__verdana_bold), 12.f * 2, NULL, io.Fonts->GetGlyphRangesCyrillic()); this->esp.verdana_bold_small->Scale = 0.35f;
    this->esp.undefeated          = io.Fonts->AddFontFromMemoryTTF(__undefeated,   sizeof(__undefeated),   12.f * 2, NULL); this->esp.undefeated->Scale        = 0.65f;
    this->esp.undefeated_bigger   = io.Fonts->AddFontFromMemoryTTF(__undefeated,   sizeof(__undefeated),   12.f * 2, NULL); this->esp.undefeated_bigger->Scale = 0.85f;
    this->esp.pixel               = io.Fonts->AddFontFromMemoryTTF(__pixel,        sizeof(__pixel),        12.f * 2, NULL); this->esp.pixel->Scale             = 0.40f;
}

void CImGuiRenderer::init() noexcept {
    ImGui::CreateContext();
    ImGui_ImplAndroid_Init(NULL);
    ImGui_ImplOpenGL3_Init(oxorany("#version 300 es"));
    this->m_fonts.init();
}

void CImGuiRenderer::beginFrame() noexcept {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(g.window.m_iWidth, g.window.m_iHeight);
    ImGui::NewFrame();
}

void CImGuiRenderer::endFrame() noexcept {
    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void CImGuiRenderer::text(ImDrawList* pDrawlist, const ImVec2& vecCoords, const ImColor& color, const char* const& szText, bool shadow, bool outline) noexcept {
    if(shadow && !outline) {
        pDrawlist->AddText(vecCoords + ImVec2(1.f, 1.f), ImColor(0.f, 0.f, 0.f, color.Value.w), szText);
    } else if(outline && !shadow) {
        pDrawlist->AddText(vecCoords + ImVec2(1.f, 0.f), ImColor(0.f, 0.f, 0.f, color.Value.w), szText);
        pDrawlist->AddText(vecCoords + ImVec2(0.f, 1.f), ImColor(0.f, 0.f, 0.f, color.Value.w), szText);
        pDrawlist->AddText(vecCoords + ImVec2(1.f, 1.f), ImColor(0.f, 0.f, 0.f, color.Value.w), szText);
        pDrawlist->AddText(vecCoords - ImVec2(1.f, 0.f), ImColor(0.f, 0.f, 0.f, color.Value.w), szText);
        pDrawlist->AddText(vecCoords - ImVec2(0.f, 1.f), ImColor(0.f, 0.f, 0.f, color.Value.w), szText);
        pDrawlist->AddText(vecCoords - ImVec2(1.f, 1.f), ImColor(0.f, 0.f, 0.f, color.Value.w), szText);
    }
    pDrawlist->AddText(vecCoords, color, szText);
}

void CImGuiRenderer::glow(ImDrawList* const pDrawlist, const ImVec2& vecLeftUpper, const ImVec2& vecRightLower, const ImColor& col, const float& fWidth, bool bInner) noexcept {
	if (!bInner) {
		pDrawlist->AddRectFilledMultiColor(vecLeftUpper - ImVec2(0, fWidth), ImVec2(vecRightLower.x, vecLeftUpper.y), ImColor(0, 0, 0, 0), ImColor(0, 0, 0, 0), col, col);/*up*/
		pDrawlist->AddRectFilledMultiColor(ImVec2(vecRightLower.x, vecLeftUpper.y), vecRightLower + ImVec2(fWidth, 0), col, ImColor(0, 0, 0, 0), ImColor(0, 0, 0, 0), col);/*right*/
		pDrawlist->AddRectFilledMultiColor(ImVec2(vecLeftUpper.x, vecRightLower.y), vecRightLower + ImVec2(0, fWidth), col, col, ImColor(0, 0, 0, 0), ImColor(0, 0, 0, 0));/*down*/
		pDrawlist->AddRectFilledMultiColor(vecLeftUpper - ImVec2(fWidth,0), ImVec2(vecLeftUpper.x, vecRightLower.y), ImColor(0,0,0,0), col, col, ImColor(0, 0, 0, 0));/*left*/

		pDrawlist->AddRectFilledMultiColor(vecLeftUpper - ImVec2(fWidth,fWidth), vecLeftUpper, ImColor(0,0,0,0), ImColor(0, 0, 0, 0), col, ImColor(0, 0, 0, 0));/*left angle*/
		pDrawlist->AddRectFilledMultiColor(ImVec2(vecRightLower.x + fWidth, vecLeftUpper.y - fWidth), ImVec2(vecRightLower.x, vecLeftUpper.y), ImColor(0, 0, 0, 0), ImColor(0, 0, 0, 0), col, ImColor(0, 0, 0, 0));/*right angle*/
		pDrawlist->AddRectFilledMultiColor(vecRightLower + ImVec2(fWidth, fWidth), vecRightLower, ImColor(0, 0, 0, 0), ImColor(0, 0, 0, 0), col, ImColor(0, 0, 0, 0));/*right lower angle*/
		pDrawlist->AddRectFilledMultiColor(ImVec2(vecLeftUpper.x - fWidth, vecRightLower.y + fWidth), ImVec2(vecLeftUpper.x, vecRightLower.y), ImColor(0, 0, 0, 0), ImColor(0, 0, 0, 0), col, ImColor(0, 0, 0, 0));/*right lower angle*/
	}
	else {
		pDrawlist->AddRectFilledMultiColor(vecLeftUpper + ImVec2(fWidth, 0), ImVec2(vecRightLower.x - fWidth, vecLeftUpper.y + fWidth), col, col, ImColor(0, 0, 0, 0), ImColor(0, 0, 0, 0));/*up*/
		pDrawlist->AddRectFilledMultiColor(ImVec2(vecRightLower.x - fWidth, vecLeftUpper.y + fWidth), vecRightLower - ImVec2(0, fWidth), ImColor(0, 0, 0, 0), col, col, ImColor(0, 0, 0, 0));/*right*/
		pDrawlist->AddRectFilledMultiColor(ImVec2(vecLeftUpper.x + fWidth, vecRightLower.y - fWidth), vecRightLower - ImVec2(fWidth, 0), ImColor(0, 0, 0, 0), ImColor(0, 0, 0, 0), col, col);/*down*/
		pDrawlist->AddRectFilledMultiColor(vecLeftUpper + ImVec2(0, fWidth), ImVec2(vecLeftUpper.x + fWidth, vecRightLower.y - fWidth), col, ImColor(0, 0, 0, 0), ImColor(0, 0, 0, 0), col);/*left*/

		pDrawlist->AddRectFilledMultiColor(vecLeftUpper, vecLeftUpper + ImVec2(fWidth, fWidth), col, col, ImColor(0, 0, 0, 0), col);/*left angle*/
		pDrawlist->AddRectFilledMultiColor(ImVec2(vecRightLower.x, vecLeftUpper.y), ImVec2(vecRightLower.x - fWidth, vecLeftUpper.y + fWidth), col, col, ImColor(0, 0, 0, 0), col);/*right angle*/
		pDrawlist->AddRectFilledMultiColor(vecRightLower, vecRightLower - ImVec2(fWidth, fWidth), col, col, ImColor(0, 0, 0, 0), col);/*right lower angle*/
		pDrawlist->AddRectFilledMultiColor(ImVec2(vecLeftUpper.x, vecRightLower.y), ImVec2(vecLeftUpper.x + fWidth, vecRightLower.y - fWidth), col, col, ImColor(0, 0, 0, 0), col);/*right lower angle*/
	}
}

void CImGuiRenderer::glowCircle(ImDrawList* const pDrawlist, const ImVec2& vecCoords, const float& fRadius, const ImColor& col, bool bInner) noexcept {
	if (!bInner) {
		pDrawlist->AddRectFilledMultiColor(vecCoords - ImVec2(fRadius, 0), vecCoords - ImVec2(0, fRadius), ImColor(0, 0, 0, 0), col, ImColor(0, 0, 0, 0), ImColor(0, 0, 0, 0));/*left*/
		pDrawlist->AddRectFilledMultiColor(vecCoords + ImVec2(fRadius, 0), vecCoords - ImVec2(0, fRadius), ImColor(0, 0, 0, 0), col, ImColor(0, 0, 0, 0), ImColor(0, 0, 0, 0));/*right*/
		pDrawlist->AddRectFilledMultiColor(vecCoords + ImVec2(fRadius, 0), vecCoords + ImVec2(0, fRadius), ImColor(0, 0, 0, 0), col, ImColor(0, 0, 0, 0), ImColor(0, 0, 0, 0));/*right lower*/
		pDrawlist->AddRectFilledMultiColor(vecCoords - ImVec2(fRadius, 0), vecCoords + ImVec2(0, fRadius), ImColor(0, 0, 0, 0), col, ImColor(0, 0, 0, 0), ImColor(0, 0, 0, 0));/*left lower*/
	}
}

void CImGuiRenderer::box(ImDrawList* pDrawlist, const ImVec2& vecMin, const ImVec2& vecMax, const ImColor& color, bool outline, bool corners, float roundness) noexcept {
    const float thick = 2.f;
    if(!corners) {
        pDrawlist->AddRect(vecMin, vecMax, color, 0.f, 0, thick);
        if(outline) {
            pDrawlist->AddRect(vecMin - ImVec2(thick/2, thick/2), vecMax + ImVec2(thick/2, thick/2), ImColor(0.f, 0.f, 0.f, color.Value.w), roundness, 0, 1.f);
            pDrawlist->AddRect(vecMin + ImVec2(thick, thick), vecMax - ImVec2(thick, thick), ImColor(0.f, 0.f, 0.f, color.Value.w), roundness, 0, 1.f);
        }
    } else {
        const ImVec2 size = vecMax - vecMin;
        const float width = size.x / 4;
        const float height = size.y / 5;

        if(outline) {
            //left upper
            pDrawlist->AddLine(vecMin - ImVec2(1.f, 0.f), vecMin + ImVec2(width, 0.f) + ImVec2(1.f, 0.f), ImColor(0.f, 0.f, 0.f, color.Value.w), thick * 2);
            pDrawlist->AddLine(vecMin - ImVec2(0.f, 1.f), vecMin + ImVec2(0.f, height) + ImVec2(0.f, 1.f), ImColor(0.f, 0.f, 0.f, color.Value.w), thick * 2);

            //right upper
            pDrawlist->AddLine(ImVec2(vecMax.x - width, vecMin.y) - ImVec2(1.f, 0.f), ImVec2(vecMax.x, vecMin.y) + ImVec2(1.f, 0.f), ImColor(0.f, 0.f, 0.f, color.Value.w), thick * 2);
            pDrawlist->AddLine(ImVec2(vecMax.x, vecMin.y) - ImVec2(0.f, 1.f), ImVec2(vecMax.x, vecMin.y + height) + ImVec2(0.f, 1.f), ImColor(0.f, 0.f, 0.f, color.Value.w), thick * 2);

            //left lower
            pDrawlist->AddLine(ImVec2(vecMin.x, vecMax.y) - ImVec2(1.f, 0.f), ImVec2(vecMin.x + width, vecMax.y) + ImVec2(1.f, 0.f), ImColor(0.f, 0.f, 0.f, color.Value.w), thick * 2);
            pDrawlist->AddLine(ImVec2(vecMin.x, vecMax.y - height) - ImVec2(0.f, 1.f), ImVec2(vecMin.x, vecMax.y) + ImVec2(0.f, 1.f), ImColor(0.f, 0.f, 0.f, color.Value.w), thick * 2);

            //right lower
            pDrawlist->AddLine(ImVec2(vecMax.x - width, vecMax.y) - ImVec2(1.f, 0.f), ImVec2(vecMax.x, vecMax.y) + ImVec2(1.f, 0.f), ImColor(0.f, 0.f, 0.f, color.Value.w), thick * 2);
            pDrawlist->AddLine(ImVec2(vecMax.x, vecMax.y - height) - ImVec2(0.f, 1.f), ImVec2(vecMax.x, vecMax.y) + ImVec2(0.f, 1.f), ImColor(0.f, 0.f, 0.f, color.Value.w), thick * 2);
        }

        //left upper
        pDrawlist->AddLine(vecMin - ImVec2(1.f, 0.f), vecMin + ImVec2(width, 0.f) + ImVec2(1.f, 0.f), color, thick);
        pDrawlist->AddLine(vecMin - ImVec2(0.f, 1.f), vecMin + ImVec2(0.f, height) + ImVec2(0.f, 1.f), color, thick);

        //right upper
        pDrawlist->AddLine(ImVec2(vecMax.x - width, vecMin.y) - ImVec2(1.f, 0.f), ImVec2(vecMax.x, vecMin.y) + ImVec2(1.f, 0.f), color, thick);
        pDrawlist->AddLine(ImVec2(vecMax.x, vecMin.y) - ImVec2(0.f, 1.f), ImVec2(vecMax.x, vecMin.y + height) + ImVec2(0.f, 1.f), color, thick);

        //left lower
        pDrawlist->AddLine(ImVec2(vecMin.x, vecMax.y) - ImVec2(1.f, 0.f), ImVec2(vecMin.x + width, vecMax.y) + ImVec2(1.f, 0.f), color, thick);
        pDrawlist->AddLine(ImVec2(vecMin.x, vecMax.y - height) - ImVec2(0.f, 1.f), ImVec2(vecMin.x, vecMax.y) + ImVec2(0.f, 1.f), color, thick);

        //right lower
        pDrawlist->AddLine(ImVec2(vecMax.x - width, vecMax.y) - ImVec2(1.f, 0.f), ImVec2(vecMax.x, vecMax.y) + ImVec2(1.f, 0.f), color, thick);
        pDrawlist->AddLine(ImVec2(vecMax.x, vecMax.y - height) - ImVec2(0.f, 1.f), ImVec2(vecMax.x, vecMax.y) + ImVec2(0.f, 1.f), color, thick);
    }
}

void CImGuiRenderer::boxFilled(ImDrawList* pDrawlist, const ImVec2& vecMin, const ImVec2& vecMax, const ImColor& color, float roundness) noexcept {
    pDrawlist->AddRectFilled(vecMin, vecMax, color, roundness);
}

void CImGuiRenderer::line(ImDrawList* pDrawlist, const ImVec2& vecStart, const ImVec2& vecEnd, const ImColor& color, float thick) noexcept {
    pDrawlist->AddLine(vecStart, vecEnd, color, thick);
}

void CImGuiRenderer::circle(ImDrawList* pDrawlist, const ImVec2& vecCoords, const float& radius, const ImColor& color, float thick) noexcept {
    pDrawlist->AddCircle(vecCoords, radius, color, 0.f, thick);
}

ImRect CImGuiRenderer::progressBar(ImDrawList* pDrawlist, const ImVec2& vecMin, const ImVec2& vecMax, const ImColor& color, const float& maxValue, const float& curValue, bool outline, bool horizontal, bool showText, const char* format) noexcept {
    if (outline) {
        pDrawlist->AddRectFilled(vecMin, vecMax, ImColor(0.f, 0.f, 0.f, 0.8f - (1.f - color.Value.w)), 0.f, 0);
    }
    const float diff = (horizontal ? (vecMax.x - vecMin.x) : vecMax.y - vecMin.y);
    const float progress = ((diff * curValue) / maxValue);

    const ImVec2 p1 {
        vecMin.x,
        (horizontal ? vecMin.y : vecMax.y - progress)
    };

    const ImVec2 p2 {
        (horizontal ? vecMin.x + progress : vecMax.x),
        vecMax.y
    };

    if (curValue > 0) {
        pDrawlist->AddRectFilled(p1, p2, color);
    }

    if (outline) {
        pDrawlist->AddRect(vecMin - ImVec2(1.f, 1.f), vecMax + ImVec2(1.f, 1.f), ImColor(0.f, 0.f, 0.f, color.Value.w), 0.f, 0);
    }

    if(showText) {
        if(curValue < maxValue) {
            ImGui::PushFont(this->m_fonts.esp.pixel);

            char szValue[128]{};
            if(format[1] == 'd')
                snprintf(szValue, sizeof(szValue), format, (int32_t)curValue);
            else if(format[1] == 'u')
                snprintf(szValue, sizeof(szValue), format, (uint32_t)curValue);
            else
                snprintf(szValue, sizeof(szValue), format, curValue);

            const ImVec2 vecTextSize = ImGui::CalcTextSize(szValue);
            
            if(horizontal) {
                this->text(
                    pDrawlist,
                    ImVec2(p2.x - (vecTextSize.x / 2), p2.y - (vecTextSize.y / 2)),
                    ImColor(1.f, 1.f, 1.f, color.Value.w),
                    szValue,
                    false,
                    true
                );
            } else {
                this->text(
                    pDrawlist,
                    ImVec2(p2.x - ((p2.x - p1.x) / 2) - (vecTextSize.x / 2), p1.y - (vecTextSize.y / 2)),
                    ImColor(1.f, 1.f, 1.f, color.Value.w),
                    szValue,
                    false,
                    true
                );
            }
            
            ImGui::PopFont();
        }
    }

    return ImRect{p1, p2};
}