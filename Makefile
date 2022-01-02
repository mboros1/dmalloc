CC=cc
CFLAGS=-g -O0 -Wall -std=c11

hash.o: hash.c
quick_sort.o: quick_sort.c hash.o
hash_tree.o: hash.o hash_tree.c
bst.o: hash.o bst.c
dmalloc.o: hash.o dmalloc.c hash_tree.o bst.o

test_quick_sort.o: test_quick_sort.c quick_sort.o hash.o
test_hash.o: test_hash.c hash.o quick_sort.o
test_hash_tree.o: test_hash_tree.c hash_tree.o hash.o
test_bst.o: test_bst.c bst.o hash.o

test_hash: hash.o test_hash.o quick_sort.o
test_quick_sort: hash.o quick_sort.o test_quick_sort.o
test_hash_tree: test_hash_tree.o hash.o hash_tree.o
test_bst: test_bst.o hash.o bst.o

clean:
	rm -f *.o test_hash test_quick_sort test_hash_tree
