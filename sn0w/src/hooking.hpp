#pragma once
#include <stdint.h>
#include <jni.h>
#include <dlfcn.h>
#include "sdk/include.h"

struct hooks_t {
    struct orig {
        struct libc {
            void* (*dlsym)(void* handle, const char* symbol);
        } libc;
        struct engine {
            int32_t (*getTouchCount)();
            bool (*rayCast)(void*& scene, ray_t& ray, float maxDistance, raycast_hit_t& hit, int32_t layer, uint8_t trigger);
            void (*onPostRender)();
        } engine;
        struct game {
            void (*lateUpdate)(void* obj);
            void (*createMove)(void* obj, CInputs* pCmd);
            void (*hit)(void* obj, void* hitdata);
        } game;
    } orig;

    struct libc {
        void init();
        static void* dlsym(void* handle, const char* symbol);
    } libc;
    struct engine {
        void init();
        void initRender();
        static void onGUI(void* obj);
        static int32_t getTouchCount();
        static bool rayCast(void*& scene, ray_t& ray, float maxDistance, raycast_hit_t& hit, int32_t layer, uint8_t trigger);
        static void onPostRender();
    } engine;
    struct game {
        CGameObject* __obj;
        void initLateUpdate();
        static void update();
        static void lateUpdate(void* obj);
        static void createMove(void* obj, CInputs* pCmd);
        static void hit(void* obj, void* hitdata);
    } game;
};