#include <endapi.h>
#include <window.h>

typedef struct {
} settings;

bool settings_callback_button1(struct EWH* sender, void* arg) {
  strcpy(sender->title, "Clicked");
  sender->width = 9;  // make the text in the center
}

int settings_main(void) {
  EWH* window = ewh_new_window(1, 1, 15, 10, "Simple window");
  EWH* button = ewh_new_button(1, 1, 10, 3, "Click me", window);
  button->ewh_callback = settings_callback_button1;

  ewh_add(window);
  ewh_add(button);
}