#define DMALLOC_DISABLE 1
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

static bst_t* frees;

static hashtree_t* allocs;

static void init_base_alloc();

static void base_allocator_atexit();

void* dmalloc(size_t sz, const char* file, size_t line){
    if (sz == 0)
        return NULL;

    if (disabled){
        return malloc(sz);
    }

    ++disabled;

    init_base_alloc();

    void* ptr = bst_fetch(frees, sz);

    if (!ptr) {
        ptr = malloc(sz);
    }

    if (!ptr) {
        fprintf(stderr, "ERROR: failed to allocate %s, %zu, size %zu\n", file, line, sz);
        exit(EXIT_FAILURE);
    }

    if (ptr) {
        val_t v = {(uintptr_t)ptr, sz};
        ht_ins(allocs, v);
    }

    --disabled;
    return ptr;
}


void dfree(void* ptr, const char* file, size_t line){
    if (disabled || !ptr){
        free(ptr);
    } else {
        ++disabled;
        hashtree_t* ht = ht_get(allocs, (uintptr_t)ptr);
        if (!ht){
            fprintf(stderr, "ERROR: wild free, %p, %s, %zu\n", ptr, file, line);
            exit(EXIT_FAILURE);
        }
        ht_del(allocs, ht->val);
        --disabled;
    }
}


static void init_base_alloc(){
    static int base_alloc_atexit_installed = 0;
    if (!base_alloc_atexit_installed){
        atexit(base_allocator_atexit);
        frees = bst_init();
        allocs = ht_init();
        base_alloc_atexit_installed = 1;
    }
}

static void base_allocator_atexit() {
    ht_mem_leak_report(allocs);
    bst_free(frees);
}
