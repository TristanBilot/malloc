#include "block_list.h"

void *new_page(int nb_pages)
{
	void *new = mmap(NULL, nb_pages * PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE
		| MAP_ANONYMOUS, -1, 0);
	if (new == MAP_FAILED)
		return NULL;
	return new;
}

struct block *divise_block(struct block *l, size_t size)
{
	/* new is the new free block at the right of the block
	** in which we'll store the data 
	*/
	struct block *new = ADDR(l + sizeof(struct block) + size); // maybe macro
	// struct block *new2 = (void *) l + sizeof(struct block) + size;
	// printf("===> (void *): %x\n", new);
	// printf("===> (addr): %p\n", new);
	new->size = l->size - size - sizeof(struct block);
	new->state = FREE;
	l->size = size;
	l->state = BUSY;
	new->next = l->next;
	l->next = new;
	return l;
}

struct block *last_block(void)
{
	struct block *iterator = list.first;
	while (iterator->next)
	{
		iterator = iterator->next;
		// printf("%p\n", iterator);
	}
	return iterator;
}

struct block *init_list(size_t first_block_size)
{
	void *page;
	int nb_needed_pages = (first_block_size / PAGE_SIZE) + 1;
	if (!(page = new_page(nb_needed_pages)))
	{
		printf("ERROR: mmap failed.");
		return NULL;
	}
	list.first = page;
	list.first->state = BUSY;
	list.size = nb_needed_pages * PAGE_SIZE;
	
	// printf("-----> %zu\n", first_block_size - sizeof(struct block));

	list.first->size = first_block_size; // - sizeof(struct block)
	printf("Taille: %zu, adress: %p\n", list.first->size, (void *) list.first);
	struct block *rest = ADDR(list.first + sizeof(struct block) + first_block_size);
	rest->size = (nb_needed_pages * PAGE_SIZE) - first_block_size - sizeof(struct block);
	rest->state = FREE;
	list.first->next = rest;
	return list.first;
}

struct block *get_first_free_block(size_t size)
{
	struct block *iterator = list.first;
	while (iterator)
	{
		// printf("%zu\n", size);
		if (iterator->state == FREE
			&& iterator->size - sizeof(struct block) >= size)
		{
			printf("TAILLE FIRST FREE_BLOCK: %zu\n", iterator->size);
			return iterator;
		}
		iterator = iterator->next;
	}
	return NULL;
}

struct block *extend_list(size_t size)
{
	printf("[+] Need a bigger block: %zu\n", size);
	struct block *last = last_block();
	// size_t size_last_free_block = last->size;
	size_t empty_free_place = last->size;
	int nb_needed_pages = ((size - empty_free_place) / PAGE_SIZE) + 1;
	
	printf("[+] Place: %zu\n", empty_free_place);
		printf("--- Last->next: %p\n", (void *) last->next);
	printf("--- Last: %p\n", (void *) last);
	printf("--- Nb pages: %d\n", nb_needed_pages);
	
	if (!(last->next = new_page(nb_needed_pages)))
	{
		printf("ERROR: mmap failed: extend_list");
		return NULL;
	}
	last->size = size;
	last->state = BUSY;
	list.size += PAGE_SIZE * nb_needed_pages;
	// if (size_last_free_block <= size + sizeof(struct block) && size_last_free_block >= size)
	// {
	// 	printf("%s\n", "ZIZI");
	// 	add_page_if_full();
	// }
	struct block *rest = ADDR(last + size + sizeof(struct block));
	rest->size = (PAGE_SIZE * nb_needed_pages) - size + empty_free_place - sizeof(struct block);
	rest->state = FREE;
	last->next = rest;
	return last;
}

int list_is_full()
{
	struct block *iterator = list.first;
	size_t cpt = 0;
	while (iterator)
	{
		cpt += iterator->size + sizeof(struct block);
		iterator = iterator->next;
	}
	return cpt == list.size;
}

int add_page_if_full()
{
	struct block *last = last_block();
	if (!(last->next = new_page(1)))
	{
		printf("ERROR: mmap failed: extend_list");
		return -1;
	}
	last->next->state = FREE;
	last->next->size = PAGE_SIZE;
	return 0;
}

void print_heap(struct list* list)
{
  // FREE start: 0x8000000, size: 0x1000
  // BUSY start: 0x8002000, size: 0x9000
  printf("\n");
  printf("--- HEAP ---\n");
  printf("\n");
  struct block* iterator = list->first;
  size_t cpt = 0;
  while (iterator != NULL) {
    printf("%s start: 0x%zX, size: 0x%zX, size: %zu\n",
           iterator->state == FREE ? "FREE" : "BUSY",
           (size_t) iterator,
           iterator->size, iterator->size);
    if (iterator->state != FREE)
    	cpt += iterator->size + sizeof(struct block);
    iterator = iterator->next;
    printf("%zu\n", list->size);
  }
  printf("°Filled size: %zu\n", cpt);
  printf("°Size of the list: %zu\n", list->size);
  printf("°Expected offset: %zu\n", list->size - cpt);
  printf("\n");
}
