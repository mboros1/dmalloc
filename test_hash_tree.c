#include "hash_tree.h"
#include <assert.h>

int main(){
    printf("initializing new tree\n");
    hashtree_t* root = ht_init();
    for(int i = 1; i <= 1000; ++i){
        val_t v = {i,i};
        ht_ins(root, v);
    }
    ht_print(root);
    printf("de-allocating tree\n");
    ht_free(root);

    printf("re-initializing new tree\n");
    root = ht_init();
    for(int i = 1; i <= 10; ++i){
        val_t v = {i, i};
        ht_ins(root, v);
    }

    for(int i = 0; i <= 10; ++i){
        hashtree_t* tmp = ht_get(root, i);
        assert(tmp != NULL);
    }

    for(int i = 2; i <= 10; i+=2){
        val_t v = {i,i};
        ht_del(root, v);
    }

    for(int i = 1; i <= 10; ++i){
        hashtree_t* tmp = ht_get(root, i);
        if (i % 2 == 0)
            assert(tmp == NULL);
        else
            assert(tmp != NULL);
    }
    ht_print(root);
    ht_free(root);
}
