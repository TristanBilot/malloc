CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -std=c99
DEPS=block_list.h
PATH=src/

SRC=malloc.c utils.c tests.c
OBJ=$(SRC:.c=.o)

malloc: $(OBJ)
	$(CC) $(CFLAGS) -o malloc $(OBJ)

main:
	$(CC) $(CFLAGS) -o main tests/main.c

imalloc:
	$(CC) $(CFLAGS) -o malloc src/malloc.c

project: main malloc

libmalloc.so: 	$(OBJ)
		$(CC) -c -fpic $(SRC) $(CFLAGS)

clean:
		rm -f $(OBJ)

Alibmalloc.so: $(OBJ)
	ar -cr libmalloc.so $(OBJ)
