#include <endapi.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef ENDUI_IMPL

WINDOW *endui_scr = NULL;
process_keypress_t process_keypress = NULL;
run_app_t run_app = NULL;
ewh_add_t ewh_add = NULL;
draw_windows_t draw_windows = NULL;
get_desktop_id_ptr_t get_desktop_id_ptr = NULL;
get_max_desktops_t get_max_desktops;

void __endui_update_symbols(api_symbols *symbols) {
  endui_scr = symbols->endui_scr;
  process_keypress = symbols->process_keypress;
  run_app = symbols->run_app;
  ewh_add = symbols->ewh_add;
  draw_windows = symbols->draw_windows;
  get_desktop_id_ptr = symbols->get_desktop_id_ptr;
  get_max_desktops = symbols->get_max_desktops;
#endif
}

#ifdef __cplusplus
}
#endif