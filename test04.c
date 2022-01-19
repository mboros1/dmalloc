#include "dmalloc.h"
#include <assert.h>
// Failed allocation.

int main() {
    void* ptrs[10];
    for (int i = 0; i != 10; ++i) {
        ptrs[i] = malloc(i + 1);
    }
    for (int i = 0; i != 10; ++i) {
        free(ptrs[i]);
    }
    size_t very_large_size = (size_t) -1 - 150;
    void* garbage = malloc(very_large_size);
    assert(!garbage);
    garbage = malloc((size_t)-1);
    assert(!garbage);
}
