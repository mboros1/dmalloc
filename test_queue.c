#include "queue.h"
#include <assert.h>

int main(){
    queue_t* queue = malloc(sizeof(queue));
    hashtree_t t1 = {{1,1},{1,1}};
    hashtree_t t2 = {{2,2},{2,2}};
    hashtree_t t3 = {{3,3},{3,3}};


    push(queue, &t1);
    push(queue, &t2);
    push(queue, &t3);

    hashtree_t* tmp = pop(queue);
    assert(tmp->key.h1 == t1.key.h1);
    tmp = pop(queue);
    assert(tmp->key.h1 == t2.key.h1);

    push(queue, &t3);
    push(queue, &t2);

    pop(queue);
    tmp = pop(queue);
    assert(tmp->key.h1 == t3.key.h1);


    push(queue, &t1);
    pop(queue);

    assert(peek(queue)->key.h1 == t1.key.h1);

    pop(queue);

    assert(0 == is_empty(queue));
}

