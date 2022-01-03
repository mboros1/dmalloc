#define DMALLOC_DISABLE 1
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

bst_t* bst_find_min(bst_t* root){
    if (!root)
        return NULL;
    if (root->left)
        return bst_find_min(root->left);

    return root;
}

void* bst_bst_pop(bst_t* root, size_t key);

bst_t* bst_remove_next(bst_t* search_node, void** out_ptr){
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
            bst_t* tmp = bst_find_min(search_node->right);
            bst_bst_pop(search_node->right, tmp->key);
            return tmp;
        }
    }
    return search_node;
}

void* bst_bst_pop(bst_t* root, size_t key){
    if (!root)
        return NULL;

    bst_t* search_node = root;
    void* out_ptr;

    while(1){
        size_t search_key = search_node->key;
        if (key < search_key){
            if (search_node->left){
                if (key == search_node->left->key){
                    search_node->left = bst_remove_next(search_node->left, &out_ptr);
                    return out_ptr;
                }
                search_node = search_node->left;
            }
        } else if (key > search_key) {
            if (search_node->right){
                if (key == search_node->right->key){
                    search_node->right = bst_remove_next(search_node->right, &out_ptr);
                    return out_ptr;
                }
                search_node = search_node->right;
            }
        } else {
            return NULL;
        }
    }
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

    if (!search_result)
        return NULL;

    return bst_bst_pop(root, search_result->key);
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

// interface for queue used by ht_print
typedef struct list_node list_node_t;
struct list_node {
    bst_t* val;
    list_node_t* next;
};

typedef struct queue bst_queue_t;
struct queue {
    size_t sz;
    list_node_t* head;
    list_node_t* tail;
};

// get the next value on the queue without destroying any data
bst_t* bst_peek(bst_queue_t* queue);

// get's the next value while moving the queue forward once
bst_t* bst_pop(bst_queue_t* queue);

// bst_pushes a hashtree node to the end of the queue
void bst_push(bst_queue_t* queue,bst_t* tree);

// checks whether the queue is empty, returns 0 if empty and 1 if not empty
int bst_is_empty(bst_queue_t* queue);

// creates a new empty queue; user responsible for freeing queue
bst_queue_t* init_queue();
// end queue interface

// prints tree by level
void bst_print(bst_t *tree_ptr) {
    if (!tree_ptr) return;
    bst_queue_t* queue = init_queue();
    bst_push(queue, tree_ptr);
    size_t level = 0;
    while(!bst_is_empty(queue)){
        int level_size = queue->sz;
        printf("Level %lu: ", level);
        while(level_size != 0){
            bst_t* curr_node = bst_pop(queue);
            printf("%lu, ", curr_node->key);
            if (curr_node->left) bst_push(queue, curr_node->left);
            if (curr_node->right) bst_push(queue, curr_node->right);
            level_size--;
        }
        printf("\n");
        level++;
    }
    free(queue);
}

// queue implementation
bst_t* bst_peek(bst_queue_t* queue){
    if (!queue->head){
        return NULL;
    }
    return queue->head->val;
}

bst_t* bst_pop(bst_queue_t* queue){
    if (!queue->head){
        fprintf(stderr, "ERROR: bst_pop operation on empty queue\n");
        exit(EXIT_FAILURE);
    }

    queue->sz--;

    bst_t* result = queue->head->val;
    list_node_t* tmp = queue->head;
    queue->head = queue->head->next;
    free(tmp);
    if (!queue->head)
        queue->tail = NULL;

    return result;
}

void bst_push(bst_queue_t* queue, bst_t* tree){
    list_node_t* tmp = malloc(sizeof(list_node_t));
    tmp->val = tree;
    tmp->next = NULL;

    queue->sz++;

    if (queue->tail)
        queue->tail->next = tmp;

    queue->tail = tmp;

    if (!queue->head)
        queue->head = tmp;
}

int bst_is_empty(bst_queue_t* queue){
    return (!queue->sz);
}

bst_queue_t* init_queue(){
    bst_queue_t* queue = malloc(sizeof(bst_queue_t));
    queue->head = NULL;
    queue->tail = NULL;
    queue->sz = 0;
    return queue;
}

void bst_free(bst_t* root){

}

