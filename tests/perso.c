#include "malloc.h"

int main()
{
	malloc(12);
	malloc(4096 * 4096 );
	malloc(500);
	show_alloc_mem();
}
