#include <apps/endbar.h>
#include <endapi.h>
#include <endfs.h>
#include <hooking.h>
#include <mouse.h>
#include <window.h>

typedef struct {
  int menu_toggle_key;
} settings_t;

settings_t settings;
EWH* settings_window = NULL;

lm_address_t process_keypress_TR;

void process_keypress_H(int key, endui_mouse* mouse, vec_void_t* handles,
                        EWH** drag_window) {
  if (key == settings.menu_toggle_key) {
    main_menu->hidden = !main_menu->hidden;
  }
  ((process_keypress_t)process_keypress_TR)(key, mouse, handles, drag_window);
}

int settings_main(void) {
  settings.menu_toggle_key = 'h';
  settings_window = ewh_new_window(17, 1, 20, 10, "Settings");
  EWH* labelKeybinds = ewh_new_label(1, 2, "Keybinds: ", settings_window);
  EWH* separatorKeybinds = ewh_new_separator(1, 5, 18, settings_window);
  separatorKeybinds->width = separatorKeybinds->parent->width - 2;

  endui_hook(process_keypress, process_keypress_H, &process_keypress_TR);

  settings_window->hidden = true;
  ewh_add(settings_window);
  ewh_add(labelKeybinds);
  ewh_add(separatorKeybinds);
}