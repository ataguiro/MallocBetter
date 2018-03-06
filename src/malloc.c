/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 14:22:19 by ataguiro          #+#    #+#             */
/*   Updated: 2018/03/04 18:09:01 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	presets(void)
{
	g_tiny = NULL;
	g_small = NULL;
	g_large = NULL;
}

void		*malloc(size_t size)
{
	void			*ret;
	static uint8_t	flag = 1;

	size = ALIGN(size);
	if (flag)
	{
		flag = 0;
		presets();
	}
	pre_allocation(size);
	if (size <= TINY_LIMIT)
		ret = get_tiny(size);
	else if (size <= SMALL_LIMIT)
		ret = get_small(size);
	else
		ret = allocate_large(size);

	return (ret);
}
/*
int			main(void)
{*/
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
/*	
	char *p, *p1;

	p1 = ft_malloc(48);
	p = ft_malloc(0);
	ft_free(p1);
	ft_free(p);
	p = ft_malloc(2);
	p1 = ft_malloc(700000);
	ft_free(p1);
	show_alloc_mem();*/
/*	char *s;
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
	}*//*
	return (0);
}*/
