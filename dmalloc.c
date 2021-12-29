#include "dmalloc.h"
#include <string.h>

#define BOUNDARY_SZ 4
#define TRAILER_MAGIC 0xAD
#define HH_TRACK_SZ 5

typedef struct metadata metadata_t;
struct metadata {
    size_t sz;
    uintptr_t alloced;
    metadata_t *next, *prev;
};

typedef struct base_alloc {
    uintptr_t addr;
    size_t sz;
} base_alloc_t;



