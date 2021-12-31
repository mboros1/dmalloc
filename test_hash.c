#include "hash.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "quick_sort.h"

int main(int argc, char** argv){
    uint64_t seed = 0x1231231;
    uintptr_t ptr = (uintptr_t)malloc(1);

    size_t n = 1000000;
    key_t* keys = malloc(n*sizeof(key_t));
    for(size_t i = ptr; i < n+ptr; ++i){
        key_t h = hash(i, seed);
        keys[i-ptr] = h;
        if ((i-ptr) % 100000 == 0){
            printf("Run %lu...\n", i-ptr);
            printf("h=%llu%llu\n", h.h1,h.h2);
        }
    }
    quick_sort(keys, 0, n-1);

    int collisions = 0;
    for(int i = 0; i < n-1; ++i){
        key_t k1 = keys[i];
        key_t k2 = keys[i+1];
        if (k1.h1 == k2.h1 && k1.h2 == k2.h2){
            printf("collision on %llu%llu\n", k1.h1, k1.h2);
            ++collisions;
        } 
        if (k1.h1 > k2.h1){
            printf("improper sort on %llu%llu and %llu%llu\n", k1.h1, k1.h2, k2.h1, k2.h1);
        }
    }

    free(keys);
    printf("%d collisions after running %lu random numbers\n", collisions, n);

    val_t v = {3,3};
    key_t k1 = hash(v.ptr, seed);
    key_t k2 = hash(v.ptr, seed);

    assert(hash_equal(k1,k2));

}

