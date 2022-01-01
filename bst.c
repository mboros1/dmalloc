#include "bst.h"

bst_t* bst_new(void* ptr, size_t sz){
    bst_t* tmp = malloc(sizeof(bst_t));
    tmp->key = sz;
    tmp-> val = ptr;
    tmp->next = NULL;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}

bst_t* bst_init(){
    return bst_new(0, 0);
}

bst_t* find_min(bst_t* root){
    if (!root)
        return NULL;
    if (root->left)
        return find_min(root->left);

    return root;
}

bst_t* remove_node(bst_t* search_node, void** out_ptr){
    if (search_node->next){
        bst_val_t* tmp = search_node->next;
        search_node->next = search_node->next->next;
        *out_ptr = tmp->val;
        free(tmp);
    } else {
        *out_ptr = search_node->val;
        bst_t* tmp = search_node;
        if (!search_node->left && !search_node->right){
            free(tmp);
            search_node = NULL;
        } else if (!search_node->left){
            search_node = search_node->right;
            free(tmp);
        } else if (!search_node->right){
            search_node = search_node->left;
            free(tmp);
        } else {
            bst_t* tmp = find_min(search_node->right);
            bst_del(search_node->right, tmp->key);
            return tmp;
        }
    }
    return search_node;
}

void bst_del(bst_t* root, size_t key){
    if (!root)
        return;

    bst_t* search_node = root;
    void* dummy_ptr;

    while(1){
        size_t search_key = search_node->key;
        if (key < search_key){
            if (search_node->left){
                if (key == search_node->left->key){
                    search_node->left = remove_node(search_node->left, &dummy_ptr);
                    return;
                }
                search_node = search_node->left;
            }
        } else if (key > search_key) {
            if (search_node->right){
                if (key == search_node->right->key){
                    search_node->right = remove_node(search_node->right, &dummy_ptr);
                    return;
                }
                search_node = search_node->right;
            }
        } else {
            return;
        }
    }
}

void* get_next(bst_t* root, size_t key){
    bst_t* search_node = root;
    while(search_node){
        size_t search_key = search_node->key;
        if (key < search_key){
            if (search_node->left){
                if (key == search_node->left->key){
                    void* out_ptr;
                    search_node->left = remove_node(search_node->left, &out_ptr);
                    return out_ptr;
                }
                search_node = search_node->left;
            } else {
                return NULL;
            }
        } else if (key > search_key){

        } else {

        }
    }
    return NULL;
}

void* bst_fetch(bst_t* root, size_t key){
    if (!root)
        return NULL;

    bst_t* search_node = root;
    bst_t* search_result = NULL;
    
    while(search_node){
        size_t search_key = search_node->key;
        if (key < search_key){
            if (!search_result || search_key < search_result->key){
                search_result = search_node;
            }
            search_node = search_node->left;
        } else if (key > search_key){
            search_node = search_node->right;
        }
        else {
            search_result = search_node;
            break;
        }
    }

    void* result = get_next(root, search_result->key);

    return result;
}

void bst_ins(bst_t* root, val_t val){
    bst_t* search_node = root;
    size_t key = val.sz;

    while(1){
        size_t search_key = search_node->key;
        if (key == search_key){
            bst_val_t* tmp = malloc(sizeof(bst_val_t));
            tmp->val = (void*)val.ptr;
            tmp->next = search_node->next;
            search_node->next = tmp;
            return;
        } else if (key < search_key){
            if (!search_node->left){
                search_node->left = bst_new((void*)val.ptr, val.sz);
                return;
            } else {
                search_node = search_node->left;
            }
        } else {
            if (!search_node->right){
                search_node->right = bst_new((void*)val.ptr, val.sz);
                return;
            } else {
                search_node = search_node->right;
            }
        }
    }
}

void bst_free(bst_t* root);
