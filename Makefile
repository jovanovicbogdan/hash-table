# default: test
# 	gcc -o test ./output/test -lhashtable -L$(pwd)
# 	./test
#
# libhashtable: hash_table.c
# 	gcc -o libhashtable.so -fpic -shared hash_table.c
#
# test: test.c
# 	gcc -Wall -g test.c -o ./output/test

CC=gcc
CFLAGS=-Wall

default: app
	./output/app

app: main.o hash_table.o
	$(CC) $(CFLAGS) main.o hash_table.o -o output/app

main.o: main.c hash_table.h
	$(CC) $(CFLAGS) -c main.c

hashtable.o: hash_table.c hash_table.h
	$(CC) $(CFLAGS) -c hash_table.c

clean:
	rm -rf *.o ./output/*
