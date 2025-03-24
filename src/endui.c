#define ENDUI_IMPL

#include <endlib.h>
#include <fnptr.h>
#include <includes.h>
#include <virtual_desktop.h>

#define TARGET_FPS 60
#define FRAME_TIME (1000000 / TARGET_FPS)

/* vars/typedef's */

typedef fnptr(void *, endui_main);
typedef fnptr(void, endapi_fini);

/* functions */

char errs[1024];

app_exec_result *run_app(const char *name) {
  endui_main main_f;
  app_exec_result *res;
  pthread_t dlth;

  res = malloc(sizeof(*res));
  res->success = true;

  res->handle = dlopen(name, RTLD_NOW); /* open the app's main library */
                                        /* kinda how android does */

#define handle_error()                                                         \
  if ((res->_dlerror = dlerror()) != NULL) {                                   \
    res->success = false;                                                      \
    return res;                                                                \
  }

  if (!res->handle) {
    res->success = false;
    res->handle = NULL;
    res->_dlerror = dlerror();
    return res;
  }

  main_f = dlsym(res->handle, "main");
  handle_error();
  handle_error();

  /* run main */
  pthread_create(&dlth, NULL, main_f, NULL);

  if (res->success && res->handle) {
    vec_push(&app_handles, (void *)res);
  }
  return res;
#undef handle_error
}

void endui_init() {
  int i;

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
  for (i = 0; i < COLORS; i++) {
    init_pair(i + 1, i, -1);
  }
}

void *endui_fini() {
  int i;

  endwin();

  for (i = 0; i < handles.length; i++) {
    EWH *handle = (EWH *)handles.data[i];
    if (handle->title != NULL)
      free(handle->title);
    free(handle);
  }
  vec_deinit(&handles);
  vec_deinit(&app_handles);
  ezheap_destruct();

  return NULL;
}

int main() {
  int i;
  app_exec_result *app_res;
  /* initalize */

  endui_init();

  segcatch_init((fini_t)endui_fini); /* initalize segmentation fault catching */

  app_res = run_app("./libeverything.so");
  if (app_res->success == false) { /* open default app */
    free(app_res);
  }

  /* --------- */

  while (true) {
    int k;

    empty_screen(); /* pretty much the entire rendering */
    draw_windows(&handles, drag_window, &mouse);

    refresh();

    k = getch();
    if (k == 'q')
      break;

    process_keypress(k, &mouse, &handles, &drag_window);

    usleep(FRAME_TIME);
  }

  /* uninitalize */

  /* close apps */
  for (i = 0; i < app_handles.length; i++) {
    endapi_fini fini_f;
    app_exec_result *app;

    app = (app_exec_result *)app_handles.data[i];
    if (app != NULL) {
      if (app->handle != NULL) {
        fini_f = dlsym(app->handle, "endui_fini");
        if (dlerror() == NULL) {
          fini_f();
        }
        dlclose(app->handle);
      }
    }
    free(app);
  }
  endui_fini();

  /* ----------- */
  return 0;
}
