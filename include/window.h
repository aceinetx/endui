#ifndef WINDOW_H
#define WINDOW_H

#include <max_len.h>
#include <stdbool.h>
#include <vec.h>

typedef enum {
  EWH_NORESIZE = 1,
  EWH_NOMOVE = 2,
  EWH_NOTITLE = 4,
} EWH_WINFLAGS;

typedef enum {
  EWH_BUTTON = 0x0001,
} EWH_CHILDCLASS;

typedef struct EWH {
  int width;
  int height;
  int y;
  int x;
  int child_class;
  int flags;
  int clicked_frames;
  struct EWH *parent;
  bool (*ewh_callback)(struct EWH *, void *);
  char *title;
  char *class;
  bool hidden;
} EWH;

#define SIZEOF_EWH                                                      \
  sizeof(int) + sizeof(int) + sizeof(int) + sizeof(int) + sizeof(int) + \
      sizeof(int) + sizeof(int) + sizeof(void *) + sizeof(void *) +     \
      sizeof(void *) + sizeof(void *) + sizeof(bool)

EWH *ewh_new();
EWH *ewh_new_window(int x, int y, int width, int height, const char *title);
EWH *ewh_new_button(int x, int y, int width, int height, const char *title,
                    EWH *parent);

#define ewh_title(w, t)                \
  if (w->title) free(w->title);        \
  w->title = malloc(WINDOW_TITLE_MAX); \
  strcpy(w->title, t)

#define ewh_class(w, t)                \
  if (w->class) free(w->class);        \
  w->class = malloc(WINDOW_CLASS_MAX); \
  strcpy(w->class, t)

#endif