/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 14:22:19 by ataguiro          #+#    #+#             */
/*   Updated: 2018/02/22 17:36:19 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_chunks	*g_chunks;

static void	add_chunk(size_t size, void *ret)
{
	t_chunks	*ptr;
	t_chunks	*new;

	ptr = g_chunks;
	new = (t_chunks *)mmap(AL(sizeof(t_chunks)));
	new->next = NULL;
	new->size = size;
	new->free = 0;
	new->data = ret;
	if (!ptr)
		g_chunks = new;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

void		*ft_malloc(size_t size)
{
	void			*ret;
	static uint8_t	flag = 1;

	if (flag)
	{
		flag = 0;
		pre_allocation();
	}
	if (size <= TINY_LIMIT)
		ret = get_tiny(size);
	else if (size <= SMALL_LIMIT)
		ret = get_small(size);
	else
		ret = allocate_large(size);
	if (ret)
		add_chunk(ALIGN(size), ret);
	t_chunks *ptr = g_chunks;

	while (ptr)
	{
		//printf("next: %p\nsize: %llu\nfree: %hhu\ndata: %p\n", ptr->next, ptr->size, ptr->free, ptr->data);
		ptr = ptr->next;
	}
	return (ret);
}

int             main(void)
{
	/*char    *str, *str1, *str2;
	for (int i = 0; i < 300; i++)
		str = ft_malloc(300);
	str = ft_malloc(300);
	str = ft_malloc(300);
	str = ft_malloc(300);
	str = ft_malloc(900);
	str = ft_malloc(900);
	str = ft_malloc(900);
	str1 = ft_malloc(4);
	str2 = ft_malloc(4);
	str[0] = 'A';
	str[1] = 0;
	str1[0] = 'B';
	str1[2] = 0;
	str2[0] = 'C';
	str2[1] = 0;
	printf("%s - %s - %s\n", str, str1, str2);
	printf("%s - %s\n", str, str1);
	printf("page size : %d\n", getpagesize());
*/
	char *p, *p1;

	p = ft_malloc(31);
	p1 = ft_malloc(31);
	memset(p, 'A', 32);
	printf("p: %s\n", p);
	memset(p1, 'B', 31);
	printf("p (after fill): %s\n", p);
	return (0);
}
