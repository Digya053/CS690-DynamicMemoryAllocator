CC = gcc
CFLAGS = -c -w -Wall 

mymalloc.o: mymalloc.c mymalloc.h
	$(CC) $(CFLAGS) mymalloc.c

main.o: main.c mymalloc.h
	$(CC) $(CFLAGS) main.c

lib: main.o mymalloc.o
	ar rcs mymalloc.a main.o mymalloc.o

main: main.o mymalloc.a
	$(CC) main.o mymalloc.a -o main

clean:
	rm -rf main
	rm -rf *.o
	rm -rf *.a
