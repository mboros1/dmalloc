#include "dmalloc.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
// Should report no errors even if the execution is convaluted

int main() {
    for (int i = 0; i != 10; ++i) {
        int* ptr = (int*) malloc(10 * sizeof(int));
        for (int j = 0; j != 10; ++j) {
            ptr[i] = i;
        }
        free(ptr);
    }
}
