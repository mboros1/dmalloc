#define DMALLOC_DISABLE 1
#include "dmalloc.h"

#define BOUNDARY_SZ 4
#define TRAILER_MAGIC 0xAD

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
        ptr = malloc(sz+BOUNDARY_SZ);
    }

    if (!ptr) {
        fprintf(stderr, "ERROR: failed to allocate %s:%zu, size %zu\n", file, line, sz);
        exit(EXIT_FAILURE);
    }

    if (ptr) {
        *((char*)ptr+sz) = TRAILER_MAGIC;
        val_t v = {(uintptr_t)ptr, sz};
        ht_ins(allocs, v, file, line);
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
            fprintf(stderr, "ERROR: wild free, %p, %s:%zu\n", ptr, file, line);
            exit(EXIT_FAILURE);
        }

        size_t sz = ht->val.sz;

        bst_ins(frees, ht->val);
        ht_del(allocs, ht->val);
        --disabled;

        uint8_t boundary = *( (uint8_t*)ptr + sz);
        if (boundary != TRAILER_MAGIC){
          fprintf(stderr, "ERROR: write past end of allocation for pointer %p at address %p, %s:%zu\n",
              ptr, (char*)ptr+sz, file, line);
          exit(EXIT_FAILURE);
        }
    }
}

void* dcalloc(size_t nmemb, size_t sz, const char* file, size_t line){
    if (((size_t)-1)/nmemb <= sz){
        fprintf(stderr, "ERROR: failed to allocate %s, %zu, count %zu of size %zu\n", file, line, nmemb, sz);
        exit(EXIT_FAILURE);
    }

    void* ptr = dmalloc(nmemb * sz, file, line);
    if (ptr){
        memset(ptr, 0, nmemb * sz);
    }
    return ptr;
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
