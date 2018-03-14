#include "malloc.h"

int main()
{
	malloc(0);
	malloc(32);
	char *ptr = malloc(512);
	free(ptr);
	free(NULL);
//	realloc(NULL, 32);
	show_alloc_mem_ex();
	return (0);
}
