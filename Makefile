CC=cc
CFLAGS=-g -O0 -Wall

hash.o: hash.c
quick_sort.o: quick_sort.c hash.o
test_quick_sort.o: test_quick_sort.c quick_sort.o hash.o
test_hash.o: test_hash.c hash.o quick_sort.o

test_hash: hash.o test_hash.o quick_sort.o
test_quick_sort: hash.o quick_sort.o test_quick_sort.o

clean:
	rm *.o test_hash test_quick_sort
