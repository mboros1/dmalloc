#ifndef BST_H
#define BST_H

#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

// binary search tree, each node contains a pointer to a freed allocation with it's
// address and size, search key being the size which allows us to quickly find
// unused allocations of the correct size and re-use them
// because duplicate allocation sizes are common, each node has a linked list of
// all freed allocations of the same size


// linked list for duplicate allocation sizes, just stores the address and next.
// size of the allocation is stored in the trees node
typedef struct bst_val bst_val_t;
struct bst_val {
    void* val;
    bst_val_t* next;
};

// struct for the nodes in the tree
// key: the size of the allocation
// val: the address of the first allocation
// next: pointer to the linked list of duplicate allocations
// left: pointer to left subtree
// right: pointer to right subtree
typedef struct bst bst_t;
struct bst {
    size_t key;
    void* val;
    bst_val_t* next;
    bst_t* left;
    bst_t* right;
};

// inits an empty bst with a dummy root node
bst_t* bst_init();

// fetches the next freed allocation that has size >= sz and pops it off the tree
void* bst_fetch(bst_t* root, size_t sz);

// insert a freed allocation into the tree
void bst_ins(bst_t* root, val_t val);

// free all nodes in a tree, should be called on program exit
void bst_free(bst_t* root);

// delete a node
void bst_del(bst_t* root, size_t key);

// print tree
void bst_print(bst_t* root);

#endif
