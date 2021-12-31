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
hashtree_t* init_tree();

// inserts a value into tree, returns pointer to created leaf
hashtree_t *ins_node(hashtree_t *root, val_t value);

// initializes a new tree
hashtree_t *create_node(val_t value);

// frees node and all of it's children
void free_tree(hashtree_t *root);

// prints node and all of it's children
void print_tree(hashtree_t *root);

// delete a node, maintains search tree structure
void del_node(hashtree_t *root, val_t value);

#endif
