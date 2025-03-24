# Api documentation
## Variables / Functions
```c
EWH* ewh_new() // creates a new handle
EWH *ewh_new_window(int x, int y, int width, int height, const char *title) // creates a new window, autofills the fields of EWH with the arguments
EWH *ewh_new_button(int x, int y, int width, int height, const char *title, EWH *parent) // creates a new button
void ewh_add(EWH* w) // add a window to handles
WINDOW *endui_scr // ncurses stdscr pointer
```
## Hooking
EndUI Supports functions hooking with [yHook](https://github.com/aceinetx/yHook)<br>
You can hook all functions you can find in libendui.so<br>
#### Functions you can hook
- process_keypress
- run_app
- ewh_add
- draw_windows
- get_desktop_id_ptr
- get_max_desktops
```c
#include <hooking.h>
#include <mouse.h>
#include <window.h>

yHook_t pkh; // our hook

void process_keypress_H(int key, endui_mouse* mouse, vec_void_t* handles,
                        EWH** drag_window) { /* our hook */
  if (key == 'p') { /* or any other key */
    /* do stuff */
  }
  yHookTrampoline(pkh, process_keypress, key, mouse, handles, drag_window); // call the original function
}

void main(void) {
  /* hook the function */
  pkh = yHookInstall(process_keypress, process_keypress_H);
  yHookEnable(pkh);
}

void endui_fini(){ return; }
```

## Examples
### Simple window with a button
```c
#include <window.h>

bool callback(struct EWH* sender, void* arg) {
  strcpy(sender->title, "Clicked");
  sender->width = 9;  // make the text in the center
}

void main(void) {
  EWH* window = ewh_new_window(1, 1, 15, 10, "Simple window");
  EWH* button = ewh_new_button(1, 1, 10, 3, "Click me", window);
  button->ewh_callback = callback;

  ewh_add(window);
  ewh_add(button);
}

void endui_fini() { return; }
```
