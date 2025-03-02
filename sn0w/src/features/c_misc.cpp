#include "c_misc.hpp"
#include "../globals.hpp"

void CMisc::disableOccludee() noexcept {
    if(g.vars.players.isEmpty())
        return;
    for(uint8_t i=0;i<g.vars.players.getSize();++i) {
        CPlayerController* player = g.vars.players[i];
        if(player != NULL) {
            if(player->isAlive()) {
                player->forceVisible();
            }
        }   
    }
}

void CMisc::clampAngles() noexcept {
    if(g.vars.players.m_local != NULL) {
        if(g.vars.players.m_local->isAlive()) {
            g.vars.players.m_local->clampAngles();
        }
    }
}

void CMisc::cameraFOV() noexcept {
    const CLocalPlayer* local = g.vars.players.m_local;
    if(g.vars.mainCamera != NULL && local != NULL) {
        if(local->isAlive()) {
            if(!local->isScoped()) {
                g.vars.mainCamera->setFOV((float)g.config.misc.general.fov);
                g.vars.updateMatrix();
            }
        }
    }
}

void CMisc::removals() noexcept {
    CLocalPlayer* local = g.vars.players.m_local;
    static bool updateScope{};
    static bool updateArms{};
    static bool updateWeapon{};

    if(g.vars.pHUDView == NULL) {
        updateScope = false;
        return;
    }

    if(local == NULL) {
        updateArms = false;
        updateWeapon = false;
        return;
    }

    if(!local->isAlive()) {
        updateArms = false;
        updateWeapon = false;
        return;
    }

    //flashbang & smoke
    if(g.vars.pGrenadeEffectEmitter != NULL) {
        dictionary_t<weapon_id, list_t<C_Component*>*>* emitters = *(decltype(emitters)*)((unsigned long long)g.vars.pGrenadeEffectEmitter + ofs(grenade_effect_emitter.effects));
        if(emitters != NULL) {
            if(emitters->isValid()) {
                for(uint8_t i=0;i<emitters->getSize();++i) {
                    list_t<C_Component*>* effects = emitters->get(i).m_value;
                    if(effects != NULL) {
                        if(effects->isValid()) {
                            if(emitters->get(i).m_key == weapon_id_grenade_flash) {
                                for(uint32_t f=0;f<effects->getSize();++f) {
                                    C_Component* flashEffect = effects->get(f);
                                    if(flashEffect != NULL) {
                                        if(g.config.misc.general.removals[0]) {
                                            *(float*)((unsigned long long)flashEffect + ofs(flashbang_effect_controller.progress)) = 1.f;
                                        }
                                    }
                                }
                            }
                            //shitass not working
                            /*if(emitters->get(i).m_key == weapon_id_grenade_smoke) {
                                static float oldDuration{};
                                for(uint32_t s=0;s<effects->getSize();++s) {
                                    C_Component* smokeEffect = effects->get(s);
                                    if(smokeEffect != NULL) {
                                        void* pars = *(void**)((unsigned long long)smokeEffect + oxorany(0x38));
                                        if(pars != NULL) {
                                            float* pDuration = (float*)((unsigned long long)pars + oxorany(0x30));
                                            
                                        }
                                    }
                                }
                            }*/
                        }
                    }
                }
            }
        }
    }
        
    //scope
    if(updateScope != g.config.misc.general.removals[2]) {
        void* aimView = *(void**)((unsigned long long)g.vars.pHUDView + ofs(hud_view.aim));
        if(aimView != NULL) {
            C_Component* sniperScope = *(C_Component**)((unsigned long long)aimView + ofs(aim_view.sniper_sight));
            if(sniperScope != NULL) {
                if(sniperScope->getGameObject() != NULL) {
                    updateScope = g.config.misc.general.removals[2];
                    sniperScope->getGameObject()->setActive(!updateScope);
                }
            }
        }
    }

    //scope zoom
    if(g.config.misc.general.removals[4] && local->isScoped() && g.vars.mainCamera != NULL) {
        g.vars.mainCamera->setFOV(g.config.misc.general.fov);
        g.vars.updateMatrix();
    }

    //arms
    if(updateArms != g.config.misc.general.removals[5]) {
        if(local->m_armsLODGroup != NULL && local->m_viewMode == view_mode_fps) {
            updateArms = g.config.misc.general.removals[5];
            CArmsLodGroup* lod = local->m_armsLODGroup;
            if(lod->m_armsMeshRenderer != NULL && lod->m_glovesMeshRenderer != NULL) {
                CRenderer* arms = lod->m_armsMeshRenderer;
                CRenderer* gloves = lod->m_glovesMeshRenderer;
                if(arms->getGameObject() != NULL && gloves->getGameObject() != NULL) {
                    arms->getGameObject()->setActive(!updateArms);
                    gloves->getGameObject()->setActive(!updateArms);
                }
            }
        }
    }

    //weapons
    if(updateWeapon != g.config.misc.general.removals[6]) {
        if(local->m_weaponry->m_dWeaponSlots != NULL) {
            dictionary_t<uint8_t, CWeaponController*>* weapons = local->m_weaponry->m_dWeaponSlots;
            if(weapons->isValid()) {
                updateWeapon = g.config.misc.general.removals[6];
                for(uint8_t i=0;i<weapons->getSize();++i) {
                    CWeaponController* weapon = weapons->get(i).m_value;
                    if(weapon != NULL) {
                        if(weapon->m_LODGroup != NULL) {
                            array_t<CRenderer*>* renderers = weapon->m_LODGroup->m_aMeshRenderers;
                            if(renderers != NULL) {
                                if(renderers->isValid()) {
                                    for(uint8_t r=0;r<renderers->m_iCapacity;++r) {
                                        CRenderer* renderer = renderers->get(r);
                                        if(renderer != NULL) {
                                            if(renderer->getGameObject() != NULL) {
                                                renderer->getGameObject()->setActive(!updateWeapon);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

}

void CMisc::removalsR() noexcept {
    const CLocalPlayer* local = g.sn0w.esp->m_players.m_local;
    if(local != NULL) {
        if(local->isAlive()) {
            //scope
            if(g.config.misc.general.removals[2]) {
                if(local->isScoped()) {
                    if(local->getCurrentWeapon()->getType() == weapon_type_sniper) {
                        const ImVec2 res = ImVec2{(float)g.window.m_iWidth, (float)g.window.m_iHeight};
                        g.renderer.imgui->line(g.sn0w.esp->m_pDrawlist, ImVec2{0.f, res.y / 2}, ImVec2{res.x, res.y / 2}, ImColor{0.f, 0.f, 0.f, 1.f}, 2.f);
                        g.renderer.imgui->line(g.sn0w.esp->m_pDrawlist, ImVec2{res.x/2, 0.f}, ImVec2{res.x / 2, res.y}, ImColor{0.f, 0.f, 0.f, 1.f}, 2.f);
                    }
                }
            }

        }
    }
}

void CMisc::hitsound() noexcept {

}

void CMisc::thirdperson() noexcept {
    static float currentDistance{};
    static float currentOffset = 1.6f;
    static bool updateView = true;

    CLocalPlayer* local = g.vars.players.m_local;
    if(local == NULL || g.vars.mainCamera == NULL) {
        currentDistance = 0.f;
        updateView = true;
        return;
    }
    if(!local->isAlive() || g.vars.mainCamera->getTransform() == NULL) {
        currentDistance = 0.f;
        updateView = true;
        return;
    }

    const CWeaponController* weapon = local->getCurrentWeapon();
    if(weapon == NULL) {
        currentDistance = 0.f;
        updateView = true;
        return;
    }
    
    currentDistance = ImLerp(currentDistance, ((g.config.misc.general.thirdperson && weapon->getType() != weapon_type_grenade) ? g.config.misc.general.thirdperson_distance : 0), ImGui::GetIO().DeltaTime*8);
    
    if(currentDistance > 0.25f) {
        if(updateView) {
            local->setView(view_mode_tps);
            updateView = false;
        }

        currentOffset = ImLerp(currentOffset, (local->isCrouching() ? 1.35f : 1.6f), ImGui::GetIO().DeltaTime*8);

        const vec3_t vecOrigin = local->m_transform->getPosition();
        const vec3_t vecForward = g.vars.mainCamera->getTransform()->getForward();
        g.vars.mainCamera->getTransform()->setPosition(vecOrigin + vec3_t{0, currentOffset, 0} - (vecForward * currentDistance));
    } else {
        if(!updateView) {
            local->setView(view_mode_fps);
            updateView = true;
        }
    }
}

void CMisc::airStrafes() noexcept {
    static float originalSpeed{};
    static bool update{};

    CLocalPlayer* local = g.vars.players.m_local;
    if(local != NULL) {
        CMovementController* movement = local->m_movement;
        if(movement != NULL) {
            CPlayerTranslationData* data = movement->m_data;
            CPlayerTranslationParameters* pars = movement->m_parameters;
            if(data != NULL && pars != NULL) {
                if(pars->m_jumpParameters != NULL) {
                    float& jumpSpeed = pars->m_jumpParameters->m_fJumpMoveSpeed;

                    if(originalSpeed <= 0)
                        originalSpeed = jumpSpeed;

                    if(g.config.misc.movement.air_strafes) {
                        data->m_vecMoveDirection = vec3_t{};
                        jumpSpeed = g.config.misc.movement.air_strafes_speed;
                        update = true;
                    } else {
                        if(update) {
                            jumpSpeed = originalSpeed;
                            update = false;
                        }
                    }

                }
            }
        }
    }

}

void CMisc::fastStop() noexcept {
    static float originalMoveSpeed{};
    static float originalMecanimSpeed{};
    static bool update{};

    CLocalPlayer* local = g.vars.players.m_local;
    if(local != NULL) {
        CMovementController* movement = local->m_movement;
        if(movement != NULL) {
            CPlayerTranslationParameters* pars = movement->m_parameters;
            if(pars != NULL) {
                float& mecanimSpeed = pars->m_fMecanimDirectionChangeSpeed;
                float& moveSpeed = pars->m_fMoveDirectionChangeSpeed;

                if(originalMoveSpeed <= 0) {
                    originalMoveSpeed = moveSpeed;
                    originalMecanimSpeed = mecanimSpeed;
                }

                if(g.config.misc.movement.fast_stop) {
                    moveSpeed = 10.f;
                    mecanimSpeed = 10.f;
                    update = true;
                } else {
                    if(update) {
                        moveSpeed = originalMoveSpeed;
                        mecanimSpeed = originalMecanimSpeed;
                        update = false;
                    }
                }

            }
        }
    }
}

void CMisc::viewmodel() noexcept {

}

//хотел через камеру сделать но чето забил на это (в либюнити смещение на aspect найти т.к set_aspect нету в ил2спп)
void CMisc::aspectRatio() noexcept {
    const uint16_t width = g.screen.m_iWidth - (g.config.misc.general.aspect_ratio_w * 15);
    if(width != g.window.m_iWidth && g.config.misc.general.aspect_ratio_update) {
        CScreen::setResolution(width, g.window.m_iHeight);
    }
}

void CMisc::test() noexcept {
    
}

void CMisc::update() noexcept {
    CMisc* const& thiz = g.sn0w.misc;
    thiz->disableOccludee();
    thiz->clampAngles();
    thiz->cameraFOV();
    thiz->removals();
    //thiz->hitsound();
    thiz->airStrafes();
    thiz->fastStop();
    //thiz->viewmodel();
    thiz->aspectRatio();
    thiz->test();
}

void CMisc::lateUpdate() noexcept {
    CMisc* const& thiz = g.sn0w.misc;
    thiz->thirdperson();
}

void CMisc::render() noexcept {
    CMisc* const& thiz = g.sn0w.misc;
    thiz->removalsR();
}