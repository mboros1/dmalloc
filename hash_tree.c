//
// Binary search tree, see header file for details and API description
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hash_tree.h"

#define SEED 0x123123

hashtree_t *insert(hashtree_t *root, val_t value) {
    if (!root){
        return create_node(value);
    }

    hashtree_t* search_node = root;
    key_t key = hash(value.ptr, SEED);

    while (1){
        key_t search_key = search_node->key;
        if (hash_equal(key,search_key)) {
            search_node->val = value;
            return search_node;
        } else if (hash_less(key,search_key)) {
            if (!search_node->left){
                search_node->left = create_node(value);
                return search_node->left;
            } else {
                search_node = search_node->left;
            }
        } else {
            if (!search_node->right){
                search_node->right = create_node(value);
                return search_node->right;
            } else {
                search_node = search_node->right;
            }
        }
    }
    // shouldn't get here
    return NULL;
}

hashtree_t *create_node(val_t value) {
    hashtree_t* new_node = malloc(sizeof(hashtree_t));
    new_node->key = hash(value.ptr, SEED);
    new_node->val = value;
    new_node->left = new_node->right = NULL;
    return new_node;
}

void free_tree(hashtree_t *tree_ptr) {
    if (!tree_ptr) return;
    free_tree(tree_ptr->left);
    free_tree(tree_ptr->right);
    free(tree_ptr);
}

// TODO: make level search, print each level (allow checking how thick the trees are)
void print_tree(hashtree_t *tree_ptr) {
    if (!tree_ptr) return;
}
