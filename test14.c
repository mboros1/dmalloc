#include "dmalloc.h"
#include <string.h>
// Detect common strcpy error

int main() {
  const char* s1 = "String to demonstrate a common error.";
  char* s1_copy = malloc(strlen(s1)); // did not allocate space for null terminator

  strcpy(s1_copy, s1);
  free(s1_copy);
}
