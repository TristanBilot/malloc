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
// 	return (void *)((int) current + sizeof(struct block));
// }





__attribute__((visibility("default")))
void *malloc(size_t __attribute__((unused)) size)
{
	struct block *free_block = NULL;
	// struct block *new2 = (void *)free_block + sizeof(struct block) + size;
	// struct block *new = (struct block*)((char*) free_block + sizeof(struct block) + size);
	
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
		else if (free_block->size > size + sizeof(struct block))
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
	list.size -= freed_block->size;
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
		return malloc(sizeof(struct block));
	}
	void *save = ptr;
	free(ptr);
	void *new_alloc = NULL;
	if (!(new_alloc = malloc(size)))
    	return NULL;
    memcpy(new_alloc, save, size);
    
    ptr = new_alloc;
    return ADDR(ptr);
}

__attribute__((visibility("default")))
void *calloc(size_t __attribute__((unused)) nmemb,
             size_t __attribute__((unused)) size)
{
	size_t alloc_size = (nmemb * size);
	void *ptr = malloc(alloc_size);
	if (!ptr)
		return NULL;
	// for (size_t i = sizeof(struct block); i < alloc_size; ++i)
	// {
	// 	((char *)ptr)[i] = 0;
	// }
    return memset(ADDR(ptr + sizeof(struct block)), 0, alloc_size);
}

int main(void)
{
	/* --- malloc() tests --- */
	// char* some_int = malloc(7000);
	// int* some_int2 = malloc(1000);
	// int* some_int103 = malloc(6000);
	// int* some_int104 = malloc(30000);
	// int* some_int105 = malloc(12345);
	// int* some_int106 = malloc(3733 - 24);
	// int* some_int107 = malloc(6000);
	// printf("\n");
	// print_heap(&list);

	// /* --- free() tests --- */
	// free(some_int2);
	// free(some_int);
	// free(some_int103);
	// free(some_int104);
	// free(some_int105);
	// free(some_int106);
	// free(some_int107);
	

	/* --- calloc() tests --- */
	printf("\n-- Call to calloc() -- \n");
	int* some_int1000 = malloc(1600);
	// int* some_int1001 = calloc(2500, 4);
	int* some_int1001 = malloc(30000);
	int* some_int1002 = malloc(30000);
	int* some_int1003 = calloc(3864 - 24, 1);
	int* some_int1004 = malloc(100000);
	// int* some_int1004 = calloc(30000, 1);
	// free(some_int1001);
	// int* some_int1002 = malloc(1600);
	// int* some_int1003 = malloc(30000);
	// int* some_int1004 = malloc(40000);


	// int* some_int1002 = malloc(600);
	// int* some_int1003 = malloc(100); // => si ajouté, bug !! certainement lié au calloc, rajouté le free block à la fin de la heap
	

	// int* some_int108 = malloc(6000);
	// int* some_int109 = malloc(6000);
	// print_heap(&list);
	/* --- realloc() tests --- */
	// printf("\n-- Call to realloc() -- \n");
	// void * p = realloc(some_int1000, 1500);
	// free(some_int1000);
	// malloc(1700);

	print_heap(&list);
	// printf("%p\n", p);


	free(some_int1000);
	free(some_int1002);
	free(some_int1003);
	free(some_int1001);
	free(some_int1004);
	// free(some_int2);
	// free(some_int);
	// free(some_int103);
	// free(some_int104);
	// free(some_int105);
	// free(some_int106);
	// free(some_int107);


	return 0;
}
