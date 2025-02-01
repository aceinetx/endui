#if !defined(ENDBAR_H)
#define ENDBAR_H

#include <stdbool.h>
#include <window.h>

extern EWH *bar;
extern EWH *main_button;
extern EWH *main_menu;

bool endbar_toggle_menu(struct EWH *sender, void *arg);
void endbar_main();

#endif // ENDBAR_H
