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
