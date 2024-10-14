#include <vec.h>
#include <window.h>

EWH *ewh_new() {
  EWH *result = (EWH *)malloc(SIZEOF_EWH);
  memset(result, 0, SIZEOF_EWH);
  return result;
}

EWH *ewh_new_window(int x, int y, int width, int height, const char *title) {
  EWH *res = ewh_new();
  res->x = x;
  res->y = y;
  res->width = width;
  res->height = height;
  ewh_title(res, title);
  return res;
}

EWH *ewh_new_button(int x, int y, int width, int height, const char *title,
                    EWH *parent) {
  EWH *res = ewh_new();
  res->x = x;
  res->y = y;
  res->width = width;
  res->height = height;
  res->parent = parent;
  res->child_class = EWH_BUTTON;
  ewh_title(res, title);
  return res;
}

EWH *ewh_new_label(int x, int y, const char *title, EWH *parent) {
  EWH *res = ewh_new();
  res->x = x;
  res->y = y;
  res->child_class = EWH_LABEL;
  res->parent = parent;
  ewh_title(res, title);
  return res;
}

EWH *ewh_new_separator(int x, int y, int width, EWH *parent) {
  EWH *res = ewh_new();
  res->x = x;
  res->y = y;
  res->width = width;
  res->child_class = EWH_SEPARATOR;
  res->parent = parent;
  ewh_title(res, "");
  return res;
}