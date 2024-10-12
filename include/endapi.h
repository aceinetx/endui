#if !defined(ENDAPI_H)
#define ENDAPI_H

#include <ncurses.h>
#include <window.h>

typedef void (*ewh_add_t)(EWH *w);

#ifndef ENDUI_IMPL
extern ewh_add_t ewh_add;
extern WINDOW *endui_scr;
#endif

typedef struct {
  ewh_add_t ewh_add_f;
  WINDOW *endui_scr;
} api_symbols;

#endif  // ENDAPI_H
