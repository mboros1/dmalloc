#include "dmalloc.h"
#include <assert.h>
// test free offset of pointer

int main() {
    void* ptr = malloc(2000);
    free(ptr+128);
}
