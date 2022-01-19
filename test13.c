#include "dmalloc.h"
// Detect write past end of allocation

int main() {
  int* ptr = (int*)malloc(sizeof(int) * 10);
  // this should be < not <=; classic buffer overrun
  for(int i = 0; i <= 10 ; ++i){
    ptr[i] = i;
  }
  free(ptr);
}
