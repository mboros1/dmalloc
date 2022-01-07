#include "dmalloc.h"
#include <assert.h>
#include <string.h>
// test that freed pointers are being re-used

int main() {
    void* ptrs[10];
    void* ptrs2[10];
    memset(ptrs, 0x0, 10);
    memset(ptrs2, 0x0, 10);

    for(int i = 0; i < 10; ++i){
        ptrs[i] = malloc(1);
        ptrs2[i] = ptrs[i];
    }

    for(int i = 0; i < 10; ++i)
        free(ptrs[i]);

    for(int i = 0; i < 10; ++i){
        ptrs[i] = malloc(1);
    }

    for(int i = 0; i < 10; ++i){
        int found = 0;
        for(int j = 0; j < 10; ++j){
            if (ptrs[i] == ptrs2[j]){
                found = 1;
                break;
            }
        }
        if (!found)
            assert(0);
    }
    for(int i = 0; i < 10; ++i)
        free(ptrs[i]);
}
