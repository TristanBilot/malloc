#include "block_list.h"

__attribute__((visibility("hidden")))
size_t block_size(void)
{
    return sizeof(struct block);
}


__attribute__((visibility("hidden")))
size_t page_size(void)
{
    return (size_t) sysconf(_SC_PAGESIZE);
}

__attribute__((visibility("hidden")))
void *new_page(int nb_pages)
{
    void *new = mmap(NULL, nb_pages * page_size(), PROT_READ
        | PROT_WRITE, MAP_PRIVATE
        | MAP_ANONYMOUS, -1, 0);
    if (new == MAP_FAILED)
        return NULL;
    return new;
}

__attribute__((visibility("hidden")))
struct block *divise_block(struct block *l, size_t size)
{
    struct block *new = addr(l, block_size() + ALIGN(size));
    new->size = ALIGN(l->size) - ALIGN(size) - block_size();
    new->state = FREE;
    l->size = ALIGN(size);
    l->state = BUSY;
    new->next = l->next;
    l->next = new;
    return addr(l, block_size());
}

__attribute__((visibility("hidden")))
struct block *last_block(void)
{
    struct block *iterator = list.first;
    while (iterator->next)
        iterator = iterator->next;
    return iterator;
}

__attribute__((visibility("hidden")))
struct block *init_list(size_t first_block_size)
{
    int nb_needed_pages = (first_block_size / page_size()) + 1;
    if (first_block_size > page_size() - 2 * block_size()
        && first_block_size < page_size())
        nb_needed_pages++;
    if (!(list.first = new_page(nb_needed_pages)))
        return NULL;
    list.first->state = BUSY;
    list.size = nb_needed_pages * page_size();
    list.first->size = first_block_size;
    struct block *rest = addr(list.first, block_size() + first_block_size);
    rest->size = (nb_needed_pages * page_size()) - first_block_size - block_size();
    rest->state = FREE;
    list.first->next = rest;
    return addr(list.first, block_size());
}

__attribute__((visibility("hidden")))
struct block *merge(struct block *block)
{
    if (!block->next || !block)
        return NULL;
    struct block *next = block->next;
    block->size += next->size + block_size();
    if (next->next)
        block->next = next->next;
    else
        block->next = NULL;
    block->state = FREE;
    return block;
}

__attribute__((visibility("hidden")))
struct block *get_first_free_block(size_t size)
{
    struct block *iterator = list.first;
    while (iterator)
    {
        if (iterator->state == FREE
            && iterator->size > 2 * block_size()
            && iterator->size - 2 * block_size() >= size
            && iterator->size > block_size())
            return iterator;
        iterator = iterator->next;
    }
    return NULL;
}

__attribute__((visibility("hidden")))
struct block *extend_list(size_t size)
{
    struct block *last = last_block();
    size_t empty_free_place = last->size;
    int nb_needed_pages = ((ALIGN(size)) / page_size()) + 1;
    if (ALIGN(size) < empty_free_place
        || (ALIGN(size) > nb_needed_pages * page_size() - 2 * block_size()
        && ALIGN(size) < nb_needed_pages * page_size()))
        nb_needed_pages++;
    if (!(last->next = new_page(nb_needed_pages)))
        return NULL;
    last->next->size = ALIGN(size);
    last->next->state = BUSY;
    list.size += page_size() * nb_needed_pages;
    struct block *rest = addr(last->next, ALIGN(size) + block_size());
    rest->size = (page_size() * nb_needed_pages) - ALIGN(size) - block_size();
    rest->state = FREE;
    last->next->next = rest;
    return addr(last->next, block_size());
}
