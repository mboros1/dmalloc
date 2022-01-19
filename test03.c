#include "dmalloc.h"

int main() {
    void* ptrs[5];
    for (int i = 0; i != 5; ++i) {
        ptrs[i] = malloc(i + 1);
    }
    for (int i = 0; i != 5; ++i) {
        free(ptrs[i]);
    }
}
