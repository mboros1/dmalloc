#include "hash_tree.h"
#include <assert.h>
#include "test_runner.h"

static hashtree_t* root;

void test_init_tree(){
    root = ht_init();
    for(int i = 1; i <= 1000; ++i){
        val_t v = {i,i};
        ht_ins(root, v);
    }
}

void test_free_and_init(){
    ht_free(root);
    root = ht_init();
    for(int i = 1; i <= 10; ++i){
        val_t v = {i, i};
        ht_ins(root, v);
    }
}

void test_get(){
    for(int i = 0; i <= 10; ++i){
        hashtree_t* tmp = ht_get(root, i);
        assert(tmp != NULL);
    }
}

void test_del(){
    for(int i = 2; i <= 10; i+=2){
        val_t v = {i,i};
        ht_del(root, v);
    }
}

void test_get_after_del(){
    for(int i = 1; i <= 10; ++i){
        hashtree_t* tmp = ht_get(root, i);
        if (i % 2 == 0)
            assert(tmp == NULL);
        else
            assert(tmp != NULL);
    }
}

int main(){
    run_test(test_init_tree);
    run_test(test_free_and_init);
    run_test(test_get);
    run_test(test_del);
    run_test(test_get_after_del);
}
