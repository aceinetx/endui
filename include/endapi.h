#if !defined(ENDAPI_H)
#define ENDAPI_H

#include <ncurses.h>
#include <window.h>

typedef void (*ewh_add_t)(EWH *w);

#ifndef ENDUI_IMPL
extern WINDOW *endui_scr;
void ewh_add(EWH *w);
#endif

typedef struct {
  WINDOW *endui_scr;
} api_symbols;

#endif  // ENDAPI_H
