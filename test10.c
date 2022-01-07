#include "dmalloc.h"
#include <assert.h>
// test double free

int main() {
    void* ptr = malloc(10);
    free(ptr);
    free(ptr);
}
