#include "test_runner.h"

const char*test_strs[]={
    "Memory leak address: 0x????????????, size: 1 bytes\n",
    "No memory leaks detected\n",
    "No memory leaks detected\n",
    "ERROR: failed to allocate test04.c:14, size 18446744073709551465\nNo memory leaks detected\n",
    "Memory leak address: 0x????????????, size: ? bytes\nMemory leak address: 0x????????????, size: ? bytes\nMemory leak address: 0x????????????, size: ? bytes\nMemory leak address: 0x????????????, size: ? bytes\n",
    "No memory leaks detected\n",
    "No memory leaks detected\n",
    "ERROR: wild free, 0x20, test08.c:7\n",
    "No memory leaks detected\n",
    "ERROR: wild free, 0x????????????, test10.c:8\nNo memory leaks detected\n",
    "ERROR: wild free, 0x?????????, test11.c:7\nMemory leak address: 0x?????????, size: 2000 bytes\n",
    "No memory leaks detected\n"
};

int main(){
    run_test_stderr("test01", test_strs[0]);
    run_test_stderr("test02", test_strs[1]);
    run_test_stderr("test03", test_strs[2]);
    run_test_stderr("test04", test_strs[3]);
    run_test_stderr("test05", test_strs[4]);
    run_test_stderr("test06", test_strs[5]);
    run_test_stderr("test07", test_strs[6]);
    run_test_stderr("test08", test_strs[7]);
    run_test_stderr("test09", test_strs[8]);
    run_test_stderr("test10", test_strs[9]);
    run_test_stderr("test11", test_strs[10]);
    run_test_stderr("test12", test_strs[11]);
}

