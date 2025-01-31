#if !defined(HOOKING_H)
#define HOOKING_H

#if defined(ENDUI_X86)
#include <libmem/libmem.h>
#define addr_t lm_address_t
#define endui_hook(from, to, trampoline) LM_HookCode((lm_address_t)from, (lm_address_t)to, (lm_address_t *)trampoline)
#endif

#if defined(ENDUI_ARM)
#include <dobby.h>
#define addr_t void*
#define endui_hook(from, to, trampoline) DobbyHook((void*)from, (dobby_dummy_func_t)to, (dobby_dummy_func_t*)trampoline)
#endif

// Check if everything is defined
#ifndef endui_hook
#error "endui_hook not defined, probably unknown architecture"
#endif

#endif // HOOKING_H
