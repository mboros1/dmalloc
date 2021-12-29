#include "hash.h"

int hash_less(key_t key1, key_t key2){
    if (key1.h1 < key2.h1)
        return 1;
    
    if (key1.h1 == key2.h1 && key1.h2 < key2.h2)
        return 1;
    
    return 0;
}

int hash_greater(key_t key1, key_t key2){
    if (key1.h1 > key2.h1)
        return 1;

    if (key1.h1 == key2.h1 && key1.h2 > key2.h2)
        return 1;
    
    return 0;
}

int hash_equal(key_t key1, key_t key2){
    return key1.h1 == key2.h1 && key1.h2 == key2.h2;
}

static uint64_t rotl64 ( uint64_t x, int8_t r ) {
  return (x << r) | (x >> (64 - r));
}

static uint64_t fmix64 ( uint64_t k ) {
  k ^= k >> 33;
  k *= 0xff51afd7ed558ccdLLU;
  k ^= k >> 33;
  k *= 0xc4ceb9fe1a85ec53LLU;
  k ^= k >> 33;

  return k;
}


key_t hash(uintptr_t ptr, uint32_t seed) {
    uint64_t h1 = seed;
    uint64_t h2 = seed;

    uint64_t c1 = 0x87c37b91114253d5LLU;
    uint64_t c2 = 0x4cf5ad432745937fLLU;

    //----------
    // body

    uint64_t k1 = (uint64_t)ptr;
    uint64_t k2 = (uint64_t)ptr;

    k1 *= c1; k1  = rotl64(k1,31); k1 *= c2; h1 ^= k1;

    h1 = rotl64(h1,27); h1 += h2; h1 = h1*5+0x52dce729;

    k2 *= c2; k2  = rotl64(k2,33); k2 *= c1; h2 ^= k2;

    h2 = rotl64(h2,31); h2 += h1; h2 = h2*5+0x38495ab5;

    //----------
    // tail

    const uint8_t * tail = (const uint8_t*)(&ptr) + 3;

    k1 = 0;
    k2 = 0;

    k2 ^= (uint64_t)(tail[ 3]) << 24;
    k2 ^= (uint64_t)(tail[ 2]) << 16;
    k2 *= c2; k2  = rotl64(k2,33); k2 *= c1; h2 ^= k2;

    k1 ^= (uint64_t)(tail[ 1]) << 8;
    k1 ^= (uint64_t)(tail[ 0]) << 0;
    k1 *= c1; k1  = rotl64(k1,31); k1 *= c2; h1 ^= k1;

    //----------
    // finalization

    h1 += h2;
    h2 += h1;

    h1 = fmix64(h1);
    h2 = fmix64(h2);

    h1 += h2;
    h2 += h1;

    key_t result = {h1, h2};
    return result;
}
