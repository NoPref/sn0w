#include <jni.h>
#include "globals.hpp"

globals_t g{};

void *thread(void *) {
    g.entry();

    pthread_exit(0);
}

__attribute__((constructor))
void init() {
    pthread_t t;
    pthread_create(&t, nullptr, thread, nullptr);
}