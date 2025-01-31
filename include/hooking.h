#if !defined(HOOKING_H)
#define HOOKING_H

#if defined(ENDUI_X86)

#include <libmem/libmem.h>

#define endui_hook(from, to, trampoline) LM_HookCode((lm_address_t)from, (lm_address_t)to, (lm_address_t *)trampoline)

#elif defined(ENDUI_ARM)

#error "Hooking not implemented for ARM"

#else

#error "Unknown architecture"

#endif

#endif // HOOKING_H
