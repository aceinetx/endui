#if !defined(ENDAPI_H)
#define ENDAPI_H

#include <app_exec_result.h>
#include <fnptr.h>
#include <mouse.h>
#include <ncurses.h>
#include <window.h>

typedef fnptr(void, process_keypress_t, int, endui_mouse *, vec_void_t *,
              EWH **);
typedef fnptr(app_exec_result *, run_app_t, const char *);
typedef fnptr(void, ewh_add_t, EWH *);
typedef fnptr(void, draw_windows_t, vec_void_t *, EWH *, endui_mouse *);
typedef fnptr(char *, get_desktop_id_ptr_t);
typedef fnptr(char, get_max_desktops_t);

#ifndef ENDUI_IMPL
extern WINDOW *endui_scr;
extern process_keypress_t process_keypress;
extern run_app_t runApp;
extern ewh_add_t ewh_add;
extern draw_windows_t draw_windows;
extern get_desktop_id_ptr_t get_desktop_id_ptr;
extern get_max_desktops_t get_max_desktops;
#endif

typedef struct {
  WINDOW *endui_scr;
  process_keypress_t process_keypress;
  run_app_t run_app;
  ewh_add_t ewh_add;
  draw_windows_t draw_windows;
  get_desktop_id_ptr_t get_desktop_id_ptr;
  get_max_desktops_t get_max_desktops;
} api_symbols;

#endif  // ENDAPI_H
