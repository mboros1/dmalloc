#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#define run_test(f) do { \
    printf("Running " #f "..."); \
    f(); \
    printf(" Passed\n"); \
} while(0);

#endif

