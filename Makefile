CC=gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -fPIC \
         -fvisibility=hidden -fno-builtin -D_DEFAULT_SOURCE
CFLAGS += -g
LDFLAGS = -shared
TARGET_LIB = libmalloc.so
OBJS = src/malloc.o src/utils.o
CALL_LIB = libtracemalloc.so
CALL_OBJS = src/call_trace.o

SRC = src/utils.c src/malloc.c tests/test_unit.c
O = src/utils.o src/malloc.o tests/tests.o
OBJ = $(SRC:.o=.c)

.PHONY: all $(TARGET_LIB) $(CALL_LIB) trace clean

all: $(TARGET_LIB)

check: $(OBJ)
	$(CC) $(CFLAGS) -o malloc $(OBJ)

$(TARGET_LIB): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

trace: $(CALL_LIB)

$(CALL_LIB): CFLAGS += -g -fPIC -ldl
$(CALL_LIB): $(CALL_OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	$(RM) $(O) $(TARGET_LIB) $(CALL_LIB) $(OBJS)
