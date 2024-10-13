# Api documentation
## Variables / Functions
```c
EWH* ewh_new() // creates a new handle
EWH *ewh_new_window(int x, int y, int width, int height, const char *title) // creates a new window, autofills the fields of EWH with the arguments
EWH *ewh_new_button(int x, int y, int width, int height, const char *title, EWH *parent) // creates a new button
void ewh_add(EWH* w) // add a window to handles
WINDOW *endui_scr // ncurses stdscr pointer
```
## Examples
### Simple window with a button
```c
#include <endapi.h>
#include <window.h>

bool callback(struct EWH* sender, void* arg) {
  strcpy(sender->title, "Clicked");
  sender->width = 9;  // make the text in the center
}

int main(void) {
  EWH* window = ewh_new_window(1, 1, 15, 10, "Simple window");
  EWH* button = ewh_new_button(1, 1, 10, 3, "Click me", window);
  button->ewh_callback = callback;

  ewh_add(window);
  ewh_add(button);
}

void endui_fini() { return; }
```