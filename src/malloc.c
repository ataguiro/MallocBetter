/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 14:22:19 by ataguiro          #+#    #+#             */
/*   Updated: 2018/03/02 18:12:53 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	presets(void)
{
	g_tiny = NULL;
	g_small = NULL;
}

void		*ft_malloc(size_t size)
{
	void			*ret;
	static uint8_t	flag = 1;

	size = ALIGN(size);
	if (flag)
	{
		flag = 0;
		presets();
	}
	pre_allocation();
	if (size <= TINY_LIMIT)
		ret = get_tiny(size);
	else if (size <= SMALL_LIMIT)
		ret = get_small(size);
	else
		ret = allocate_large(size);
/*
	t_chunks *ptr;

	ptr = g_chunks;
	while (ptr)
	{
		printf("========================\nsize: \033[1m%zu\033[0m\nfree: %s\ndata: %p\n========================\n||||||||||||||||||||||||\n", ptr->size, ptr->free ? "\033[1;32mYES\033[0m" : "\033[1;31mNO\033[0m", ptr->data);
		ptr = ptr->next;
	}
	printf("\n\n\n");*/
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
	printf("p (after fill): %s\n", p);/*
	char *s;
	for (int i = 0; i < 5000; i++)
	{
		s = ft_malloc(11);
		s[0] = 'A';
		s[1] = 0;
		//printf("%s\n", s);
	}
	for (int j = 0; j < 5000; j++)
	{
		s = ft_malloc(SMALL_LIMIT);
		s[0] = 'A';
		s[1] = 0;
	}
	return (0);*/
}
