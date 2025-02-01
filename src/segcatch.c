#include <segcatch.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

fini_t fini_f = NULL;

void endui_segfault_handler(int signal, siginfo_t *si, void *arg) {
  if (fini_f)
    fini_f();
  printf("============ Segmentation Fault ============\n");
  printf("if you see this message, endui was properly\n");
  printf("closed, so it's likely not an issue with\n");
  printf("any external libraries\n\n");
  printf("Faulty address: %p\n", si->si_addr);
  printf("More info:\n");
  printf("si->si_code = %d\n", si->si_code);
  printf("si->si_errno = %d\n", si->si_errno);
  printf("si->si_signo = %d\n", si->si_signo);
  printf("============ ------------------ ============\n");
  exit(1);
}

void segcatch_init(fini_t __fini_f) {
  struct sigaction sa;
  memset(&sa, 0, sizeof(struct sigaction));
  sigemptyset(&sa.sa_mask);
  sa.sa_sigaction = endui_segfault_handler;
  sa.sa_flags = SA_SIGINFO;

  sigaction(SIGSEGV, &sa, NULL);

  fini_f = __fini_f;
}