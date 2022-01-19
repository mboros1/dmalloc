#include "dmalloc.h"
#include <string.h>
// Detect wild free after memory stamping

int main() {
    char* a = (char*) malloc(200);
    char* b = (char*) malloc(50);
    char* c = (char*) malloc(200);
    char* p = (char*) malloc(3000);
    (void) a, (void) c;
    memcpy(p, b-200, 450);
    free(b);
    memcpy(b-200, p, 450);
    free(b);
    free(a);free(c);free(p);
}
