#include "c_cheat_manager.hpp"
#include "../globals.hpp"

void C_CheatManager::init() noexcept {
    this->ui       = CUserInterface::inst();
    this->esp      = C_ESP::inst();
    this->aimbot   = CAimbot::inst();
    this->visuals  = CVisuals::inst();
    this->chams    = C_Chams::inst();
    this->misc     = CMisc::inst();
    this->legit    = CLegitbot::inst();
    this->rage     = CRagebot::inst();
    this->antiaim  = CAntiAim::inst();
    this->changer  = C_Changer::inst();
    this->exploits = CExploits::inst();
}

void C_CheatManager::render() noexcept {
    g.sn0w.ui->handleTouches();
    g.sn0w.ui->render();

    g.sn0w.esp->render();
    g.sn0w.misc->render();
    g.sn0w.visuals->render();
}

void C_CheatManager::createMove() noexcept {
    g.sn0w.legit->createMove();
    g.sn0w.exploits->createMove();
    g.sn0w.rage->createMove();
    g.sn0w.antiaim->createMove();
}

void C_CheatManager::lateUpdate() noexcept {
    g.sn0w.rage->lateUpdate();
    g.sn0w.antiaim->lateUpdate();
    g.sn0w.exploits->lateUpdate();
    g.sn0w.misc->lateUpdate();
}

void C_CheatManager::update() noexcept {
    g.sn0w.exploits->update();
    g.sn0w.rage->update();
    g.sn0w.misc->update();
    g.sn0w.visuals->update();
    g.sn0w.chams->update();
}

void C_CheatManager::hit() noexcept {
    
}

void C_CheatManager::hitP() noexcept {
    //g.sn0w.esp.hitP();
}

void C_CheatManager::gui() noexcept {
    //g.sn0w.ui.gui();
}
void C_CheatManager::repaint() noexcept {
    /*g.sn0w.esp.repaint();
    g.renderer->man->handleTouches();*/
}