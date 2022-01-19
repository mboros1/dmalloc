#include "hash.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "quick_sort.h"
#include "test_runner.h"

const uint64_t seed = 0x1231231;

const uint64_t ptr = 0x000c03423400;

const size_t n = 1000000;

static key_t keys[n];

void gen_key_arr(){
    for(size_t i = ptr; i < n+ptr; ++i){
        key_t h = hash(i, seed);
        keys[i-ptr] = h;
    }
}

void test_keys_consistent(){
    for(size_t i = ptr; i < n+ptr; ++i){
        key_t h = hash(i, seed);
        assert(hash_equal(h, keys[i-ptr]));
    }
}

void test_collisions(){
    quick_sort(keys, 0, n-1);

    int collisions = 0;
    for(int i = 0; i < n-1; ++i){
        key_t k1 = keys[i];
        key_t k2 = keys[i+1];
        if (k1.h1 == k2.h1 && k1.h2 == k2.h2){
            printf("collision on %llu%llu\n", k1.h1, k1.h2);
            ++collisions;
        } 
        assert(k1.h1 <= k2.h1);
    }
    assert(collisions == 0);
}

int main(int argc, char** argv){

    gen_key_arr();

    run_test(test_keys_consistent);

    run_test(test_collisions);
}

