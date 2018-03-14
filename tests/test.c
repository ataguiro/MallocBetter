#include "malloc.h"

int main()
{
	char *ptr1 = malloc(0);
	char *ptr2 = malloc(64);
	char *ptr3 = malloc(512);
	free(ptr3);
	show_alloc_mem_ex();
}
