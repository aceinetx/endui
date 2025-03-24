#include <virtual_desktop.h>

char desktop_id = 1;

char *get_desktop_id_ptr() { return &desktop_id; }
char get_max_desktops() { return 4; }
