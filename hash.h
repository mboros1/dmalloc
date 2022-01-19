//-----------------------------------------------------------------------------
// This is an implementation of Austin Appleby's MurmurHash3 algorithm, 
// implemented by Martin Boros, a slight modification of the implementation 
// written by Peter Scott https://github.com/PeterScott/murmur3.git
//

#ifndef _HASH_H
#define _HASH_H

#include <stdint.h>
#include <stddef.h>

typedef struct key {
    uint64_t h1,h2;
} key_t;

typedef struct value {
    uintptr_t ptr;
    size_t sz;
} val_t;


// input: pointer to be hashed, seed value (should be set at the program level)
// output: 128-bit hash key
key_t hash(uintptr_t ptr, uint32_t seed);

// input: 2 128-bit hash keys
// output: 1 if they are equal, else 0
int hash_equal(key_t key1, key_t key2);

// input: 2 128-bit hash keys
// output: 1 if key1 is less then key2, else 0
int hash_less(key_t key1, key_t key2);

// input: 2 128-bit hash keys
// output: 1 if key1 is greater then key2, else 0
int hash_greater(key_t key1, key_t key2);

#endif
