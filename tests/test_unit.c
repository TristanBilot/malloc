#include "../src/block_list.h"

void trivial(void)
{
    void *a = malloc(500);
    void *b = malloc(500);
    free(a);
    free(b);
}

void intermediate(void)
{
    void *a = NULL;
    a = malloc(10000000);
    free(a);
}

void intermediate2(void)
{
    char *a = malloc(50);
    char *s = "This text should be the same after the realloc call.";
    for (size_t i = 0; i < 51; i++)
        a[i] = s[i];
    void *b = realloc(a, 60);
    free(b);
}

void hard(void)
{
    void *a = NULL;
    for (size_t i = 0; i < 5000; i++)
        a = malloc(i);
    free(a);
}

int main(void)
{
    trivial();
    intermediate();
    intermediate2();
    hard();
    return 0;
}
