#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


#define run_test(f) do { \
    printf("Running " #f "..."); \
    f(); \
    printf(" Passed\n"); \
} while(0);

#define run_test_stderr(f,s) do { \
    printf("Running " f "..."); \
    system("./" f " 2> tmp_test_output"); \
    int n = strlen(s); \
    int c; \
    FILE* file_ptr = fopen("tmp_test_output", "r"); \
    for(int i = 0; i < n; ++i){ \
        assert((c=fgetc(file_ptr)) != EOF); \
        if (s[i] != '?') \
            assert(s[i] == c); \
    } \
    assert(fgetc(file_ptr) == EOF); \
    printf(" Passed\n"); \
    remove("tmp_test_output"); \
} while(0);


#endif

