#ifndef DRAWING_H
#define DRAWING_H

#include <mouse.h>
#include <vec.h>
#include <window.h>

void empty_screen();
void draw_windows(vec_void_t* handles, EWH* drag_window, endui_mouse* mouse);

#endif