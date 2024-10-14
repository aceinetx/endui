#define ENDUI_IMPL
#include "includes.h"

wchar_t graphics[] = {L'▒', L'▓', L'▒'};

void empty_screen() {
  for (int i = 0; i < getmaxy(stdscr); i++) {
    for (int j = 0; j < getmaxx(stdscr); j++) {
      attron(COLOR_PAIR(242));
      mvaddwstr(i, j, &graphics[0]);
      attroff(COLOR_PAIR(242));
    }
  }
}

void draw_windows(vec_void_t *handles, EWH *drag_window, endui_mouse *mouse) {
  /* draw parent windows first */
  for (int wi = 0; wi < handles->length; wi++) {
    EWH *window = (EWH *)handles->data[wi];

    if (window == NULL) continue;

    if (window->parent == NULL && window->hidden == false) {
      int end_y = window->y + window->height;
      int end_x = window->x + window->width;

      for (int x = window->x; x < end_x; x++) {
        for (int y = window->y; y < end_y; y++) {
          attron(COLOR_PAIR(249));
          mvaddwstr(y, x, &graphics[2]);
          attroff(COLOR_PAIR(249));
        }
      }

      if (!(window->flags & EWH_NOTITLE)) {
        int text_y = window->y;
        int text_x = window->x;
        if (drag_window == window) {
          mvaddwstr(text_y, text_x, L"• ");
          text_x += 2;
        }
        mvprintw(text_y, text_x, "%s", window->title);
      }
    }
  }

  /* draw child windows after parent one's */
  for (int wi = 0; wi < handles->length; wi++) {
    EWH *window = handles->data[wi];

    if (window == NULL) continue;
    if (window->parent == NULL) continue;

    window->hidden = window->parent->hidden;
    if (!window->hidden) {
      switch (window->child_class) {
        case EWH_BUTTON:
          int end_y = window->parent->y + window->y + window->height;
          int end_x = window->parent->x + window->x + window->width;

          for (int x = window->parent->x + window->x; x < end_x; x++) {
            for (int y = window->parent->y + window->y; y < end_y; y++) {
              int color = 247;
              if (window->clicked_frames > 0) {
                color = 240;
                window->clicked_frames--;
              }

              attron(COLOR_PAIR(color));
              mvaddwstr(y, x, &graphics[1]);
              attroff(COLOR_PAIR(color));
            }
          }

          int text_x = window->x + window->parent->x + (window->width / 2) -
                       (strlen(window->title) / 2);
          int text_y = window->y + window->parent->y + (window->height / 2);
          mvprintw(text_y, text_x, "%s", window->title);
          break;
        case EWH_LABEL:
          mvprintw(window->parent->y + window->y, window->parent->x + window->x,
                   "%s", window->title);
          break;
        case EWH_SEPARATOR:
          for (int i = 0; i < window->width; i++) {
            mvprintw(window->parent->y + window->y,
                     window->parent->x + window->x + i, "-");
          }
      }
    }
  }
  mvprintw(mouse->y, mouse->x, ".");
}