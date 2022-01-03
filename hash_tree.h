#ifndef HASHTREE_H
#define HASHTREE_H

// binary hash tree structure; hash created with murmur3 128 bit hash
// key: 128-bit hash of ptr
// val: address of alloc and it's size
// left: left child of node, left->key must be less than key
// right: right child of node, right->key must be greater than key

#include "hash.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct hashtree hashtree_t;
struct hashtree {
    key_t key;
    val_t val;
    hashtree_t* left;
    hashtree_t* right;
};

// initializes the root node, which is a dummy with zero'd out data. Tree must be initialized before use
hashtree_t* ht_init();

// inserts a value into tree, returns pointer to created leaf
hashtree_t * ht_ins(hashtree_t *root, val_t value);

// create a new node
hashtree_t *ht_new(val_t value);

// frees node and all of it's children
void ht_free(hashtree_t *root);

// prints node and all of it's children
void ht_print(hashtree_t *root);

// delete a node, maintains search tree structure
void ht_del(hashtree_t *root, val_t value);

// search for a node with given pointer, return the node or NULL if not found
hashtree_t* ht_get(hashtree_t* root, uintptr_t ptr);

// prints out report of all detected memory leaks
void ht_mem_leak_report(hashtree_t *root);

#endif
