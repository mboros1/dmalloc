//
// Binary search tree, see header file for details and API description
//

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


// interface for queue used by print_tree
typedef struct list_node list_node_t;
struct list_node {
    hashtree_t* val;
    list_node_t* next;
};

typedef struct queue queue_t;
struct queue {
    size_t sz;
    list_node_t* head;
    list_node_t* tail;
};

// get the next value on the queue without destroying any data
hashtree_t* peek(queue_t* queue);

// get's the next value while moving the queue forward once
hashtree_t* pop(queue_t* queue);

// pushes a hashtree node to the end of the queue
void push(queue_t* queue, hashtree_t* tree);

// checks whether the queue is empty, returns 0 if empty and 1 if not empty
int is_empty(queue_t* queue);

// creates a new empty queue; user responsible for freeing queue
queue_t* init_queue();
// end queue interface

// prints tree by level
void print_tree(hashtree_t *tree_ptr) {
    if (!tree_ptr) return;
    queue_t* queue = init_queue();
    push(queue, tree_ptr);
    size_t level = 0;
    while(!is_empty(queue)){
        int level_size = queue->sz;
        printf("Level %lu: ", level);
        while(level_size != 0){
            hashtree_t* curr_node = pop(queue);
            printf("%lu, ", curr_node->val.ptr);
            if (curr_node->left) push(queue, curr_node->left);
            if (curr_node->right) push(queue, curr_node->right);
            level_size--;
        }
        printf("\n");
        level++;
    }
    free(queue);
}

// queue implementation
hashtree_t* peek(queue_t* queue){
    if (!queue->head){
        return NULL;
    }
    return queue->head->val;
}

hashtree_t* pop(queue_t* queue){
    if (!queue->head){
        fprintf(stderr, "ERROR: pop operation on empty queue\n");
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

void push(queue_t* queue, hashtree_t* tree){
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

int is_empty(queue_t* queue){
    return (!queue->sz);
}

queue_t* init_queue(){
    queue_t* queue = malloc(sizeof(queue_t));
    queue->head = NULL;
    queue->tail = NULL;
    queue->sz = 0;
    return queue;
}
