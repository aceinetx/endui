#define ENDUI_IMPL

#include <includes.h>

#define TARGET_FPS 60
#define FRAME_TIME (1000000 / TARGET_FPS)

// vars/typedef's
vec_void_t handles;
vec_void_t app_handles;
EWH *drag_window = NULL;

endui_mouse mouse = {0};

api_symbols symbols;

typedef void *(*endui_main)();
typedef void *(*endapi_update_symbols)(api_symbols *);
typedef void *(*endapi_fini)();

// functions
void ewh_add(EWH *w) { vec_push(&handles, w); }

app_exec_result *runApp(const char *name) {
  app_exec_result *res = malloc(sizeof(void *) + sizeof(void *) + sizeof(bool));
  res->handle = NULL;
  res->success = true;

  endui_main main_f;
  endapi_update_symbols update_symbols;

  res->handle = dlopen(name, RTLD_NOW);

  if (res->handle) {
    main_f = dlsym(res->handle, "main");
    if ((res->_dlerror = dlerror()) != NULL) {
      res->success = false;
      return res;
    }
    update_symbols = dlsym(res->handle, "__endui_update_symbols");
    if ((res->_dlerror = dlerror()) != NULL) {
      res->success = false;
      return res;
    }

    update_symbols(&symbols);
    pthread_t dlth;
    pthread_create(&dlth, NULL, main_f, &symbols);
  } else {
    res->success = false;
    res->handle = NULL;
  }
  if (res->success && res->handle) {
    vec_push(&app_handles, &res);
  }
  return res;
}

void endui_init() {
  initscr();
  vec_init(&handles);
  vec_init(&app_handles);

  ezheap_init();

  setlocale(LC_ALL, "");
  start_color();
  use_default_colors();
  curs_set(0);
  noecho();
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);

  for (int i = 0; i < COLORS; i++) {
    init_pair(i + 1, i, -1);
  }

  symbols.ewh_add_f = ewh_add;
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

  segcatch_init((fini_t)endui_fini);

  app_exec_result *res = runApp("./libendbar.so");

  // ---------

  while (true) {
    empty_screen();
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