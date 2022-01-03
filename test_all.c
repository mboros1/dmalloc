#include "test_runner.h"

const char* test01_str = "Memory leak address: 0x????????????, size: 1 bytes\n";


int main(){
    run_test_stderr("test01", test01_str);
}

