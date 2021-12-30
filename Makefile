CC=cc
CFLAGS=-g -O0 -Wall -std=c11

hash.o: hash.c
quick_sort.o: quick_sort.c hash.o
hash_tree.o: hash.o hash_tree.c
queue.o: hash_tree.o queue.c

test_quick_sort.o: test_quick_sort.c quick_sort.o hash.o
test_hash.o: test_hash.c hash.o quick_sort.o
test_queue.o: test_queue.c hash_tree.o hash.o queue.o

test_hash: hash.o test_hash.o quick_sort.o
test_quick_sort: hash.o quick_sort.o test_quick_sort.o
test_queue: hash.o hash_tree.o queue.o test_queue.o

clean:
	rm *.o test_hash test_quick_sort
