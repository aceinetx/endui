# endui
A sequel to TWn, completely rewritten
## Why rewrite?
- TWn had many bugs and crashes
- I wanted to rewrite it completely with C (maybe c3) for more speed
- I wanted to use CMake as a build system to make testing and cross-platforming easier
- TWn had really bad codebase, like, the entire drawing was in a main.c, endui will solve that
## Pros/Cons of using EndUI
### Pros
- The most lightweight window manager
- Supports TTY only environment (like a fresh archlinux install)
- Easy to develop apps
### Cons
- Doesn't support GTK/Qt (or others) gui frameworks
## API
- [API documentation](APIDOCS.md)

EndUI will be tested on as many platforms as possible to avoid all bugs
