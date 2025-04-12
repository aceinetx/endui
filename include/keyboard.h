#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <mouse.h>
#include <vec.h>
#include <window.h>

void process_keypress(int key, endui_mouse* mouse, vec_void_t* handles, EWH** drag_window);

#endif