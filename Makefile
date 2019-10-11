CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -std=c99

PATH=src/
SRC=$(PATH)malloc.c $(PATH)utils.c $(PATH)tests.c
OBJ=$(SRC:.c=.o)

malloc:		$(OBJ)
		$(CC) $(CFLAGS) -o malloc $(OBJ)

libmalloc.so: 	$(OBJ)
		$(CC) -c -fpic $(SRC) $(CFLAGS)

clean:
		rm -f $(OBJ)
