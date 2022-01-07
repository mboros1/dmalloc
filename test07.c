
#include "dmalloc.h"
#include <assert.h>
// test calloc

const char data[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int main() {
    char* p = (char*) calloc(10,1);
    assert(p != NULL);
    assert(memcmp(data, p, 10) == 0);
    free(p);
}
