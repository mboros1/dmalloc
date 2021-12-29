#include "quick_sort.h"
#include <stdio.h>

key_t keys[] = { {4,4}, {2,2}, {3,3}, {1,1}};

int main(){
    printf("keys: ");
    for(int i = 0; i < 4; ++i){
        printf("{%llu,%llu}, ", keys[i].h1, keys[i].h2);
    }
    printf("\n");
    quick_sort(keys, 0, 3);
    printf("keys: ");
    for(int i = 0; i < 4; ++i){
        printf("{%llu,%llu}, ", keys[i].h1, keys[i].h2);
    }
    printf("\n");

}
