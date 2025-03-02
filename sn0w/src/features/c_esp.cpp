#include "c_esp.hpp"
#include "../globals.hpp"

//old code idgaf

void C_ESP::render() noexcept {
    g.sn0w.esp->updateVars();
    if(g.sn0w.esp->m_pCamera != NULL && g.sn0w.esp->m_players.m_localPhoton != NULL) {
        if(g.sn0w.esp->m_pCamera->getTransform() != NULL && g.sn0w.esp->m_players.m_localPhoton->getTeam() != team_none) {
            g.sn0w.esp->players();
            g.sn0w.esp->droppedWeapons();
            g.sn0w.esp->droppedGrenades();
            g.sn0w.esp->bomb();
        }
    }
}

void C_ESP::updateVars() noexcept {
    //if(this->m_pDrawlist == NULL)
        this->m_pDrawlist = ImGui::GetBackgroundDrawList();
    
    this->m_pCamera = C_Camera::getMain();
    if(this->m_pCamera == NULL) {
        this->m_players.m_local = NULL;
        this->m_players.m_data = NULL;
        this->m_droppedGrenades = NULL;
        this->m_droppedWeapons = NULL;
        this->m_pPlantedBomb = NULL;
        return;
    }

    static FieldInfo* pNetworkingPeerF{};
    if(pNetworkingPeerF == NULL)
        pNetworkingPeerF = g.il2cpp.class_get_field_from_name(g.il2cpp.getClass(oxorany("PhotonNetwork"), oxorany(""), oxorany("Assembly-CSharp.dll")), oxorany("networkingPeer"));
    else
        g.il2cpp.field_static_get_value(pNetworkingPeerF, &this->m_pNetworkingPeer);
    
    static FieldInfo* pPlayerManagerF{};
    if(pPlayerManagerF == NULL)
        pPlayerManagerF = g.il2cpp.getSingletonField(g.il2cpp.getClass(oxorany("PlayerManager"), oxorany("Axlebolt.Standoff.Player"), oxorany("Assembly-CSharp.dll")));
    else
        g.il2cpp.field_static_get_value(pPlayerManagerF, &this->m_pPlayerManager);

    static FieldInfo* pWeaponDropManagerF{};
    if(pWeaponDropManagerF == NULL)
        pWeaponDropManagerF = g.il2cpp.getSingletonField(g.il2cpp.getClass(oxorany("WeaponDropManager"), oxorany("Axlebolt.Standoff.Inventory.Drop"), oxorany("Assembly-CSharp.dll")));
    else 
        g.il2cpp.field_static_get_value(pWeaponDropManagerF, &this->m_pWeaponDropManager);

    static FieldInfo* pGrenadeManagerF{};
    if(pGrenadeManagerF == NULL)
        pGrenadeManagerF = g.il2cpp.getSingletonField(g.il2cpp.getClass(oxorany("GrenadeManager"), oxorany("Axlebolt.Standoff.Inventory.Grenade"), oxorany("Assembly-CSharp.dll")));
    else
        g.il2cpp.field_static_get_value(pGrenadeManagerF, &this->m_pGrenadeManager);

    static FieldInfo* pBombManagerF{};
    if(pBombManagerF == NULL)
        pBombManagerF = g.il2cpp.getSingletonField(g.il2cpp.getClass(oxorany("BombManager"), oxorany("Axlebolt.Standoff.Inventory.Bomb"), oxorany("Assembly-CSharp.dll")));
    else
        g.il2cpp.field_static_get_value(pBombManagerF, &this->m_pBombManager);

    //----------------------------------------

    if(this->m_pNetworkingPeer != NULL) {
        this->m_players.m_localPhoton = *(CPhotonPlayer**)((unsigned long long)this->m_pNetworkingPeer + ofs(networking_peer.localplayer));
    } else {
        this->m_players.m_localPhoton = NULL;
    }

    if(this->m_pPlayerManager != NULL) {
        this->m_players.m_local = *(CLocalPlayer**)((unsigned long long)this->m_pPlayerManager + ofs(player_manager.localplayer));
        this->m_players.m_data = *(decltype(this->m_players.m_data)*)((unsigned long long)this->m_pPlayerManager + ofs(player_manager.players_d));
    } else {
        this->m_players.m_data = NULL;
        this->m_players.m_local = NULL;
    }

    if(this->m_pGrenadeManager != NULL) {
        this->m_droppedGrenades = *(decltype(this->m_droppedGrenades)*)((unsigned long long)this->m_pGrenadeManager + ofs(grenade_manager.dropped));
    } else {
        this->m_droppedGrenades = NULL;
    }

    if(this->m_pWeaponDropManager != NULL) {
        this->m_droppedWeapons = *(decltype(this->m_droppedWeapons)*)((unsigned long long)this->m_pWeaponDropManager + ofs(weapon_drop_manager.dropped));
    } else {
        this->m_droppedWeapons = NULL;
    }

    if(this->m_pBombManager != NULL) {
        this->m_pPlantedBomb = *(CPlantedBombController**)((unsigned long long)this->m_pBombManager + ofs(bomb_manager.planted));
    } else {
        this->m_pPlantedBomb = NULL;
    }
}

ImRect C_ESP::getRect(const vec3_t& vecCoords, const vec3_t& vecHeadCoords, const float& width) noexcept {
    const float height = ((vecCoords.y - vecHeadCoords.y) * width);
    ImRect ret {
        (vecHeadCoords.x > vecCoords.x ? vecCoords.x : vecHeadCoords.x) - (height / 2),
        (vecHeadCoords.y > vecCoords.y ? vecCoords.y : vecHeadCoords.y),                                 
        (vecHeadCoords.x > vecCoords.x ? vecHeadCoords.x : vecCoords.x) + (height / 2),
        (vecHeadCoords.y > vecCoords.y ? vecHeadCoords.y : vecCoords.y), 
    };
    return ret;
}

float C_ESP::getAlphaFactor(const vec3_t& vecOrigin, float startDistance) const noexcept {
    const float distance = g.sn0w.esp->m_pCamera->getTransform()->getPosition().distanceTo(vecOrigin);
    if(distance > 0.f)
        return (1.f - ImClamp<float>(distance / startDistance, 0.f, 1.f));
    return 0.f;
}

void C_ESP::players() noexcept {
    if(g.config.visuals.esp.enabled) {
        if(!this->m_players.isEmpty() && g.vars.maxCTHealth > 0 && g.vars.maxTHealth > 0) {
            for(uint8_t i=0;i<this->m_players.getSize();++i) {
                const CPlayerController* player = this->m_players[i];
                if(player != NULL) {
                    if(player->isAlive()) {
                        const team team = player->m_photon->getTeam();
                        if(g.config.visuals.esp.teammates ? true : (team != this->m_players.m_localPhoton->getTeam())) {
                            const vec3_t  vecOrigin     = player->m_transform->getPosition();
                            const vec3_t  vecHead       = vecOrigin + vec3_t{0.f, (player->isCrouching() ? 1.5f : 1.7f), 0.f};
                            const vec3_t  vecCoords     = C_Camera::w2s(vecOrigin);
                            const vec3_t  vecHeadCoords = C_Camera::w2s(vecHead);
                            if(vecCoords.z > 0 && vecHeadCoords.z > 0) {
                                const ImRect rect = C_ESP::getRect(vecCoords, vecHeadCoords, 0.60f);
                                const float alphaFactor = this->getAlphaFactor(vecOrigin);

                                if(g.config.visuals.esp.box) {
                                    ImColor col = float4toimcolor(g.config.visuals.esp.box_color);
                                    col.Value.w = ImClamp<float>(col.Value.w - alphaFactor, 0.f, 1.f);

                                    g.renderer.imgui->box(
                                        this->m_pDrawlist, 
                                        rect.Min, rect.Max, 
                                        col, 
                                        true, 
                                        g.config.visuals.esp.box_type
                                    );
                                }

                                if(g.config.visuals.esp.health) {
                                    const int32_t health        = player->m_photon->getHealth();
                                    const int32_t maxHealth     = (player->m_photon->getTeam() == team_tr ? g.vars.maxTHealth : g.vars.maxCTHealth);

                                    ImColor col{};
                                    if(g.config.visuals.esp.health_type) {
                                        const float normalizedHealth = (float)health/(float)maxHealth;
                                        col = ImColor(1.f - normalizedHealth, normalizedHealth, 0.05f, g.config.visuals.esp.health_color[3]);
                                    } else {
                                        col = float4toimcolor(g.config.visuals.esp.health_color);
                                    }
                                    col.Value.w = ImClamp<float>(col.Value.w - alphaFactor, 0.f, 1.f);

                                    g.renderer.imgui->progressBar(
                                        this->m_pDrawlist,
                                        rect.Min - ImVec2(8.f, 0.f),
                                        ImVec2(rect.Min.x - 5.f, rect.Max.y), 
                                        col, 
                                        (float)maxHealth, 
                                        (float)health
                                    );
                                }

                                if(g.config.visuals.esp.skeleton) {
                                    if(player->getBone((bip)(bip_max_tps - 1)) != NULL) {
                                        ImColor col = float4toimcolor(g.config.visuals.esp.skeleton_color);
                                        col.Value.w = ImClamp<float>(col.Value.w - alphaFactor, 0.f, 1.f);

                                        const vec3_t vecHeadC   = C_Camera::w2s(player->getBone(bip_head)->getPosition());
                                        const vec3_t vecNeckC   = C_Camera::w2s(player->getBone(bip_neck)->getPosition());

                                        const vec3_t vecSpineC = C_Camera::w2s(player->getBone(bip_spine)->getPosition());
                                        const vec3_t vecSpine1C = C_Camera::w2s(player->getBone(bip_spine1)->getPosition());
                                        const vec3_t vecSpine2C = C_Camera::w2s(player->getBone(bip_spine2)->getPosition());

                                        const vec3_t vecLShC    = C_Camera::w2s(player->getBone(bip_left_shoulder)->getPosition());
                                        const vec3_t vecLUaC    = C_Camera::w2s(player->getBone(bip_left_upperarm)->getPosition());
                                        const vec3_t vecLHandC  = C_Camera::w2s(player->getBone(bip_left_hand)->getPosition());

                                        const vec3_t vecRShC    = C_Camera::w2s(player->getBone(bip_right_shoulder)->getPosition());
                                        const vec3_t vecRUaC    = C_Camera::w2s(player->getBone(bip_right_upperarm)->getPosition());
                                        const vec3_t vecRHandC  = C_Camera::w2s(player->getBone(bip_right_hand)->getPosition());

                                        const vec3_t vecHipC    = C_Camera::w2s(player->getBone(bip_hip)->getPosition());

                                        const vec3_t vecLThC    = C_Camera::w2s(player->getBone(bip_left_up_leg)->getPosition());
                                        const vec3_t vecLCalfC  = C_Camera::w2s(player->getBone(bip_left_leg)->getPosition());
                                        const vec3_t vecLFootC  = C_Camera::w2s(player->getBone(bip_left_foot)->getPosition());

                                        const vec3_t vecRThC    = C_Camera::w2s(player->getBone(bip_right_up_leg)->getPosition());
                                        const vec3_t vecRCalfC  = C_Camera::w2s(player->getBone(bip_right_leg)->getPosition());
                                        const vec3_t vecRFootC  = C_Camera::w2s(player->getBone(bip_right_foot)->getPosition());

                                        if(vecHeadC.z > 0 && vecRFootC.z > 0 && vecLFootC.z > 0 && vecSpine1C.z > 0) {
                                            this->m_pDrawlist->AddLine(ImVec2(vecHeadC.x, vecHeadC.y), ImVec2(vecNeckC.x, vecNeckC.y), col, 1.f);
                                            this->m_pDrawlist->AddLine(ImVec2(vecNeckC.x, vecNeckC.y), ImVec2(vecSpine2C.x, vecSpine2C.y), col, 1.f);
                                            this->m_pDrawlist->AddLine(ImVec2(vecSpine2C.x, vecSpine2C.y), ImVec2(vecSpine1C.x, vecSpine1C.y), col, 1.f);
                                            this->m_pDrawlist->AddLine(ImVec2(vecSpine1C.x, vecSpine1C.y), ImVec2(vecSpineC.x, vecSpineC.y), col, 1.f);
                                            this->m_pDrawlist->AddLine(ImVec2(vecSpineC.x, vecSpineC.y), ImVec2(vecHipC.x, vecHipC.y), col, 1.f);
                                            //left arm
                                            this->m_pDrawlist->AddLine(ImVec2(vecSpine2C.x, vecSpine2C.y), ImVec2(vecLShC.x, vecLShC.y), col, 1.f);
                                            this->m_pDrawlist->AddLine(ImVec2(vecLShC.x, vecLShC.y), ImVec2(vecLUaC.x, vecLUaC.y), col, 1.f);
                                            this->m_pDrawlist->AddLine(ImVec2(vecLUaC.x, vecLUaC.y), ImVec2(vecLHandC.x, vecLHandC.y), col, 1.f);
                                            //right arm
                                            this->m_pDrawlist->AddLine(ImVec2(vecSpine2C.x, vecSpine2C.y), ImVec2(vecRShC.x, vecRShC.y), col, 1.f);
                                            this->m_pDrawlist->AddLine(ImVec2(vecRShC.x, vecRShC.y), ImVec2(vecRUaC.x, vecRUaC.y), col, 1.f);
                                            this->m_pDrawlist->AddLine(ImVec2(vecRUaC.x, vecRUaC.y), ImVec2(vecRHandC.x, vecRHandC.y), col, 1.f);
                                            //left leg
                                            this->m_pDrawlist->AddLine(ImVec2(vecHipC.x, vecHipC.y), ImVec2(vecLThC.x, vecLThC.y), col, 1.f);
                                            this->m_pDrawlist->AddLine(ImVec2(vecLThC.x, vecLThC.y), ImVec2(vecLCalfC.x, vecLCalfC.y), col, 1.f);
                                            this->m_pDrawlist->AddLine(ImVec2(vecLCalfC.x, vecLCalfC.y), ImVec2(vecLFootC.x, vecLFootC.y), col, 1.f);
                                            //right leg
                                            this->m_pDrawlist->AddLine(ImVec2(vecHipC.x, vecHipC.y), ImVec2(vecRThC.x, vecRThC.y), col, 1.f);
                                            this->m_pDrawlist->AddLine(ImVec2(vecRThC.x, vecRThC.y), ImVec2(vecRCalfC.x, vecRCalfC.y), col, 1.f);
                                            this->m_pDrawlist->AddLine(ImVec2(vecRCalfC.x, vecRCalfC.y), ImVec2(vecRFootC.x, vecRFootC.y), col, 1.f);
                                        }
                                    }
                                }

                                if(g.config.visuals.esp.skeleton_hit) {
                                    
                                }

                                if(g.config.visuals.esp.nick) {
                                    if(player->m_photon->m_sNameField != NULL) {
                                        ImGui::PushFont(g.renderer.imgui->m_fonts.esp.tahoma);

                                        ImColor col = float4toimcolor(g.config.visuals.esp.nick_color);
                                        col.Value.w = ImClamp<float>(col.Value.w - alphaFactor, 0.f, 1.f);

                                        const std::string nick = player->m_photon->m_sNameField->toUTF8();
                                        const ImVec2 vecLabelSize = ImGui::CalcTextSize(nick.c_str());
                                        
                                        g.renderer.imgui->text(
                                            this->m_pDrawlist, 
                                            ImVec2{
                                                (rect.Max.x - ((rect.Max.x - rect.Min.x) / 2)) - (vecLabelSize.x / 2), 
                                                vecHeadCoords.y - (vecLabelSize.y + 2.f)
                                            }, 
                                            col, 
                                            nick.c_str()
                                        );

                                        ImGui::PopFont();
                                    }
                                }

                                if(g.config.visuals.esp.weapon) {
                                    ImColor col = float4toimcolor(g.config.visuals.esp.weapon_color);
                                    col.Value.w = ImClamp<float>(col.Value.w - alphaFactor, 0.f, 1.f);

                                    const CWeaponController* currentWeapon = player->getCurrentWeapon();
                                    if(currentWeapon != NULL) {

                                        uint8_t text_pad = 2;
                                        uint8_t icon_pad = 2;
                                        
                                        if(g.config.visuals.esp.ammo) {
                                            if(player->isHoldingGun()) {
                                                text_pad += 9;
                                                icon_pad += 9;
                                            }
                                        }

                                        if(g.config.visuals.esp.weapons[0]) {
                                            ImGui::PushFont(g.renderer.imgui->m_fonts.esp.verdana_bold);

                                            const std::string name = currentWeapon->getName();
                                            const ImVec2 vecLabelSize = ImGui::CalcTextSize(name.c_str());

                                            icon_pad += vecLabelSize.y;

                                            g.renderer.imgui->text(
                                                this->m_pDrawlist, 
                                                ImVec2{
                                                    (rect.Max.x - ((rect.Max.x - rect.Min.x) / 2)) - (vecLabelSize.x / 2), 
                                                    vecCoords.y + text_pad
                                                }, 
                                                col, 
                                                name.c_str()
                                            );
                                            
                                            ImGui::PopFont();
                                        }
                                        if(g.config.visuals.esp.weapons[1]) {
                                            ImGui::PushFont(g.renderer.imgui->m_fonts.esp.undefeated);

                                            const char icon[2] = {currentWeapon->getIcon(), '\0'};
                                            const ImVec2 vecLabelSize = ImGui::CalcTextSize(icon);

                                            g.renderer.imgui->text(
                                                this->m_pDrawlist, 
                                                ImVec2{
                                                    (rect.Max.x - ((rect.Max.x - rect.Min.x) / 2)) - (vecLabelSize.x / 2), 
                                                    vecCoords.y + icon_pad
                                                }, 
                                                col, 
                                                icon
                                            );
                                            
                                            ImGui::PopFont();
                                        }
                                    }
                                }

                                if(g.config.visuals.esp.ammo) {
                                    if(player->isHoldingGun()) {
                                        ImColor col = float4toimcolor(g.config.visuals.esp.ammo_color);
                                        col.Value.w = ImClamp<float>(col.Value.w - alphaFactor, 0.f, 1.f);
                                        
                                        const CGunController* currentWeapon = (CGunController*)player->getCurrentWeapon();
                                        const CGunParameters* pars = currentWeapon->m_parameters;
                                        if(pars != NULL) {
                                            if(pars->m_ammunition != NULL) {
                                                const int16_t maxAmmo = pars->m_ammunition->m_iMagazineCapacity;
                                                const int32_t currentAmmo = currentWeapon->m_iMagazineCapacitySafe.getValue(true);

                                                char szAmmo[16]{};
                                                snprintf(szAmmo, sizeof(szAmmo), "%d", currentAmmo);
                                                
                                                g.renderer.imgui->progressBar(
                                                    this->m_pDrawlist, 
                                                    ImVec2{rect.Min.x, rect.Max.y + 5.f},
                                                    ImVec2{rect.Max.x, rect.Max.y + 8.f}, 
                                                    col, 
                                                    maxAmmo, 
                                                    currentAmmo, 
                                                    true, 
                                                    true
                                                );

                                            }
                                        }
                                    }
                                }

                                if(g.config.visuals.esp.flags) {
                                    ImColor col = float4toimcolor(g.config.visuals.esp.flags_color);
                                    col.Value.w = ImClamp<float>(col.Value.w - alphaFactor, 0.f, 1.f);

                                    ImGui::PushFont(g.renderer.imgui->m_fonts.esp.verdana_bold_small);

                                    uint8_t     totalFlags{};
                                    const float flagHeight = ImGui::CalcTextSize("S").y;

                                    //armor
                                    if(g.config.visuals.esp.flags_a[0]) {
                                        char armor[3]{};
                                        const int32_t nArmor = player->m_photon->getArmor();
                                        const bool hasHelmet = player->m_photon->getHasHelmet();

                                        const uint8_t kevlarIndex = (hasHelmet ? 1 : 0);

                                        if(hasHelmet)
                                            armor[0] = 'H';
                                        if(nArmor > 15) {
                                            armor[kevlarIndex] = 'K';
                                        }

                                        armor[kevlarIndex + 1] = '\0';

                                        if(armor[0] != NULL) {

                                            g.renderer.imgui->text(
                                                this->m_pDrawlist,
                                                ImVec2{
                                                    rect.Max.x + 5, rect.Min.y
                                                },
                                                col,
                                                armor,
                                                false,
                                                true
                                            );

                                            ++totalFlags;
                                        }
                                    }
                                    //bomb/kits
                                    if(g.config.visuals.esp.flags_a[1]) {
                                        bool bomb_kits{};
                                        if(team == team_tr) {
                                            bomb_kits = player->hasWeapon(weapon_id_bomb);
                                        } else {
                                            bomb_kits = player->m_weaponry->m_kit != NULL;
                                        }
                                        if(bomb_kits) {
                                            
                                            g.renderer.imgui->text(
                                                this->m_pDrawlist,
                                                ImVec2{
                                                    rect.Max.x + 5, rect.Min.y + (flagHeight * totalFlags)
                                                },
                                                col,
                                                (team == team_tr ? oxorany("BOMB") : oxorany("KIT")),
                                                false,
                                                true
                                            );

                                            ++totalFlags;
                                        }
                                    }
                                    //scope
                                    if(g.config.visuals.esp.flags_a[2]) {
                                        if(player->isScoped()) {

                                            g.renderer.imgui->text(
                                                this->m_pDrawlist,
                                                ImVec2{
                                                    rect.Max.x + 5, rect.Min.y + (flagHeight * totalFlags)
                                                },
                                                col,
                                                oxorany("SCOPE"),
                                                false,
                                                true
                                            );

                                            ++totalFlags;
                                        }
                                    }
                                    //reload
                                    if(g.config.visuals.esp.flags_a[3]) {
                                        if(player->isReloading()) {

                                            g.renderer.imgui->text(
                                                this->m_pDrawlist,
                                                ImVec2{
                                                    rect.Max.x + 5, rect.Min.y + (flagHeight * totalFlags)
                                                },
                                                col,
                                                oxorany("RELOAD"),
                                                false,
                                                true
                                            );

                                            ++totalFlags;
                                        }
                                    }
                                    //plant/defusing
                                    if(g.config.visuals.esp.flags_a[4]) {
                                        bool plant_defuse{};
                                        if(team == team_tr) {
                                            plant_defuse = player->isPlanting();
                                        } else {
                                            plant_defuse = player->isDefusing();
                                        }
                                        if(plant_defuse) {

                                            g.renderer.imgui->text(
                                                this->m_pDrawlist,
                                                ImVec2{
                                                    rect.Max.x + 5, rect.Min.y + (flagHeight * totalFlags)
                                                },
                                                col,
                                                (team == team_tr ? oxorany("PLANT") : oxorany("DEFUSE")),
                                                false,
                                                true
                                            );

                                            ++totalFlags;
                                        }
                                    }
                                    ImGui::PopFont();
                                }

                            }
                        }
                    }
                } 
            }
        }
    }
}

void C_ESP::droppedWeapons() noexcept {
    if(g.config.visuals.esp.dropped_weapon) {
        if(this->m_droppedWeapons != NULL) {
            if(this->m_droppedWeapons->isValid()) {
                for(uint32_t i=0;i<this->m_droppedWeapons->getSize();++i) {
                    const CWeaponDropController* weapon = this->m_droppedWeapons->get(i).m_value;
                    if(weapon != NULL) {
                        if(weapon->getGameObject() != NULL && weapon->m_transform != NULL && weapon->m_parameters != NULL) {
                            if(weapon->getGameObject()->getIsActive()) {
                                const vec3_t vecOrigin = weapon->m_transform->getPosition();
                                const vec3_t vecCoords = C_Camera::w2s(vecOrigin);
                                if(vecCoords.z > 0) {
                                    const float alphaFactor = this->getAlphaFactor(vecOrigin, 5.f);
                                    ImColor col = float4toimcolor(g.config.visuals.esp.dropped_weapon_color);
                                    col.Value.w = ImClamp<float>(col.Value.w - alphaFactor, 0.f, 1.f);
                                    
                                    ImGui::PushFont(g.renderer.imgui->m_fonts.esp.undefeated_bigger);

                                    const char icon[2]{weapon->m_parameters->getIcon(), '\0'};
                                    const ImVec2 vecIconSize = ImGui::CalcTextSize(icon);

                                    g.renderer.imgui->text(
                                        this->m_pDrawlist,
                                        ImVec2{
                                            vecCoords.x - (vecIconSize.x / 2),
                                            vecCoords.y - vecIconSize.y,
                                        },
                                        col,
                                        icon
                                    );

                                    ImGui::PopFont();
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

//need to add timer
void C_ESP::droppedGrenades() noexcept {
    if(g.config.visuals.esp.dropped_grenade) {
        if(this->m_droppedGrenades != NULL) {
            if(this->m_droppedGrenades->isValid()) {
                for(uint32_t i=0;i<this->m_droppedGrenades->getSize();++i) {
                    const CDroppedGrenadeController* grenade = this->m_droppedGrenades->get(i).m_value;
                    if(grenade != NULL) {
                        if(grenade->getGameObject() != NULL && grenade->m_transform != NULL && grenade->m_parameters != NULL) {
                            if(grenade->getGameObject()->getIsActive()) {
                                const vec3_t vecOrigin = grenade->m_transform->getPosition();
                                const vec3_t vecCoords = C_Camera::w2s(vecOrigin);
                                if(vecCoords.z > 0) {
                                    const float alphaFactor = this->getAlphaFactor(vecOrigin, 5.f);
                                    ImColor col = float4toimcolor(g.config.visuals.esp.dropped_grenade_color);
                                    col.Value.w = ImClamp<float>(col.Value.w - alphaFactor, 0.f, 1.f);
                                    
                                    ImGui::PushFont(g.renderer.imgui->m_fonts.esp.undefeated_bigger);

                                    const char icon[2]{grenade->m_parameters->getIcon(), '\0'};
                                    const ImVec2 vecIconSize = ImGui::CalcTextSize(icon);

                                    g.renderer.imgui->text(
                                        this->m_pDrawlist,
                                        ImVec2{
                                            vecCoords.x - (vecIconSize.x / 2),
                                            vecCoords.y - vecIconSize.y,
                                        },
                                        col,
                                        icon
                                    );

                                    ImGui::PopFont();
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

//need to add timer
void C_ESP::bomb() noexcept {
    if(g.config.visuals.esp.bomb) {
        if(this->m_pPlantedBomb != NULL) {
            if(this->m_pPlantedBomb->m_transform != NULL) {
                const vec3_t vecOrigin = this->m_pPlantedBomb->m_transform->getPosition();
                const vec3_t vecCoords = C_Camera::w2s(vecOrigin);
                if(vecCoords.z > 0) {
                    const float alphaFactor = this->getAlphaFactor(vecOrigin, 1.f);
                    ImColor col = (this->m_pPlantedBomb->m_bIsDefused ? ImColor(0.5f, 1.f, 0.58f) : float4toimcolor(g.config.visuals.esp.bomb_color));
                    col.Value.w = ImClamp<float>(col.Value.w - alphaFactor, 0.f, 1.f);

                    ImGui::PushFont(g.renderer.imgui->m_fonts.esp.undefeated_bigger);

                    const char icon[2]{'o','\0'};
                    const ImVec2 vecIconSize = ImGui::CalcTextSize(icon);

                    g.renderer.imgui->text(
                        this->m_pDrawlist,
                        ImVec2{
                            vecCoords.x - (vecIconSize.x / 2),
                            vecCoords.y - vecIconSize.y
                        },
                        col,
                        icon
                    );

                    ImGui::PopFont();
                }
            }
        }
    }
}