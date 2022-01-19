#define DMALLOC_DISABLE 1
#include "quick_sort.h"

void swap(key_t *arr, int num1, int num2){
    key_t tmp = arr[num1];
    arr[num1] = arr[num2];
    arr[num2] = tmp;
}

int partition(key_t *arr, int left, int right){
    key_t pivot = arr[right];
    int i = left-1;
    for(int j = left; j <= right-1; ++j){
        if (hash_less(arr[j], pivot)){
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
