#include <endapi.h>
#include <ncurses.h>
#include <window.h>

EWH *bar;
EWH *main_button;
EWH *main_menu;

bool toggle_menu(struct EWH *sender, void *arg) {
  main_menu->hidden = !main_menu->hidden;
  return true;
}

void main(void *sym) {
  bar =
      ewh_new_window(0, getmaxy(endui_scr) - 1, getmaxx(endui_scr), 1, "EndUI");
  bar->flags = EWH_NORESIZE | EWH_NOTITLE;
  ewh_add(bar);

  main_button = ewh_new_button(0, 0, 9, 1, "EndUI", bar);
  main_button->ewh_callback = toggle_menu;
  ewh_add(main_button);

  main_menu = ewh_new_window(0, 0, 10, 10, "Main");
  main_menu->y = getmaxy(endui_scr) - main_menu->height - 1;
  main_menu->flags = EWH_NORESIZE | EWH_NOTITLE;
  main_menu->hidden = true;
  ewh_add(main_menu);
}

void endui_fini() { return; }