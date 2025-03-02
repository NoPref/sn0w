#pragma once
#include <stdint.h>
#include "f_include.hpp"

class C_CheatManager {
public:
    CUserInterface* ui{};
    C_ESP*          esp{};
    CAimbot*        aimbot{};
    CVisuals*       visuals{};
    C_Chams*        chams{};
    CMisc*          misc{};
    CLegitbot*      legit{};
    CRagebot*       rage{};
    CExploits*      exploits{};
    CAntiAim*       antiaim{};
    C_Changer*      changer{};

    C_CheatManager() = default;
    ~C_CheatManager() = default;

    void init() noexcept;

    static void render() noexcept;
    static void createMove() noexcept;
    static void lateUpdate() noexcept;
    static void update() noexcept;
    static void hit() noexcept;
    static void hitP() noexcept;
    static void gui() noexcept;
    static void repaint() noexcept;
};