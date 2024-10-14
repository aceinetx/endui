#if !defined(HOOKING_H)
#define HOOKING_H

#include <libmem/libmem.h>
#define endui_hook(from, to, trampoline) LM_HookCode((lm_address_t)from, (lm_address_t)to, (lm_address_t *)trampoline)

#endif // HOOKING_H
