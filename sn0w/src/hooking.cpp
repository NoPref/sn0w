#include <dlfcn.h>
#include <sys/mman.h>
#include <unistd.h>
#include <android/log.h>
#include "hooking.hpp"
#include "globals.hpp"
#include "utils.hpp"
#include "protection/consts.hpp"
#include "../includes/a64hook/And64InlineHook.hpp"
#include "../includes/oxorany/include.h"
#include "../includes/xdl/include/xdl.h"

void hooks_t::libc::init() {
    __hook_func(g.hi->m_syms[hi_sym_dlsym], &g.hooks.libc.dlsym, &g.hooks.orig.libc.dlsym);
}

//libmain->libunity->libil2cpp->libshared
void* hooks_t::libc::dlsym(void* handle, const char* symbol) {
    void* ret = g.hooks.orig.libc.dlsym(handle, symbol);
    static bool flag{};
	if(!flag) {
		if(ret != NULL) {
			Dl_info info{};
			if(g.hi->dladdr(ret, &info)) {
				if(g.hi->strstr(info.dli_fname, consts::libunity_so())) {
					g.hEngine = handle;
					g.lpEngineBase = (unsigned long long)info.dli_fbase;
                    g.libUnityEntry();
				}
				if(g.hi->strstr(info.dli_fname, consts::libil2cpp_so())) {
					g.hIl2Cpp = handle;
					g.lpBase = (unsigned long long)info.dli_fbase;
                    g.libil2cppEntry();
                    flag = true;
				}
			}
		}
	} 
    return ret;
}

void hooks_t::engine::init() {
    *(void**)(g.lpBase + ofs(engine.touches)) = (void*)&g.hooks.engine.getTouchCount;
    *(void**)(g.lpBase + ofs(engine.raycast)) = (void*)&g.hooks.engine.rayCast;
}

//WindowContextEGL::OnPostPresentContext
void hooks_t::engine::initRender() {
    void* inst = (void*)(g.lpEngineBase + ofs(engine.wnd_ctx));
    void** ptr = (void**)((unsigned long long)inst + ofs(engine.wnd_post_callback));
    g.hooks.orig.engine.onPostRender = (void(*)())*ptr;
    *ptr = (void*)&g.hooks.engine.onPostRender;
}

void hooks_t::engine::onGUI(void* obj) {
    g.callbacks.call(callback_event_gui);
    if(CEvent::getCurrent()->getType() == event_type_repaint)
        g.callbacks.call(callback_event_gui_repaint);
}

int32_t hooks_t::engine::getTouchCount() {
    if(g.hooks.orig.engine.getTouchCount == NULL) {
        g.gameEntry();
        g.hooks.orig.engine.getTouchCount = (int32_t(*)())g.il2cpp.import_from_engine(consts::gettouch());
    }
    g.callbacks.call(callback_event_game_frame);
    return g.hooks.orig.engine.getTouchCount();
}

bool hooks_t::engine::rayCast(void*& scene, ray_t& ray, float maxDistance, raycast_hit_t& hit, int32_t layer, uint8_t trigger) {
    if(g.hooks.orig.engine.rayCast == NULL)
        g.hooks.orig.engine.rayCast = (decltype(g.hooks.orig.engine.rayCast))g.il2cpp.import_from_engine(consts::raycast());
    if(layer == 1610637328) {
        if(g.config.rage.aimbot.enabled && g.config.rage.aimbot.exploits[2] && g.sn0w.rage->m_psInfo.m_bValid) { 
            ray.m_vecDirection = g.sn0w.rage->m_psInfo.m_vecDirection;
        }
    }
    return g.hooks.orig.engine.rayCast(scene, ray, maxDistance, hit, layer, trigger);
}

void hooks_t::engine::onPostRender() {
    g.hooks.orig.engine.onPostRender();

    if(!g.hi->m_bLoaded)
        return;

    static bool rendererInit{};
    if(!rendererInit) {
        g.renderer.imgui->init();
        rendererInit = true;
    }

    g.renderer.imgui->beginFrame();
    g.callbacks.call(callback_event_render);
    g.renderer.imgui->endFrame();
}

void hooks_t::game::update() {
    if(g.vars.pControls != NULL) {
        delegate_t* crMv = *(delegate_t**)((unsigned long long)g.vars.pControls + ofs(player_controls.create_move));
        if(crMv != NULL) {
            crMv->hook((void*)&g.hooks.game.createMove, (void**)&g.hooks.orig.game.createMove);
        }
    }
}

void hooks_t::game::initLateUpdate() {
    MethodInfo* pLateUpdate = g.il2cpp.getMethod(g.il2cpp.getClass(consts::inputfield(), consts::axleboltchat(), consts::assembly_csharp()), consts::lateupdate(), 0);
    void** ptr = (void**)&pLateUpdate->methodPointer;
    g.hooks.orig.game.lateUpdate = (void(*)(void*))*ptr;
    *ptr = (void*)&g.hooks.game.lateUpdate;

    this->__obj = (CGameObject*)g.il2cpp.object_new(g.il2cpp.getClass(consts::gameobject(), consts::unityengine(), consts::unitycoremodule()));
    this->__obj->create(oxorany("_"));
    this->__obj->addComponent(type_t::find(consts::inputfield_type()));
    this->__obj->dontDestroyOnLoad();
}

void hooks_t::game::lateUpdate(void* obj) {
    g.callbacks.call(callback_event_late_update);
    return g.hooks.orig.game.lateUpdate(obj);
}

void hooks_t::game::createMove(void* obj, CInputs* pCmd) {
    if(pCmd != NULL)
        CLocalPlayer::oldCmd = *pCmd;
    CLocalPlayer::pCmd = pCmd;
    g.callbacks.call(callback_event_create_move);
    return g.hooks.orig.game.createMove(obj, pCmd);
}

void hooks_t::game::hit(void* obj, void* hitdata) {
    CLocalPlayer::pHitData = hitdata;
    g.callbacks.call(callback_event_hit);
    return g.hooks.orig.game.hit(obj, hitdata);
}