#include "hash_tree.h"

int main(){
    printf("initializing new tree\n");
    hashtree_t* root = init_tree();
    for(int i = 1; i <= 1000; ++i){
        val_t v = {i,i};
        ins_node(root, v);
    }
    print_tree(root);
    printf("de-allocating tree\n");
    free_tree(root);

    printf("re-initializing new tree\n");
    root = init_tree();
    for(int i = 1; i <= 10; ++i){
        val_t v = {i, i};
        ins_node(root, v);
    }

    for(int i = 2; i <= 10; i+=2){
        val_t v = {i,i};
        del_node(root, v);
    }
    print_tree(root);
    free_tree(root);
}
