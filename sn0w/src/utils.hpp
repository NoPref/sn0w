#pragma once
#include <stdint.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/sysconf.h>
#include "globals.hpp"
#include "../includes/a64hook/And64InlineHook.hpp"
#include "../includes/oxorany/include.h"

#define __page_size (g.hi->sysconf(oxorany(0x28)))

#define __align_addr(addr) ((void*)((size_t)(addr) & ~((__page_size) - 1)))
#define __ro(addr) (g.hi->mprotect(__align_addr((addr)), __page_size, PROT_READ))
#define __rw(addr) (g.hi->mprotect(__align_addr((addr)), __page_size, PROT_READ | PROT_WRITE))
#define __rx(addr) (g.hi->mprotect(__align_addr((addr)), __page_size, PROT_READ | PROT_EXEC))
#define __rwx(addr) (g.hi->mprotect(__align_addr((addr)), __page_size, PROT_READ | PROT_WRITE | PROT_EXEC))

#define __hook_func(addr, hook, orig) A64HookFunction((void*)(addr), (void*)(hook), (void**)(orig)); \
									__rx((addr))