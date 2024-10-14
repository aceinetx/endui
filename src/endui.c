#define ENDUI_IMPL

#include <fnptr.h>
#include <includes.h>
#include <libmem/libmem.h>

#define TARGET_FPS 60
#define FRAME_TIME (1000000 / TARGET_FPS)

/* vars/typedef's */
vec_void_t handles;
vec_void_t app_handles;
EWH *drag_window = NULL;

endui_mouse mouse = {0};

api_symbols symbols;

typedef fnptr(void *, endui_main);
typedef fnptr(void *, endapi_update_symbols, api_symbols *);
typedef fnptr(void *, endapi_fini);

/* functions */
void ewh_add(EWH *w) { vec_push(&handles, w); }

app_exec_result *runApp(const char *name) {
  app_exec_result *res = malloc(sizeof(*res));
  res->success = true;

  endui_main main_f;
  endapi_update_symbols update_symbols;

  res->handle = dlopen(name, RTLD_NOW); /* open the app's main library */
                                        /* kinda how android does */

#define handle_error()                       \
  if ((res->_dlerror = dlerror()) != NULL) { \
    res->success = false;                    \
    return res;                              \
  }

  if (!res->handle) {
    res->success = false;
    res->handle = NULL;
    return res;
  }

  main_f = dlsym(res->handle, "main");
  handle_error();
  update_symbols = dlsym(res->handle, "__endui_update_symbols");
  handle_error();
  ewh_add_t ewh_add_f = dlsym(res->handle, "ewh_add");
  handle_error();

  /* hook api functions */
  LM_HookCode((lm_address_t)ewh_add_f, (lm_address_t)ewh_add, LM_NULLPTR);

  /* run main */
  update_symbols(&symbols);
  pthread_t dlth;
  pthread_create(&dlth, NULL, main_f, NULL);

  if (res->success && res->handle) {
    vec_push(&app_handles, &res);
  }
  return res;
#undef handle_error
}

void endui_init() {
  initscr();
  vec_init(&handles);
  vec_init(&app_handles);

  ezheap_init();

  setlocale(LC_ALL, "");
  /* initalize NCurses */
  start_color();
  use_default_colors();
  curs_set(0);
  noecho();
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);

  /* initalize color so we would able to use all 256 colors */
  for (int i = 0; i < COLORS; i++) {
    init_pair(i + 1, i, -1);
  }

  /* initalize symbols */
  /* pretty much deprecated, but we need it for variables */
  symbols.endui_scr = stdscr;
}

void endui_fini() {
  endwin();

  for (int i = 0; i < handles.length; i++) {
    EWH *handle = (EWH *)handles.data[i];
    if (handle->title != NULL) free(handle->title);
    if (handle->class != NULL) free(handle->class);
    free(handle);
  }
  vec_deinit(&handles);
  vec_deinit(&app_handles);
  ezheap_destruct();
}

int main() {
  // initalize

  endui_init();

  segcatch_init((fini_t)endui_fini); /* initalize segmentation fault catching */

  runApp("./libendbar.so"); /* open all default apps */
  runApp("./libsettings.so");

  // ---------

  while (true) {
    empty_screen(); /* pretty much the entire rendering */
    draw_windows(&handles, drag_window, &mouse);

    refresh();

    int k = getch();
    if (k == 'q') break;

    process_keypress(k, &mouse, &handles, &drag_window);

    usleep(FRAME_TIME);
  }

  // uninitalize

  endui_fini();

  // close apps
  for (int i = 0; i < app_handles.length; i++) {
    app_exec_result *app = (app_exec_result *)app_handles.data[i];
    if (app != NULL) {
      if (app->handle != NULL) {
        endapi_fini fini_f = dlsym(app->handle, "endui_fini");
        if (dlerror() == NULL) {
          fini_f();
        }
        dlclose(app->handle);
      }
    }
  }

  // -----------
}