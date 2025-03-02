#include "c_chams.hpp"
#include "../globals.hpp"

void C_Chams::update() noexcept {
    C_Chams* const& thiz = g.sn0w.chams;
    if(g.vars.isInGame()) {
        if(thiz->m_shaders[chams_material_solid] == NULL)    thiz->m_shaders[chams_material_solid]    = CShader::find(oxorany("Legacy Shaders/Diffuse"));
        if(thiz->m_shaders[chams_material_glow] == NULL)     thiz->m_shaders[chams_material_glow]     = CShader::find(oxorany("Standard"));
        if(thiz->m_shaders[chams_material_flat] == NULL)     thiz->m_shaders[chams_material_flat]     = CShader::find(oxorany("Hidden/Internal-Colored"));
        if(thiz->m_shaders[chams_material_glass] == NULL)    thiz->m_shaders[chams_material_glass]    = CShader::find(oxorany("Standard"));
    } else {
        thiz->m_shaders[chams_material_solid] = NULL;
        thiz->m_shaders[chams_material_glow] = NULL;
        thiz->m_shaders[chams_material_flat] = NULL;
        thiz->m_shaders[chams_material_glass] = NULL;
    }
    if(thiz->m_shaders[0] != NULL && thiz->m_shaders[1] != NULL && thiz->m_shaders[2] != NULL && thiz->m_shaders[3] != NULL) {
        thiz->players();
        thiz->localplayer();
        thiz->localWeapon();
        thiz->arms();
    }
}

void C_Chams::applyMaterial(const chams_material& material, CRenderer* const& renderer) noexcept {
    CMaterial* pMaterial = renderer->getMaterial();
    pMaterial->setShader(this->m_shaders[material]);
    switch(material) {
        case chams_material_solid: {
            break;
        }
        case chams_material_glow: {
            pMaterial->setFloat(5.f, oxorany("_Metallic"));
            pMaterial->setFloat(5.f, oxorany("_Glossiness"));
            break;
        }
        case chams_material_flat: {
            break;
        }
        case chams_material_glass: {
            pMaterial->setFloat(1.5f, oxorany("_SrcBlend"));
            pMaterial->setFloat(2.f, oxorany("_DstBlend"));
            pMaterial->setFloat(0.5f, oxorany("_Metallic"));
            pMaterial->setFloat(2.f, oxorany("_Glossiness"));
            break;
        }
        default: {
            break;
        }
    }
    renderer->setMaterial(pMaterial);
}

void C_Chams::init() noexcept {
    //тут должен бандл грузиться с шейдерами но он пропадает из за гарбаж колектора я ебу
}

void C_Chams::players() noexcept {
    if(!g.vars.isInGame())
        return;
    if(g.vars.players.isEmpty())
        return;
    
    if(g.config.visuals.chams.enemy || g.config.visuals.chams.teammate) {
        color_t enemyColor = float4tocolor(g.config.visuals.chams.enemy_color);
        color_t teamColor = float4tocolor(g.config.visuals.chams.teammate_color);
        const chams_material& enemyMat = (chams_material)g.config.visuals.chams.enemy_mat;
        const chams_material& teamMat = (chams_material)g.config.visuals.chams.teammate_mat;
        for(uint8_t i=0;i<g.vars.players.getSize();++i) {
            CPlayerController* player = g.vars.players[i];
            if(player == NULL)
                continue;
            if(!player->isAlive())
                continue;
            C_CharacterLODGroup* lod = player->m_characterLODGroup;
            if(lod == NULL)
                continue;
            array_t<CRenderer*>* renderers = lod->m_aMeshRenderers;
            if(renderers == NULL)
                continue;
            if(!renderers->isValid())
                continue;
            
            for(uint32_t r=0;r<renderers->m_iCapacity;++r) {
                CRenderer* renderer = renderers->get(r);
                if(renderer == NULL)
                    continue;
                CMaterial* material = renderer->getMaterial();
                if(material == NULL)
                    continue;
                
                bool isEnemy{};
                bool isTeammate{};
                if(g.config.visuals.chams.enemy) {
                    if(player->m_photon->getTeam() != g.vars.players.m_localPhoton->getTeam()) {
                        isEnemy = true;
                    }
                }
                if(g.config.visuals.chams.teammate) {
                    if(player->m_photon->getTeam() == g.vars.players.m_localPhoton->getTeam()) {
                        isTeammate = true;
                    }
                }

                if(isEnemy || isTeammate) {
                    const chams_material& currentMat = (isEnemy ? enemyMat : teamMat);
                    color_t& currentColor = (isEnemy ? enemyColor : teamColor);
                    if(currentMat == chams_material_glow) {
                        currentColor.r *= 0.1f;
                        currentColor.g *= 0.1f;
                        currentColor.b *= 0.1f;
                    }

                    if(material->getMainTexture() != NULL)
                        material->setMainTexture(NULL);

                    if(material->getShader() != this->m_shaders[currentMat]) {
                        this->applyMaterial(currentMat, renderer);
                    }

                    material->setColor(currentColor);
                }

            }
        }
    }
}

void C_Chams::localplayer() noexcept {
    if(g.config.visuals.chams.local) {
        CLocalPlayer* local = g.vars.players.m_local;
        if(local == NULL)
            return;
        if(!local->isAlive())
            return;

        C_CharacterLODGroup* lod = local->m_characterLODGroup;
        if(lod == NULL)
            return;

        array_t<CRenderer*>* renderers = lod->m_aMeshRenderers;
        if(renderers == NULL)
            return;
        if(!renderers->isValid())
            return;

        const chams_material& currentMat = (chams_material)g.config.visuals.chams.local_mat;
        color_t currentColor = float4tocolor(g.config.visuals.chams.local_color);
        if(currentMat == chams_material_glow) {
            currentColor.r *= 0.1f;
            currentColor.g *= 0.1f;
            currentColor.b *= 0.1f;
        }
        
        for(uint32_t r=0;r<renderers->m_iCapacity;++r) {
            CRenderer* renderer = renderers->get(r);
            if(renderer == NULL)
                continue;
            CMaterial* material = renderer->getMaterial();
            if(material == NULL)
                continue;

            if(material->getMainTexture() != NULL)
                material->setMainTexture(NULL);

            if(material->getShader() != this->m_shaders[currentMat]) {
                this->applyMaterial(currentMat, renderer);
            }

            material->setColor(currentColor);
        }
    }
}

void C_Chams::localWeapon() noexcept {
    static chams_material prevMaterial{};
    static weapon_id prevID{};
    if(g.config.visuals.chams.weapon && !g.config.misc.general.removals[6]) {
        CLocalPlayer* local = g.vars.players.m_local;

        if(local == NULL)
            return;
        if(!local->isAlive())
            return;

        CWeaponController* curWeapon = local->getCurrentWeapon();
        if(curWeapon == NULL)
            return;

        const weapon_id& curID = curWeapon->m_parameters->m_id;

        CWeaponLodGroup* lod = curWeapon->m_LODGroup;
        if(lod == NULL)
            return;
        
        array_t<CRenderer*>* renderers = lod->m_aMeshRenderers;
        if(renderers == NULL)
            return;

        if(!renderers->isValid())
            return;

        const chams_material& curMaterial = (chams_material)g.config.visuals.chams.weapon_mat;
        const CShader* curShader = this->m_shaders[g.config.visuals.chams.weapon_mat];
        color_t color = float4tocolor(g.config.visuals.chams.weapon_color);
        if(curMaterial == chams_material_glow) {
            color.r *= 0.1f;
            color.g *= 0.1f;
            color.b *= 0.1f;
        }
        
        for(uint32_t i=0;i<renderers->m_iCapacity;++i) {
            CRenderer* renderer = renderers->get(i);
            if(renderer == NULL)
                continue;

            CMaterial* material = renderer->getMaterial();
            if(material == NULL)
                continue;

            if(material->getMainTexture() != NULL) {
                material->setMainTexture(NULL);
            }

            if((prevID != curID) || (prevMaterial != curMaterial)) {
                this->applyMaterial(curMaterial, renderer);
            }

            material->setColor(color);
        }

        prevID = curID;
        prevMaterial = curMaterial;
    }
}

void C_Chams::arms() noexcept {
    if((g.config.visuals.chams.arms || g.config.visuals.chams.gloves) && !g.config.misc.general.removals[5]) {
        CLocalPlayer* local = g.vars.players.m_local;
        if(local == NULL)
            return;
        if(!local->isAlive())
            return;

        CArmsLodGroup* lod = local->m_armsLODGroup;
        if(lod == NULL)
            return;

        CRenderer* gloves = lod->m_glovesMeshRenderer;
        CRenderer* arms = lod->m_armsMeshRenderer;
        if(gloves == NULL || arms == NULL)
            return;

        CMaterial* glovesMaterial = gloves->getMaterial();
        CMaterial* armsMaterial = arms->getMaterial();
        if(glovesMaterial == NULL || armsMaterial == NULL)
            return;
        
        const chams_material& glovesMat = (chams_material)g.config.visuals.chams.gloves_mat;
        const chams_material& armsMat = (chams_material)g.config.visuals.chams.arms_mat;
        color_t glovesColor = float4tocolor(g.config.visuals.chams.gloves_color);
        color_t armsColor = float4tocolor(g.config.visuals.chams.arms_color);
        if(glovesMat == chams_material_glow) {
            glovesColor.r *= 0.1f;
            glovesColor.g *= 0.1f;
            glovesColor.b *= 0.1f;
        }
        if(armsMat == chams_material_glow) {
            armsColor.r *= 0.1f;
            armsColor.g *= 0.1f;
            armsColor.b *= 0.1f;
        }

        if(g.config.visuals.chams.gloves) {
            if(glovesMaterial->getMainTexture() != NULL)
                glovesMaterial->setMainTexture(NULL);
            if(glovesMaterial->getShader() != this->m_shaders[glovesMat]) {
                this->applyMaterial(glovesMat, gloves);
            }
            glovesMaterial->setColor(glovesColor);
        }
        if(g.config.visuals.chams.arms) {
            if(armsMaterial->getMainTexture() != NULL)
                armsMaterial->setMainTexture(NULL);
            if(armsMaterial->getShader() != this->m_shaders[armsMat]) {
                this->applyMaterial(armsMat, arms);
            }
            armsMaterial->setColor(armsColor);
        }
    }
}