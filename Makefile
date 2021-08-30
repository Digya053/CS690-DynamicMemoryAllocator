CC = clang
CFLAGS = -c -w -Wall 

OBJ = main

all: $(OBJ)

$(OBJ): main.o mymalloc.o
	$(CC) main.o mymalloc.o -o $(OBJ)

mymalloc.o: mymalloc.c
	$(CC) $(CFLAGS) mymalloc.c

main.o: main.c
	$(CC) $(CFLAGS) main.c

lib: main.o mymalloc.o
	ar rcs mymalloc.a main.o mymalloc.o

clean:
	rm -rf main
	rm -rf *.o
