#include "dmalloc.h"
#include <string.h>
// Detect wild free after memory stamping

int main() {
    char* a = malloc(200);
    char* b = malloc(100);
    char* c = malloc(200);
    char* p = malloc(500);
    (void) a, (void) c;
    memcpy(p, b - 200, 500);
    free(a);free(b);free(c);free(p);
    free(p + 200);
}
