#include "hash_tree.h"

int main(){
    hashtree_t* root = NULL;
    for(int i = 1; i <= 1000; ++i){
        val_t v = {i,i};
        if (!root)
            root = insert(root,v);
        else
            insert(root, v);
    }
    print_tree(root);
}
