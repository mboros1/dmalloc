#ifndef DMALLOC_H
#define DMALLOC_H
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <sys/mman.h>
#include "hash.h"
#include "hash_tree.h"

typedef val_t freed_ptr_t;

/// dmalloc(sz, file, line)
///    Return a pointer to `sz` bytes of newly-allocated dynamic memory.
void* dmalloc(size_t sz, const char* file, long line);

/// dfree(ptr, file, line)
///    Free the memory space pointed to by `ptr`.
void dfree(void* ptr, const char* file, long line);

/// dcalloc(nmemb, sz, file, line)
///    Return a pointer to newly-allocated dynamic memory big enough to
///    hold an array of `nmemb` elements of `sz` bytes each. The memory
///    should be initialized to zero.
void* dcalloc(size_t nmemb, size_t sz, const char* file, long line);

#define malloc(sz)          dmalloc((sz), __FILE__, __LINE__)
#define free(ptr)           dfree((ptr), __FILE__, __LINE__)
#define calloc(nmemb, sz)   dcalloc((nmemb), (sz), __FILE__, __LINE__)


#endif
