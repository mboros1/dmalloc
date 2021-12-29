//
// Binary search tree, see header file for details and API description
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hash_tree.h"


hashtree_t *insert(hashtree_t *root, val_t value) {
    if (!root){
        return init_tree(value);
    }

    hashtree_t* searchNode = root;
    key_t key = hash(value.ptr);

    while (1){
        if (strcmp(searchNode->key, value) == 0){
            searchNode->value++;
            break;
        } else if (strcmp(searchNode->key, value) < 0) {
            if (!searchNode->left){
                searchNode->left = createNode(value);
                break;
            } else {
                searchNode = searchNode->left;
            }
        } else {
            if (!searchNode->right){
                searchNode->right = createNode(value);
                break;
            } else {
                searchNode = searchNode->right;
            }
        }
    }
    return searchNode;
}

hashtree_t *init_tree(const char *value) {
    hashtree_t* newNode = (hashtree_t*)malloc(sizeof(hashtree_t));
    char* keyString = (char*)malloc(strlen(value) + 1);
    strcpy(keyString, value);
    newNode->key = keyString;
    newNode->value = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void freeTree(hashtree_t *pBtree) {
    if (!pBtree) return;
    freeTree(pBtree->left);
    freeTree(pBtree->right);
    free(pBtree->key);
    free(pBtree);
}

void printTree(hashtree_t *pBtree) {
    if (!pBtree) return;
    printTree(pBtree->right);
    printf("%s %d\n", pBtree->key, pBtree->value);
    printTree(pBtree->left);
}
