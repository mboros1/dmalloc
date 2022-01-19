
#include "dmalloc.h"
#include <assert.h>
#include <stdio.h>

int main(){
    void* p = malloc(1);
    free(p);
}
