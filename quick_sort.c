#include "quick_sort.h"

void swap(key_t *arr, int num1, int num2){
    key_t tmp = arr[num1];
    arr[num1] = arr[num2];
    arr[num2] = tmp;
}

int less(key_t key1, key_t key2){
    if (key1.h1 < key2.h1)
        return 1;
    
    if (key1.h1 == key2.h1 && key1.h2 < key2.h2)
        return 1;
    
    return 0;
}

int greater(key_t key1, key_t key2){
    if (key1.h1 > key2.h1)
        return 1;

    if (key1.h1 == key2.h1 && key1.h2 > key2.h2)
        return 1;
    
    return 0;
}

int partition(key_t *arr, int left, int right){
    key_t pivot = arr[right];
    int i = left-1;
    for(int j = left; j <= right-1; ++j){
        if (less(arr[j], pivot)){
            i++;
            swap(arr,i,j);
        }
    }
    swap(arr, i+1, right);
    return i+1;
}

void quick_sort(key_t *arr, int left, int right){
    if (left < right){
        int pi = partition(arr, left, right);
        quick_sort(arr, left, pi-1);
        quick_sort(arr, pi+1, right);
    }
}
