#define DMALLOC_DISABLE 1
#include "hash_tree.h"

const unsigned SEED = 0x123123;

hashtree_t* ht_init(){
    val_t value = {0,0};
    return ht_new(value);
}

hashtree_t *ht_ins(hashtree_t *root, val_t value) {
    hashtree_t* search_node = root;
    key_t key = hash(value.ptr, SEED);

    while (1){
        key_t search_key = search_node->key;
        if (hash_equal(key,search_key)) {
            search_node->val = value;
            return search_node;
        } else if (hash_less(key,search_key)) {
            if (!search_node->left){
                search_node->left = ht_new(value);
                return search_node->left;
            } else {
                search_node = search_node->left;
            }
        } else {
            if (!search_node->right){
                search_node->right = ht_new(value);
                return search_node->right;
            } else {
                search_node = search_node->right;
            }
        }
    }
    // shouldn't get here
    return NULL;
}

// helper function to find minimal value of subtree, for ht_del function
hashtree_t* ht_find_min(hashtree_t* root){
    if (!root)
        return NULL;

    if (root->left)
        return ht_find_min(root->left);

    return root;
}

hashtree_t* remove_node(hashtree_t* search_node){
    if (!search_node->left && !search_node->right){
        free(search_node);
        return NULL;
    } else if (!search_node->left){
        hashtree_t* tmp = search_node->right;
        free(search_node);
        return tmp;
    } else if (!search_node->right){
        hashtree_t* tmp = search_node->left;
        free(search_node);
        return tmp;
    } else {
        hashtree_t* tmp = ht_find_min(search_node->right);
        ht_del(search_node->right, tmp->val);
        return tmp;
    }

}

void ht_del(hashtree_t *root, val_t value){
    if (root == NULL) return;

    hashtree_t* search_node = root;
    key_t key = hash(value.ptr, SEED);

    while(1){
        key_t search_key = search_node->key;
        // check if in left subtree
        if (hash_less(key,search_key)){
            if (search_node->left){
                if (hash_equal(key, search_node->left->key)){
                    search_node->left = remove_node(search_node->left);
                    return;
                }
                search_node = search_node->left;
            } else {
                // not found
                return;
            }
        // check if in right subtree
        } else if (hash_greater(key,search_key)){
            if (search_node->right){
                if (hash_equal(key, search_node->right->key)){
                    search_node->right = remove_node(search_node->right);
                    return;
                }
                search_node = search_node->right;
            } else {
                // not found
                return;
            }
        } else {
            // shouldn't get here
            return;
        }
    }
}

hashtree_t* ht_get(hashtree_t* root, uintptr_t ptr){
    if (!root)
        return NULL;
    key_t key = hash(ptr, SEED);
    hashtree_t* search_node = root;
    while(1){
        key_t search_key = search_node->key;
        if (hash_less(key, search_key)){
            if (!search_node->left)
                return NULL;
            search_node = search_node->left;
        } else if (hash_greater(key, search_key)){
            if (!search_node->right)
                return NULL;
            search_node = search_node->right;
        } else {
            return search_node;
        }
    }
    // shouldn't get here
    return NULL;
}


hashtree_t *ht_new(val_t value) {
    hashtree_t* new_node = malloc(sizeof(hashtree_t));
    new_node->key = hash(value.ptr, SEED);
    new_node->val = value;
    new_node->left = new_node->right = NULL;
    return new_node;
}

void ht_free(hashtree_t *tree_ptr) {
    if (!tree_ptr) return;
    ht_free(tree_ptr->left);
    ht_free(tree_ptr->right);
    free(tree_ptr);
}


// interface for queue used by ht_print
typedef struct list_node list_node_t;
struct list_node {
    hashtree_t* val;
    list_node_t* next;
};

typedef struct queue ht_queue_t;
struct queue {
    size_t sz;
    list_node_t* head;
    list_node_t* tail;
};

// get the next value on the queue without destroying any data
hashtree_t* ht_peek(ht_queue_t* queue);

// get's the next value while moving the queue forward once
hashtree_t* ht_pop(ht_queue_t* queue);

// pushes a hashtree node to the end of the queue
void ht_push(ht_queue_t* queue, hashtree_t* tree);

// checks whether the queue is empty, returns 0 if empty and 1 if not empty
int ht_is_empty(ht_queue_t* queue);

// creates a new empty queue; user responsible for freeing queue
ht_queue_t* ht_init_queue();
// end queue interface

// prints tree by level
void ht_print(hashtree_t *tree_ptr) {
    if (!tree_ptr) return;
    ht_queue_t* queue = ht_init_queue();
    ht_push(queue, tree_ptr);
    size_t level = 0;
    while(!ht_is_empty(queue)){
        int level_size = queue->sz;
        printf("Level %lu: ", level);
        while(level_size != 0){
            hashtree_t* curr_node = ht_pop(queue);
            printf("%lu, ", curr_node->val.ptr);
            if (curr_node->left) ht_push(queue, curr_node->left);
            if (curr_node->right) ht_push(queue, curr_node->right);
            level_size--;
        }
        printf("\n");
        level++;
    }
    free(queue);
}


// print memory leak report
void ht_mem_leak_report(hashtree_t *root){
    if (!root) return;
    if (root->val.ptr){
        fprintf(stderr, "Memory leak address: %p, size: %zu bytes\n", (void*)root->val.ptr, root->val.sz);
    }
    ht_mem_leak_report(root->left);
    ht_mem_leak_report(root->right);
}
    

// queue implementation
hashtree_t* ht_peek(ht_queue_t* queue){
    if (!queue->head){
        return NULL;
    }
    return queue->head->val;
}

hashtree_t* ht_pop(ht_queue_t* queue){
    if (!queue->head){
        fprintf(stderr, "ERROR: ht_pop operation on empty queue\n");
        exit(EXIT_FAILURE);
    }

    queue->sz--;

    hashtree_t* result = queue->head->val;
    list_node_t* tmp = queue->head;
    queue->head = queue->head->next;
    free(tmp);
    if (!queue->head)
        queue->tail = NULL;

    return result;
}

void ht_push(ht_queue_t* queue, hashtree_t* tree){
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

int ht_is_empty(ht_queue_t* queue){
    return (!queue->sz);
}

ht_queue_t* ht_init_queue(){
    ht_queue_t* queue = malloc(sizeof(ht_queue_t));
    queue->head = NULL;
    queue->tail = NULL;
    queue->sz = 0;
    return queue;
}
