#define ENDUI_IMPL
#include <virtual_desktop.h>

#include "includes.h"

void process_keypress(int key, endui_mouse *mouse, vec_void_t *handles,
                      EWH **drag_window) {
  int ncurses_wy = getmaxy(stdscr);
  int ncurses_wx = getmaxx(stdscr);

  switch (key) {
  case KEY_UP:
    mouse->y--;
    break;
  case KEY_DOWN:
    mouse->y++;
    break;
  case KEY_LEFT:
    mouse->x--;
    break;
  case KEY_RIGHT:
    mouse->x++;
    break;
  case 'z':
    for (int i = 0; i < handles->length; i++) {
      EWH *window = (EWH *)handles->data[i];
      if (window == NULL)
        continue;
      if (window->virtual_desktop_id != *get_desktop_id_ptr())
        continue;

      if (window->parent == NULL) {
        if (*drag_window == NULL) {
          if (mouse->x >= window->x &&
              (mouse->x < window->x + strlen(window->title)) &&
              (mouse->y == window->y) && !(window->flags & EWH_NOMOVE) &&
              !(window->flags & EWH_NOTITLE)) {
            *drag_window = window;
            break;
          }
        } else {
          if (*drag_window != NULL) {
            (*drag_window)->x = mouse->x;
            (*drag_window)->y = mouse->y;
            *drag_window = NULL;
            break;
          }
        }
      } else {
        switch (window->child_class) {
        case EWH_BUTTON:
          if (mouse->x >= (window->parent->x + window->x) &&
              (mouse->x < (window->parent->x + window->x + window->width)) &&
              (mouse->y >= (window->parent->y + window->y)) &&
              (mouse->y < (window->parent->y + window->y + window->height))) {
            if (window->ewh_callback != NULL) {
              window->ewh_callback(window, NULL);
              window->clicked_frames = 70;
              break;
            }
          }
          break;
        }
      }
    }
    break;
  case 'w':
    if (*drag_window != NULL) {
      if (!(*drag_window)->flags & EWH_NORESIZE)
        (*drag_window)->height--;
    }
    break;
  case 's':
    if (*drag_window != NULL) {
      if (!(*drag_window)->flags & EWH_NORESIZE)
        (*drag_window)->height++;
    }
    break;
  case 'a':
    if (*drag_window != NULL) {
      if (!(*drag_window)->flags & EWH_NORESIZE)
        (*drag_window)->width--;
    }
    break;
  case 'd':
    if (*drag_window != NULL) {
      if (!(*drag_window)->flags & EWH_NORESIZE)
        (*drag_window)->width++;
    }
    break;
  case 'k':
    (*get_desktop_id_ptr())++;

    break;
  case 'j':
    (*get_desktop_id_ptr())--;

    break;
  }
  if (*get_desktop_id_ptr() > get_max_desktops()) {
    *get_desktop_id_ptr() = get_max_desktops();
  } else if (*get_desktop_id_ptr() < 1)
    *get_desktop_id_ptr() = 1;

  if (mouse->x <= 0)
    mouse->x = 0;
  if (mouse->x >= ncurses_wx)
    mouse->x = ncurses_wx - 1;

  if (mouse->y <= 0)
    mouse->y = 0;
  if (mouse->y >= ncurses_wy)
    mouse->y = ncurses_wy - 1;
}
