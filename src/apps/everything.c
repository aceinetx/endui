#include <endapi.h>
#include <endbar.h>
#include <settings.h>
#include <window.h>

void main() {
  settings_main();
  endbar_main();
}

void endui_fini() {}