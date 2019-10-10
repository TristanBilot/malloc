#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <pthread.h>
#include <stdint.h>
#include <stddef.h>

#define PAGE_SIZE 4096
#define BLOCK_SIZE sizeof(struct block)
#define ADDR(ptr) (struct block*)((char*) ptr)
#define ALIGN(num, align)(((num) + ((align) - 1)) & ~((align) - 1))

enum block_state
{
	FREE,
	BUSY
};

/* 24 Bytes of metadata */
struct block
{
	struct block *next;
	size_t size;
	enum block_state state;
};

struct list
{
	struct block *first;
	size_t size;
};

struct list list;

void *new_page(int nb_pages);
struct block *divise_block(struct block *l, size_t size);
struct block *last_block(void);
struct block *init_list(size_t first_block_size);
struct block *get_first_free_block(size_t size);
struct block *extend_list(size_t size);
int list_is_full();
int add_page_if_full();
void print_heap(struct list* list);

void *malloc(size_t __attribute__((unused)) size);
void free(void __attribute__((unused)) *ptr);
void *realloc(void __attribute__((unused)) *ptr,
             size_t __attribute__((unused)) size);
void *calloc(size_t __attribute__((unused)) nmemb,
             size_t __attribute__((unused)) size);
