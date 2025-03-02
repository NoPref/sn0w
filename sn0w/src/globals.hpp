#pragma once
#include <jni.h>
#include "../includes/include.h"
#include "sdk/include.h"
#include "config.hpp"
#include "hooking.hpp"
#include "offsets.hpp"
#include "singleton.hpp"
#include "features/c_cheat_manager.hpp"
#include "render/c_renderer.hpp"
#include "ui/c_user_interface.hpp"
#include "protection/hide_imports.hpp"

struct globals_t {
    JNIEnv*            jenv{};
    void*              hIl2Cpp{};
    void*              hEngine{};
    unsigned long long lpBase{};
    unsigned long long lpEngineBase{};
    resolution_t       screen{};
    resolution_t       window{};
    
    CHideImports*      hi{};
    il2cpp_api_t       il2cpp{};
    offsets_t          offsets{};
    hooks_t            hooks{};
    config_t           config{};
    CGameVars          vars{};
    C_CallbackManager  callbacks{};
    CGlobalRenderer    renderer{};
    C_CheatManager     sn0w{};

    void entry();
    void libUnityEntry();
    void libil2cppEntry();
    void gameEntry();
};

extern globals_t g;