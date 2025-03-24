#if !defined(FNPTR_H)
#define FNPTR_H

#define fnptr(ret, name, ...) ret (*name)(__VA_ARGS__)

#endif /* FNPTR_H */
