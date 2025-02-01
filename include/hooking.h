#if !defined(HOOKING_H)
#define HOOKING_H

#include <dobby.h>
#define addr_t void *
#define endui_hook(from, to, trampoline)                                       \
  DobbyHook((void *)from, (dobby_dummy_func_t)to,                              \
            (dobby_dummy_func_t *)trampoline)

#endif // HOOKING_H
