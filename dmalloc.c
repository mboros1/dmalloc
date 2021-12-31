#include "dmalloc.h"

#define BOUNDARY_SZ 4
#define TRAILER_MAGIC 0xAD
#define HH_TRACK_SZ 5

typedef struct metadata metadata_t;
struct metadata {
    size_t sz;
    uintptr_t alloced;
    metadata_t *next, *prev;
};

static int disabled;

static struct {
    freed_ptr_t *ptrs;
    size_t sz;
} frees = {0,0};

static void init_base_alloc();

static unsigned alloc_random();

static void base_allocator_atexit();

void* base_malloc(size_t sz){
    if (disabled){
        return malloc(sz);
    }

    ++disabled;
    uintptr_t ptr = 0;

    init_base_alloc();

    unsigned r = alloc_random();
    if (r % 4 != 0){
        for(size_t ntries = 0; ntries < 10 && ntries < frees.sz; ++ntries){
            freed_ptr_t f = frees.ptrs[alloc_random() % frees.sz];
            if (f.sz >= sz){

        }
    }


}

static unsigned alloc_random() {
    static uint64_t x = 8973443640547502487ULL;
    x = x * 6364136223846793005ULL + 1ULL;
    return x >> 32;
}


static void init_base_alloc(){
    static int base_alloc_atexit_installed = 0;
    if (!base_alloc_atexit_installed){
        atexit(base_allocator_atexit);
        base_alloc_atexit_installed = 1;
    }
}

static void base_allocator_atexit() {
    // clean up freed memory to shut up leak detector
    for (size_t i = 0; i < frees.sz; ++i) {
        free((void*)frees.ptrs[i].ptr);
    }
}
