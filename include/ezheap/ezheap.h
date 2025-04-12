#ifndef EZHEAP_H
#define EZHEAP_H

#include <stddef.h>
#include <string.h>

typedef struct ezheap_t {
	void** heap_addresses;
	size_t heap_addresses_len;
#ifdef EZHEAP_DBG
	int allocs;
	int frees;
#endif
} ezheap_t;

#ifndef EZHEAP_IMPL
extern ezheap_t __ezheap_instance;
#endif

/* we need to increment allocs & frees to make it match with valgrind */
#ifdef EZHEAP_DBG
#define ezheap_init()                                                                                                                                                                                                                                          \
	memset(&__ezheap_instance, 0, sizeof(__ezheap_instance));                                                                                                                                                                                                    \
	__ezheap_instance.allocs = 1;                                                                                                                                                                                                                                \
	__ezheap_instance.frees = 1
#else
#define ezheap_init() memset(&__ezheap_instance, 0, sizeof(__ezheap_instance))
#endif

#define new(x) __ezheap_malloc_errsafe(sizeof(x), &__ezheap_instance)
#define new_str(x) __ezheap_malloc_str_errsafe(sizeof(x), x, &__ezheap_instance)
#define ezheap_destruct() __ezheap_cleanup(&__ezheap_instance)

#ifdef EZHEAP_DBG
#define __ezheap_stdmalloc(x, y)                                                                                                                                                                                                                               \
	malloc(x);                                                                                                                                                                                                                                                   \
	y->allocs++
#else
#define __ezheap_stdmalloc(x, y) malloc(x)
#endif

#ifdef EZHEAP_DBG
#define __ezheap_stdfree(x, y)                                                                                                                                                                                                                                 \
	free(x);                                                                                                                                                                                                                                                     \
	y->frees++
#else
#define __ezheap_stdfree(x, y) free(x)
#endif

void* __ezheap_malloc_errsafe(size_t __size, ezheap_t* __ezheap);
void* __ezheap_malloc_str_errsafe(size_t __size, const char* __str, ezheap_t* __ezheap);
void __ezheap_cleanup(ezheap_t* __ezheap);

#define ezheap_dbg_info() __ezheap_debug_info(&__ezheap_instance)
void __ezheap_debug_info(ezheap_t* __ezheap);

#endif
