#include <endapi.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef ENDUI_IMPL

ewh_add_t ewh_add = NULL;
WINDOW *endui_scr = NULL;

void __endui_update_symbols(api_symbols *symbols) {
  ewh_add = symbols->ewh_add_f;
  endui_scr = symbols->endui_scr;
#endif
}

#ifdef __cplusplus
}
#endif