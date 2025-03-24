#include <endbar.h>
#include <settings.h>
#include <window.h>

bool active = true;

void main() {
  settings_main();
  endbar_main();
}

void endui_fini() { active = false; }