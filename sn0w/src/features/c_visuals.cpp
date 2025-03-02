#include "c_visuals.hpp"
#include "../globals.hpp"

void CVisuals::bulletTracers() noexcept {
    static bool reset{};
    static int32_t shotID{};
    static uint8_t index{};

    if(g.vars.mainCamera == NULL) {
        memset(this->m_aBulletTracers, 0, sizeof(this->m_aBulletTracers));
        return;
    }

    if(index >= 30)
        index = 0;
    if(g.config.visuals.world.render.bullet_tracer) {
        reset = true;
        CLocalPlayer* local = g.vars.players.m_local;
        if(local == NULL)
            return;

        if(!local->isAlive())
            return;

        const CGunController* gun = (CGunController*)local->getCurrentWeapon();
        if(gun == NULL)
            return;
        
        int32_t currentShotID = gun->m_iShotID;
        if(shotID != currentShotID) {
            if(!local->isCanShoot()) {
                shotID = currentShotID;
                return;
            }

            const list_t<CShootEventData*>* events = gun->m_lShotBuffer;
            if(events == NULL)
                return;
            if(!events->isValid())
                return;

            static CShootEventData* lastData{};
            for(uint32_t i=0;i<events->getSize();++i) {
                if(events->get(i) != NULL) {
                    lastData = events->get(i);
                }
            }
            if(lastData == NULL)
                return;

            const array_t<CSingleShotData*>* shoots = lastData->m_aShots;
            if(shoots == NULL)
                return;
            if(!shoots->isValid())
                return;
                
            const CSingleShotData* current = shoots->get(0);
            if(current == NULL)
                return;
            
            this->m_aBulletTracers[index] = visuals::bullet_hit_t(current->m_vecStartPoint, current->m_vecEndPoint);
            ++index;
            shotID = currentShotID;
        }
    } else {
        if(reset) {
            memset(this->m_aBulletTracers, 0, sizeof(this->m_aBulletTracers));
            reset = false;
        }
    }
}

void CVisuals::bulletTracersR() noexcept {
    if(g.config.visuals.world.render.bullet_tracer) {
        for(uint8_t i=0;i<(sizeof(this->m_aBulletTracers)/sizeof(this->m_aBulletTracers[0]));++i) {
            visuals::bullet_hit_t& hit = this->m_aBulletTracers[i];
            if(hit.m_fLocalTime > 0) {
                const vec3_t vecSrc = C_Camera::w2s_clamped(hit.m_vecSrc);
                const vec3_t vecDst = C_Camera::w2s_clamped(hit.m_vecDst);

                ImColor color = float4toimcolor(g.config.visuals.world.render.bullet_tracer_color);
                color.Value.w -= (visuals::bullet_hit_t::maxTime - hit.m_fLocalTime);
                
                g.renderer.imgui->line(g.sn0w.esp->m_pDrawlist, ImVec2(vecSrc.x, vecSrc.y), ImVec2(vecDst.x, vecDst.y), color, 1.f);

                hit.m_fLocalTime -= ImGui::GetIO().DeltaTime;
            }
        }
    }
}

void CVisuals::hitmarkers() noexcept {
    static bool reset{};
    static int32_t shotID{};
    static uint8_t index{};

    if(g.vars.mainCamera == NULL) {
        memset(this->m_aHits, 0, sizeof(this->m_aHits));
        return;
    }
    
    if(index >= 30)
        index = 0;
    if(g.config.visuals.world.render.hit_marker) {
        reset = true;
        CLocalPlayer* local = g.vars.players.m_local;
        if(local == NULL)
            return;

        if(!local->isAlive())
            return;

        const CGunController* gun = (CGunController*)local->getCurrentWeapon();
        if(gun == NULL)
            return;
        
        int32_t currentShotID = gun->m_iShotID;
        if(shotID != currentShotID) {
            if(!local->isCanShoot()) {
                shotID = currentShotID;
                return;
            }

            const dictionary_t<void*, list_t<CBulletHitData*>*>* hits = gun->m_dCharacterHits;
            if(hits == NULL)
                return;
            if(!hits->isValid())
                return;
            
            static list_t<CBulletHitData*>* lastData{};
            for(uint32_t i=0;i<hits->getSize();++i) {
                if(hits->get(i).m_value != NULL) {
                    lastData = hits->get(i).m_value;
                }
            }
            if(lastData == NULL)
                return;
            if(!lastData->isValid())
                return;

            const CBulletHitData* data = lastData->get(0);
            if(data == NULL)
                return;
            
            this->m_aHits[index] = visuals::player_hit_t(data->m_vecPoint, data->m_iDamage, data->m_bip);

            ++index;
            shotID = currentShotID;
        }
    } else {
        if(reset) {
            memset(this->m_aHits, 0, sizeof(this->m_aHits));
            reset = false;
        }
    }
}

void CVisuals::hitmarkersR() noexcept {
    if(g.config.visuals.world.render.hit_marker) {
        for(uint8_t i=0;i<(sizeof(this->m_aHits)/sizeof(this->m_aHits[0]));++i) {
            visuals::player_hit_t& hit = this->m_aHits[i];
            if(hit.m_fLocalTime > 0) {
                const vec3_t vecHit = C_Camera::w2s(hit.m_vecHit);
                const int32_t& damage = hit.m_iDamage;
                const bip& bone = hit.m_bip;

                char damageStr[16]{};
                snprintf(damageStr, sizeof(damageStr), "%d", damage);

                ImColor color = float4toimcolor(g.config.visuals.world.render.hit_marker_color);
                color.Value.w -= (visuals::player_hit_t::maxTime - hit.m_fLocalTime);
                
                if(vecHit.z > 0) {
                    g.renderer.imgui->line(g.sn0w.esp->m_pDrawlist, ImVec2(vecHit.x - 8,vecHit.y - 8), ImVec2(vecHit.x - 2.f,vecHit.y - 2.f), color, 1.8f);
                    g.renderer.imgui->line(g.sn0w.esp->m_pDrawlist, ImVec2(vecHit.x + 8,vecHit.y - 8), ImVec2(vecHit.x + 2.f,vecHit.y - 2.f), color, 1.8f);
                    g.renderer.imgui->line(g.sn0w.esp->m_pDrawlist, ImVec2(vecHit.x - 8,vecHit.y + 8), ImVec2(vecHit.x - 2.f,vecHit.y + 2.f), color, 1.8f);
                    g.renderer.imgui->line(g.sn0w.esp->m_pDrawlist, ImVec2(vecHit.x + 8,vecHit.y + 8), ImVec2(vecHit.x + 2.f,vecHit.y + 2.f), color, 1.8f);
                    ImGui::PushFont(g.renderer.imgui->m_fonts.esp.verdana_bold);
                    g.renderer.imgui->text(g.sn0w.esp->m_pDrawlist, ImVec2(vecHit.x, (vecHit.y - 20) + (hit.m_fLocalTime * 3)), ImColor(1.f, 1.f, 1.f, color.Value.w), damageStr);
                    ImGui::PopFont();
                }

                hit.m_fLocalTime -= ImGui::GetIO().DeltaTime;
            }
        }
    }
}

void CVisuals::worldColor() noexcept {
    if(g.config.visuals.world.env.world_color && g.config.visuals.world.env.world_color_update) {
        if(g.vars.isInGame()) {
            const color_t color = float4tocolor(g.config.visuals.world.env.world_color_color);

            static type_t* meshType{};
            if(meshType == NULL)
                meshType = type_t::find(oxorany("UnityEngine.MeshRenderer, UnityEngine.CoreModule"));

            CShader* shader = CShader::find(oxorany("Legacy Shaders/Diffuse"));
            if(shader == NULL)
                return;
                
            array_t<CRenderer*>* worldRenderers = (array_t<CRenderer*>*)CObject::findObjectsByType(meshType);
            if(worldRenderers == NULL)
                return;
            if(!worldRenderers->isValid())
                return;
            
            for(uint32_t i=0;i<worldRenderers->m_iCapacity;++i) {
                CRenderer* renderer = worldRenderers->get(i);
                if(renderer == NULL)
                    continue;
                array_t<CMaterial*>* materials = renderer->getMaterials();
                if(materials == NULL)
                    continue;
                if(!materials->isValid())
                    continue;
                
                for(uint32_t m=0;m<materials->m_iCapacity;++m) {
                    CMaterial* material = materials->get(m);
                    if(material == NULL)
                        continue;
                    material->setShader(shader);

                    if(g.config.visuals.world.env.world_color_solid)
                        material->setMainTexture(NULL);

                    material->setColor(color);
                }
                renderer->setMaterials(materials);
            }
        }   
        g.config.visuals.world.env.world_color_update = false;
    }
}

void CVisuals::skyColor() noexcept {
    if(g.config.visuals.world.env.sky_color) {
        if(g.vars.mainCamera != NULL) {
            const color_t color = float4tocolor(g.config.visuals.world.env.sky_color_color);
            g.vars.mainCamera->setFlags(camera_clear_flags_color);
            g.vars.mainCamera->setBackgroundColor(color);
        }
    }
}

//хули эта хуйня не на всех картах работает
void CVisuals::fog() noexcept {
    static void* (*getRenderSettings)(){};
    static void (*useFog)(void*,bool);
    if(getRenderSettings == NULL) {
        getRenderSettings = (decltype(getRenderSettings))(g.lpEngineBase + ofs(engine.get_render_settings));
        useFog = (decltype(useFog))(g.lpEngineBase + ofs(engine.use_fog));
    }
    if(g.config.visuals.world.env.fog) {
        void* pRenderSettings = getRenderSettings();
        if(pRenderSettings != NULL) {
            *(bool*)((unsigned long long)pRenderSettings + ofs(render_settings.fog_enabled)) = true;
            *(float*)((unsigned long long)pRenderSettings + ofs(render_settings.fog_start_distance)) = g.config.visuals.world.env.fog_start;
            *(float*)((unsigned long long)pRenderSettings + ofs(render_settings.fog_end_distance)) = g.config.visuals.world.env.fog_end;
            *(float*)((unsigned long long)pRenderSettings + ofs(render_settings.fog_density)) = g.config.visuals.world.env.fog_density;
            *(color_t*)((unsigned long long)pRenderSettings + ofs(render_settings.fog_color)) = float4tocolor(g.config.visuals.world.env.fog_color);
            *(int*)((unsigned long long)pRenderSettings + ofs(render_settings.fog_mode)) = 1;
            useFog(pRenderSettings, true);
        }
    }
}

void CVisuals::render() noexcept {
    CVisuals* const& thiz = g.sn0w.visuals;
    thiz->bulletTracersR();
    thiz->hitmarkersR();
}

void CVisuals::update() noexcept {
    CVisuals* const& thiz = g.sn0w.visuals;
    thiz->bulletTracers();
    thiz->hitmarkers();
    thiz->worldColor();
    thiz->skyColor();
    //thiz->fog();
}