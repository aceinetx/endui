#if !defined(SETTINGS_H)
#define SETTINGS_H

#include <window.h>
bool settings_callback_button1(struct EWH *sender, void *arg);
int settings_main(void);

extern EWH *settings_window;

#endif  // SETTINGS_H
