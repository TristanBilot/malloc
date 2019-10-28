#include "block_list.h"

__attribute__((visibility("hidden")))
struct block *addr(struct block *ptr, size_t size)
{
    char *tmp = (char*) ptr;
    tmp += size;
    return (struct block*)(tmp);
}

struct block *addr_ptr(void *ptr, size_t size)
{
    char *tmp = (char*) ptr;
    tmp += size;
    return (struct block*)(tmp);
}

__attribute__((visibility("default")))
void *malloc(size_t size)
{
    if (size == 0)
        return malloc(1);
    pthread_mutex_lock(&mutex);
    void *return_pointer = NULL;
    struct block *free_block = NULL;
    if (list.size == 0)
    {
        return_pointer = init_list(ALIGN(size));
        pthread_mutex_unlock(&mutex);
        return return_pointer;
    }
    else
    {
        if (!(free_block = get_first_free_block(size)))
        {
            return_pointer = extend_list(size);
            pthread_mutex_unlock(&mutex);
            return return_pointer;
        }
        else if (free_block->size > ALIGN(size) + block_size())
        {
            return_pointer = divise_block(free_block, size);
            pthread_mutex_unlock(&mutex);
            return return_pointer;
        }
        else if (free_block->size == size + block_size())
        {
            free_block->size = ALIGN(size);
            free_block->state = BUSY;
            pthread_mutex_unlock(&mutex);
            return addr(free_block, + block_size());
        }
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

__attribute__((visibility("default")))
void free(void *ptr)
{
    if (ptr == NULL)
        return;
    pthread_mutex_lock(&mutex);
    struct block *freed_block = addr_ptr(ptr, - block_size());
    freed_block->state = FREE;
    if (freed_block->next && freed_block->next->state == FREE
        && freed_block->state == FREE)
        merge(freed_block);
    pthread_mutex_unlock(&mutex);
}

__attribute__((visibility("default")))
void *realloc(void *ptr, size_t size)
{
    if (!ptr)
        return malloc(ALIGN(size));
    if (size == 0)
    {
        free(ptr);
        return NULL;
    }
    struct block *save = addr_ptr(ptr, - block_size());
    free(ptr);
    void *new_alloc = NULL;
    if (!(new_alloc = malloc(ALIGN(size))))
        return NULL;
    pthread_mutex_lock(&mutex);
    memcpy(addr_ptr(new_alloc, 0), addr(save, block_size()), ALIGN(size));
    pthread_mutex_unlock(&mutex);
    return addr_ptr(new_alloc, 0);
}

__attribute__((visibility("default")))
void *calloc(size_t nmemb, size_t size)
{
    if ((nmemb > 65535 || size > 65535) && ((size_t) - 1 / nmemb < size))
    {
        errno = ENOMEM;
        return NULL;
    }
    size_t alloc_size = (nmemb * size);
    void *ptr = malloc(ALIGN(alloc_size));
    if (!ptr)
        return NULL;
    pthread_mutex_lock(&mutex);
    void *tmp = memset(addr_ptr(ptr, 0), 0, ALIGN(alloc_size));
    pthread_mutex_unlock(&mutex);
    return tmp;
}
