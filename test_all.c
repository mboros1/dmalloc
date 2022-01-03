#include "test_runner.h"

const char* test01_str = "Memory leak address: 0x????????????, size: 1 bytes\n";
const char* test02_str = "No memory leaks detected\n";
#define test03_str test02_str
const char* test04_str = "ERROR: failed to allocate test04.c, 14, size 18446744073709551465\nNo memory leaks detected\n";

int main(){
    run_test_stderr("test01", test01_str);
    run_test_stderr("test02", test02_str);
    run_test_stderr("test03", test03_str);
    run_test_stderr("test04", test04_str);
}

