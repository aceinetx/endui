#include <apps/settings.h>
#include <endapi.h>
#include <everything.h>
#include <ncurses.h>
#include <window.h>

EWH *bar = NULL;
EWH *main_button = NULL;
EWH *main_menu = NULL;

bool endbar_toggle_menu(struct EWH *sender, void *arg) {
  main_menu->hidden = !main_menu->hidden;
  return true;
}

bool endbar_toggle_settings(struct EWH *sender, void *arg) {
  settings_window->hidden = !settings_window->hidden;
  return true;
}

void endbar_main() {
  bar =
      ewh_new_window(0, getmaxy(endui_scr) - 1, getmaxx(endui_scr), 1, "EndUI");
  bar->flags = EWH_NORESIZE | EWH_NOTITLE;
  ewh_add(bar);

  main_button = ewh_new_button(0, 0, 9, 1, "EndUI", bar);
  main_button->ewh_callback = endbar_toggle_menu;
  ewh_add(main_button);

  EWH *virtual_desktop_label = ewh_new_label(11, 0, "", bar);
  main_menu = ewh_new_window(0, 0, 15, 10, "Main");
  main_menu->y = getmaxy(endui_scr) - main_menu->height - 1;
  main_menu->flags = EWH_NORESIZE | EWH_NOTITLE;
  main_menu->hidden = true;
  ewh_add(main_menu);

  EWH *settings_button = ewh_new_button(1, 1, 11, 3, "Settings", main_menu);
  settings_button->ewh_callback = endbar_toggle_settings;

  ewh_add(settings_button);
  ewh_add(virtual_desktop_label);

  ewh_title(virtual_desktop_label, "");
  snprintf(virtual_desktop_label->title, WINDOW_TITLE_MAX, "%d/%d",
           *get_desktop_id_ptr(), get_max_desktops());

  while (active) {
    bar->virtual_desktop_id = *get_desktop_id_ptr();
    main_menu->virtual_desktop_id = bar->virtual_desktop_id;
    virtual_desktop_label->title[0] = 48 + (*get_desktop_id_ptr());
  }
}