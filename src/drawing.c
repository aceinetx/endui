#define ENDUI_IMPL
#include <virtual_desktop.h>

#include "includes.h"

void empty_screen() {
  int i, j;

  attron(COLOR_PAIR(242));
  for (i = 0; i < getmaxy(stdscr); i++) {
    for (j = 0; j < getmaxx(stdscr); j++) {
      mvprintw(i, j, ".");
    }
  }
  attroff(COLOR_PAIR(242));
}

void draw_windows(vec_void_t *handles, EWH *drag_window, endui_mouse *mouse) {
  int i, wi;
  /* fix newly appeared windows */
  for (wi = 0; wi < handles->length; wi++) {
    EWH *window = (EWH *)handles->data[wi];

    if (window == NULL)
      continue;
    if (window->virtual_desktop_id == 0)
      window->virtual_desktop_id = *get_desktop_id_ptr();
  }

  /* draw parent windows first */
  for (wi = 0; wi < handles->length; wi++) {
    EWH *window = (EWH *)handles->data[wi];

    if (window == NULL)
      continue;

    if (window->parent == NULL && window->hidden == false &&
        window->virtual_desktop_id == *get_desktop_id_ptr()) {
      int end_y, end_x, x, y;

      end_y = window->y + window->height;
      end_x = window->x + window->width;

      for (x = window->x; x < end_x; x++) {
        for (y = window->y; y < end_y; y++) {
          attron(COLOR_PAIR(249));
          mvprintw(y, x, "##");
          attroff(COLOR_PAIR(249));
        }
      }

      if (!(window->flags & EWH_NOTITLE)) {
        int text_y = window->y;
        int text_x = window->x;
        if (drag_window == window) {
          mvaddstr(text_y, text_x, "• ");
          /* addwstr(L"• ");
           waddnwstr(stdscr, L"", -1);*/
          text_x += 2;
        }
        mvprintw(text_y, text_x, "%s", window->title);
      }
    }
  }

  /* draw child windows after parent one's */
  for (wi = 0; wi < handles->length; wi++) {
    EWH *window = handles->data[wi];

    if (window == NULL)
      continue;
    if (window->parent == NULL)
      continue;

    window->hidden = window->parent->hidden;
    window->virtual_desktop_id = window->parent->virtual_desktop_id;
    if (!window->hidden &&
        window->virtual_desktop_id == *get_desktop_id_ptr()) {
      int end_y, end_x, text_x, text_y, x, y;
      switch (window->child_class) {
      case EWH_BUTTON:
        end_y = window->parent->y + window->y + window->height;
        end_x = window->parent->x + window->x + window->width;

        for (x = window->parent->x + window->x; x < end_x; x++) {
          for (y = window->parent->y + window->y; y < end_y; y++) {
            int color = 247;
            if (window->clicked_frames > 0) {
              color = 0;
              window->clicked_frames--;
            }
            attron(COLOR_PAIR(color));
            mvaddstr(y, x, "|");
            attroff(COLOR_PAIR(color));
          }
        }

        text_x = window->x + window->parent->x + (window->width / 2) -
                 (strlen(window->title) / 2);
        text_y = window->y + window->parent->y + (window->height / 2);
        mvprintw(text_y, text_x, "%s", window->title);
        break;
      case EWH_LABEL:
        mvprintw(window->parent->y + window->y, window->parent->x + window->x,
                 "%s", window->title);
        break;
      case EWH_SEPARATOR:
        for (i = 0; i < window->width; i++) {
          mvprintw(window->parent->y + window->y,
                   window->parent->x + window->x + i, "-");
        }
      }
    }
  }
  mvprintw(mouse->y, mouse->x, "*");
}
