#include "queue.h"


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

    if (queue->tail)
        queue->tail->next = tmp;
    
    queue->tail = tmp;

    if (!queue->head)
        queue->head = tmp;
}

int is_empty(queue_t* queue){
    return !(!queue->head);
}

