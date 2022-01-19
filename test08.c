
#include "dmalloc.h"
#include <assert.h>
// test invalid free

int main() {
    free((void*)32);
}
