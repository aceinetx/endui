#include <apps/endbar.h>
#include <endapi.h>
#include <endfs.h>
#include <hooking.h>
#include <mouse.h>
#include <unistd.h>
#include <window.h>

typedef struct {
  int menu_toggle_key;
} settings_t;

settings_t settings;
EWH* settings_window = NULL;

addr_t process_keypress_TR;

void process_keypress_H(int key, endui_mouse* mouse, vec_void_t* handles,
                        EWH** drag_window) {
  if (key == settings.menu_toggle_key) {
    main_menu->hidden = !main_menu->hidden;
  } else {
    ((process_keypress_t)process_keypress_TR)(key, mouse, handles, drag_window);
  }
}

char* settings_to_bin(settings_t* settings) {
  char* bin = malloc(sizeof(*settings));

  memcpy(bin, settings, sizeof(*settings));

  return bin;
}

void bin_to_settings(settings_t* settings, char* bin) {
  memcpy(settings, bin, sizeof(*settings));
}

void save_cfg(settings_t* settings) {
  char* bin = settings_to_bin(settings); /* write default config */
  write_file("./endui.bin", bin);
  free(bin);
}

void load_cfg(settings_t* settings) {
  char* bin = read_file("./endui.bin");
  bin_to_settings(settings, bin);
  free(bin);
}

bool setMenuBindCallback(struct EWH* sender, void* arg) {
  nodelay(endui_scr, FALSE);
  mvwprintw(endui_scr, 0, 0, "Press any key...");
  wrefresh(endui_scr);
  settings.menu_toggle_key = wgetch(endui_scr);
  nodelay(endui_scr, TRUE);

  snprintf(sender->title, WINDOW_TITLE_MAX, "Menu: %c",
           (char)settings.menu_toggle_key);

  save_cfg(&settings);
  return true;
}

int settings_main(void) {
  settings.menu_toggle_key = 'h';

  if (access("./endui.bin", F_OK) == -1) {
    save_cfg(&settings);
  } else {
    load_cfg(&settings);
  }

  settings_window = ewh_new_window(17, 1, 20, 10, "Settings");
  EWH* labelKeybinds = ewh_new_label(1, 2, "Keybinds: ", settings_window);
  EWH* separatorKeybinds = ewh_new_separator(1, 5, 18, settings_window);
  EWH* bindMenuButton = ewh_new_button(1, 3, 9, 1, "Menu: ", settings_window);
  snprintf(bindMenuButton->title, WINDOW_TITLE_MAX, "Menu: %c",
           (char)settings.menu_toggle_key);
  bindMenuButton->ewh_callback = setMenuBindCallback;

  separatorKeybinds->width = separatorKeybinds->parent->width - 2;

  endui_hook(process_keypress, process_keypress_H, &process_keypress_TR);

  settings_window->hidden = true;
  ewh_add(settings_window);
  ewh_add(labelKeybinds);
  ewh_add(separatorKeybinds);
  ewh_add(bindMenuButton);
  return 0;
}
