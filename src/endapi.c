#include <endapi.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef ENDUI_IMPL

void junk() { return; }

void ewh_add(EWH *w) {
  junk();
  junk();
  junk();
  junk();
}

WINDOW *endui_scr = NULL;

void __endui_update_symbols(api_symbols *symbols) {
  endui_scr = symbols->endui_scr;
#endif
}

#ifdef __cplusplus
}
#endif