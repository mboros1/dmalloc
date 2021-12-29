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


key_t hash(uintptr_t ptr, uint32_t seed);

#endif
