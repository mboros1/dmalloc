#include "dmalloc.h"

int main() {
    void* ptrs[1000];
    for (int i = 0; i != 1000; ++i) {
        ptrs[i] = malloc(i + 1);
    }
    for (int i = 0; i != 1000; ++i) {
        free(ptrs[i]);
    }
}
