#include <stdlib.h>
typedef struct	test
{
	int			data;
	struct test	*next;
}				t;

void blah(t *ptr)
{
	t *tmp;

	tmp = ptr;
	while (tmp)
	{
		printf("%d\n", tmp->data);
		tmp = tmp->next;
	}
}

void add(t *ptr, int a)
{
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = (t *)malloc(sizeof(ptr));
	ptr->next->data = a;
	ptr->next->next = NULL;
}

int main()
{
	t *lol;

	lol = (t *)malloc(sizeof(lol));
	lol->data = 1;
	lol->next = NULL;
	add(lol, 2);
	add(lol, 3);
	add(lol, 4);
	blah(lol);
	blah(lol);
	blah(lol);
}
