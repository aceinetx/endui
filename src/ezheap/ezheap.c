#define EZHEAP_IMPL

#include <ezheap.h>
#include <stdio.h>
#include <stdlib.h>

ezheap_t __ezheap_instance = {0};

void *__ezheap_malloc(size_t __size, ezheap_t *__ezheap) {
  void *heap_addr = __ezheap_stdmalloc(__size, __ezheap);

  if (__ezheap->heap_addresses == NULL && __ezheap->heap_addresses_len == 0) {
    // create an empty array of newly created address
    __ezheap->heap_addresses = __ezheap_stdmalloc(sizeof(void *), __ezheap);
    if (__ezheap->heap_addresses == NULL) {
      printf("[EZHEAP] malloc() failed: __ezheap->heap_addresses == NULL\n");
      abort();
    }
    memcpy(__ezheap->heap_addresses, &heap_addr, sizeof(&heap_addr));
    __ezheap->heap_addresses_len = 1;
  } else if (__ezheap->heap_addresses != NULL &&
             __ezheap->heap_addresses_len > 0) {
    size_t old_array_len_bytes = sizeof(void *) * __ezheap->heap_addresses_len;

    // create a new array
    void *new_heap_addresses =
        __ezheap_stdmalloc(old_array_len_bytes + sizeof(void *), __ezheap);
    if (new_heap_addresses == NULL) {
      printf("[EZHEAP] malloc() failed: _new_heap_addresses == NULL\n");

      if (__ezheap->heap_addresses != NULL) free(__ezheap->heap_addresses);
      abort();
    }
    memcpy(new_heap_addresses, __ezheap->heap_addresses, old_array_len_bytes);
    memcpy(new_heap_addresses + old_array_len_bytes, &heap_addr,
           sizeof(void *));

    // change old array to a new one
    __ezheap_stdfree(__ezheap->heap_addresses, __ezheap);
    __ezheap->heap_addresses = new_heap_addresses;
    __ezheap->heap_addresses_len++;
  } else {
    return NULL;
  }

  return heap_addr;
}

void *__ezheap_malloc_errsafe(size_t __size, ezheap_t *__ezheap) {
  void *result = __ezheap_malloc(__size, __ezheap);
  if (result == NULL) {
    printf(
        "[EZHEAP] __ezheap_malloc() failed: either malloc() failed, or bad "
        "heap_addresses\n");
    abort();
  }
  return result;
}

void *__ezheap_malloc_str_errsafe(size_t __size, const char *__str,
                                  ezheap_t *__ezheap) {
  void *result = __ezheap_malloc_errsafe(__size, __ezheap);
  memcpy(result, __str, __size);
  return result;
}

void __ezheap_cleanup(ezheap_t *__ezheap) {
  if (__ezheap->heap_addresses == NULL) return;

  for (int i = 0; i < __ezheap->heap_addresses_len; i++) {
    __ezheap_stdfree(__ezheap->heap_addresses[i], __ezheap);
  }
  __ezheap_stdfree(__ezheap->heap_addresses, __ezheap);
}

#ifdef EZHEAP_DBG
void __ezheap_debug_info(ezheap_t *__ezheap) {
  printf("-----------------\n");
  printf("EZHeap debug info\n");
  printf("=================\n");
  printf("heap usage (calls from ezheap)\n");
  printf("allocs: %d\n", __ezheap->allocs);
  printf("frees: %d\n", __ezheap->frees);
  printf("-----------------\n");
}
#endif