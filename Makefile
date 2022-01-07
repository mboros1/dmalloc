CC=cc
CFLAGS= -g -O0 -Wall -std=c11
INC_DIR=./

TESTS = $(patsubst %.c, %, $(sort $(wildcard test[0-9][0-9].c)))

hash.o: hash.c
quick_sort.o: quick_sort.c hash.o
hash_tree.o: hash.o hash_tree.c
bst.o: hash.o bst.c
dmalloc.o: dmalloc.c hash_tree.o bst.o

test_quick_sort.o: test_quick_sort.c quick_sort.o hash.o
test_hash.o: test_hash.c hash.o quick_sort.o
test_hash_tree.o: test_hash_tree.c hash_tree.o hash.o
test_bst.o: test_bst.c bst.o hash.o
test%.o: test%.c bst.o dmalloc.o hash_tree.o hash.o

test_hash: hash.o test_hash.o quick_sort.o
test_quick_sort: hash.o quick_sort.o test_quick_sort.o
test_hash_tree: test_hash_tree.o hash.o hash_tree.o
test_bst: test_bst.o hash.o bst.o

test01: dmalloc.o hash_tree.o bst.o hash.o test01.c
test02: dmalloc.o hash_tree.o bst.o hash.o test02.c
test03: dmalloc.o hash_tree.o bst.o hash.o test03.c
test04: dmalloc.o hash_tree.o bst.o hash.o test04.c
test05: dmalloc.o hash_tree.o bst.o hash.o test05.c
test06: dmalloc.o hash_tree.o bst.o hash.o test06.c
test07: dmalloc.o hash_tree.o bst.o hash.o test07.c
test08: dmalloc.o hash_tree.o bst.o hash.o test08.c
test09: dmalloc.o hash_tree.o bst.o hash.o test09.c
test10: dmalloc.o hash_tree.o bst.o hash.o test10.c
test11: dmalloc.o hash_tree.o bst.o hash.o test11.c
test12: dmalloc.o hash_tree.o bst.o hash.o test12.c

test_all: test_all.c

test: test_all $(TESTS)
	./test_all || rm -f tmp_test_output


clean:
	rm -f *.o test_hash test_quick_sort test_hash_tree test?? test_all
