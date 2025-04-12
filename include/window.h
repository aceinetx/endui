#ifndef WINDOW_H
#define WINDOW_H

#include <max_len.h>
#include <stdbool.h>
#include <vec.h>

typedef enum { EWH_NORESIZE = 1, EWH_NOMOVE = 2, EWH_NOTITLE = 4 } EWH_WINFLAGS;

typedef enum { EWH_BUTTON = 0x0001, EWH_LABEL = 0x0002, EWH_SEPARATOR = 0x0003 } EWH_CHILDCLASS;

typedef struct EWH {
	int width;
	int height;
	int y;
	int x;
	int child_class;
	int flags;
	int clicked_frames;
	char virtual_desktop_id;
	struct EWH* parent;
	bool (*ewh_callback)(struct EWH*, void*);
	char* title;
	bool hidden;
} EWH;

void ewh_add(EWH* w);

EWH* ewh_new();
EWH* ewh_new_window(int x, int y, int width, int height, const char* title);
EWH* ewh_new_button(int x, int y, int width, int height, const char* title, EWH* parent);
EWH* ewh_new_label(int x, int y, const char* title, EWH* parent);
EWH* ewh_new_separator(int x, int y, int width, EWH* parent);

#define ewh_title(w, t)                                                                                                                                                                                                                                        \
	if (w->title)                                                                                                                                                                                                                                                \
		free(w->title);                                                                                                                                                                                                                                            \
	w->title = malloc(WINDOW_TITLE_MAX);                                                                                                                                                                                                                         \
	strncpy(w->title, t, WINDOW_TITLE_MAX)

#define ewh_class(w, t)                                                                                                                                                                                                                                        \
	if (w->class)                                                                                                                                                                                                                                                \
		free(w->class);                                                                                                                                                                                                                                            \
	w->class = malloc(WINDOW_CLASS_MAX);                                                                                                                                                                                                                         \
	strncpy(w->class, t, WINDOW_CLASS_MAX)

#endif
