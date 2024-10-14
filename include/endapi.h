#if !defined(ENDAPI_H)
#define ENDAPI_H

#include <fnptr.h>
#include <mouse.h>
#include <ncurses.h>
#include <window.h>

typedef fnptr(void, process_keypress_t, int, endui_mouse *, vec_void_t *,
              EWH **);

#ifndef ENDUI_IMPL
extern WINDOW *endui_scr;
extern process_keypress_t process_keypress;
void ewh_add(EWH *w);
#endif

typedef struct {
  WINDOW *endui_scr;
  process_keypress_t process_keypress;
} api_symbols;

#endif  // ENDAPI_H
