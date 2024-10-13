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