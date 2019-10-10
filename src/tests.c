#include "block_list.h"

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
	int* some_int1000 = malloc(500);
	int* some_int1002 = malloc(5000);
	int* some_int1001 = malloc(500);
	print_heap(&list);
	// int* some_int1001 = calloc(2500, 4);
	// int* some_int1001 = malloc(30000);
	// int* some_int1002 = malloc(30000);
	// int* some_int1003 = calloc(3864 - 24, 1);
	// int* some_int1004 = malloc(100000);
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
	printf("\n-- Call to realloc() -- \n");
	// realloc(some_int1000, 10);
	
	
	int *new = realloc(some_int1000, 12345678);
	new = realloc(new, 50000);
	new = realloc(new, 10000000);
	// malloc(1700);

	print_heap(&list);
	// printf("%p\n", p);

	// free(p);
	free(some_int1000);
	free(some_int1002);
	// free(some_int1003);
	free(some_int1001);
	// free(some_int1004);
	// free(some_int2);
	// free(some_int);
	// free(some_int103);
	// free(some_int104);
	// free(some_int105);
	// free(some_int106);
	// free(some_int107);


	return 0;
}
