#include "bst.h"
#include "test_runner.h"
#include <assert.h>

bst_t* root;

void test_init(){
    root = bst_init();
}

void test_insert(){
    for(int i = 0; i <= 100000; ++i){
        int x = rand() % 100;
        ++x;
        int y = rand() % 10000;
        ++y;
        val_t v = {y,x};
        bst_ins(root, v);
    }
}

void test_fetch(){
    for(int i = 0; i < 1000; ++i){
        int x = rand() % 100;
        ++x;
        void* ptr = bst_fetch(root, x);
        assert(ptr != NULL);
    }
}

void test_fetch_specific(){
    val_t v = {1000, 1000};
    bst_ins(root, v);
    void* ptr = bst_fetch(root, 1000);
    assert((uintptr_t)ptr == 1000);
    ptr = bst_fetch(root, 1000);
    assert(ptr == NULL);
}


int main(){
    run_test(test_init);
    run_test(test_insert);
    run_test(test_fetch);
    run_test(test_fetch_specific);
}
