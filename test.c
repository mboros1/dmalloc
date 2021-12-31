#include <stdint.h>
#include <stdio.h>

static unsigned alloc_random() {
    static uint64_t x = 8973443640547502487ULL;
    x = x * 6364136223846793005ULL + 1ULL;
    return x >> 32;
}

static int incr(){
    static int x = 123;
    ++x;
    return x;
}

static struct{
    int x;
    int y;
} test_struct = {0,0};

int main(){
    printf("%u\n", alloc_random());
    printf("%u\n", alloc_random());
    printf("%u\n", alloc_random());
    printf("%u\n", alloc_random());

    printf("%d\n", incr());
    printf("%d\n", incr());
    printf("%d\n", incr());
    printf("%d\n", incr());


    printf("%d %d\n", test_struct.x, test_struct.y);
    test_struct.x++;test_struct.y++;
    printf("%d %d\n", test_struct.x, test_struct.y);
}
