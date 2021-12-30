#ifndef QUEUE_H
#define QUEUE_H

#include "hash_tree.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct list_node list_node_t;
struct list_node {
    hashtree_t* val;
    list_node_t* next;
};

typedef struct queue queue_t;
struct queue {
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


#endif
