#include <string.h>
#include <sys/mman.h>
#include <pthread.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <errno.h>
#include <err.h>

#define ALIGN(num)(((num) + ((sizeof(size_t)) - 1)) & ~((sizeof(size_t)) - 1))

enum block_state
{
    FREE,
    BUSY
};

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
pthread_mutex_t mutex;

void *new_page(int nb_pages);
size_t page_size(void);
size_t block_size(void);
struct block *divise_block(struct block *l, size_t size);
struct block *last_block(void);
struct block *init_list(size_t first_block_size);
struct block *get_first_free_block(size_t size);
struct block *extend_list(size_t size);
struct block *merge(struct block *block);
struct block *addr(struct block *ptr, size_t size);
struct block *addr_ptr(void *ptr, size_t size);


void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
void *calloc(size_t nmemb, size_t size);
