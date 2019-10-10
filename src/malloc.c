#include "block_list.h"





// static struct block *get_pointer(void *ptr)
// {
// 	return (struct block *) ptr - 1;
// }

// static struct block *get_addr(void *ptr)
// {
// 	return (void *) ptr;
// }

// static struct block *addr(void *ptr)
// {
// 	return (struct block*)((char*) ptr);
// }





// static void *get_memory_block(void *current)
// {
// 	return (void *)((int) current + BLOCK_SIZE);
// }





__attribute__((visibility("default")))
void *malloc(size_t __attribute__((unused)) size)
{
	struct block *free_block = NULL;
	// struct block *new2 = (void *)free_block + BLOCK_SIZE + size;
	// struct block *new = (struct block*)((char*) free_block + BLOCK_SIZE + size);
	
	// printf("struct: %p\n", &new);
	// printf("void *: %p\n", new2);
	if (list.size == 0)
	{
		return init_list(size);
	}
	else
	{
		if (list_is_full())
		{
			printf("[+++] List full");
			add_page_if_full();
		}
		if (!(free_block = get_first_free_block(size)))
		{
			// NOT ENOUGH MEMORY SO MAKE A NEW PAGE
			return extend_list(size);
		}
		else if (free_block->size > size + BLOCK_SIZE)
		{
			// FREE BLOCK TOO BIG SO DIVISE
			printf("[+] Divison of the block: %zu\n", size);
			return divise_block(free_block, size);
		}

		else
		{
			printf("[+] Perfect block: %zu\n", size);
			printf("Taille: %zu\n", free_block->size);
			free_block->size = size; // PERFECT BLOCK
			free_block->state = BUSY;
			printf("%d",list_is_full());
			return ADDR(free_block);
		}
	}
	printf("\n");
	printf("FREE_BLOCK: %p\n", (void *)free_block);

    return NULL;
}

__attribute__((visibility("default")))
void free(void __attribute__((unused)) *ptr)
{
	struct block *freed_block = ADDR(ptr);
	freed_block->state = FREE;
	// list.size -= freed_block->size;
}

__attribute__((visibility("default")))
void *realloc(void __attribute__((unused)) *ptr,
             size_t __attribute__((unused)) size)
{
	if (!ptr)
		return malloc(size);
	if (size == 0)
	{
		free(ptr);
		return malloc(BLOCK_SIZE);
	}
	struct block *save = ADDR(ptr);
	printf("%p\n", ptr);
	free(ptr);
	void *new_alloc = NULL;
	if (!(new_alloc = malloc(size)))
    	return NULL;
    memcpy(ADDR(new_alloc + BLOCK_SIZE), ADDR(save
    	+ BLOCK_SIZE), save->size);
    return ADDR(new_alloc);
}

__attribute__((visibility("default")))
void *calloc(size_t __attribute__((unused)) nmemb,
             size_t __attribute__((unused)) size)
{
	size_t alloc_size = (nmemb * size);
	void *ptr = malloc(alloc_size);
	if (!ptr)
		return NULL;
    return memset(ADDR(ptr + BLOCK_SIZE), 0, alloc_size);
}
