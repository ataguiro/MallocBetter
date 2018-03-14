/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 13:04:28 by ataguiro          #+#    #+#             */
/*   Updated: 2018/03/14 14:22:22 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	show_tiny(void)
{
	t_zone		*ptr;
	t_chunks	*tmp;
	void		*addr;

	ptr = g_alloc.tiny;
	while (ptr)
	{
		tmp = ptr->chunks;
		ft_printf("TINY : %016p\n", ptr->zone - ZHS);
		while (tmp)
		{
			if (!tmp->free)
			{
				addr = tmp->data - CHS;
				ft_printf("%016p - %016p : %d octets\n", \
						addr, addr + tmp->size, tmp->size);
			}
			tmp = tmp->next;
		}
		ptr = ptr->next;
	}
}

static void	show_small(void)
{
	t_zone		*ptr;
	t_chunks	*tmp;
	void		*addr;

	ptr = g_alloc.small;
	while (ptr)
	{
		tmp = ptr->chunks;
		ft_printf("SMALL : %016p\n", ptr->zone - ZHS);
		while (tmp)
		{
			if (!tmp->free)
			{
				addr = tmp->data - CHS;
				ft_printf("%016p - %016p : %d octets\n", \
						addr, addr + tmp->size, tmp->size);
			}
			tmp = tmp->next;
		}
		ptr = ptr->next;
	}
}

static void	show_large(void)
{
	t_chunks	*ptr;
	void		*addr;

	ptr = g_alloc.large;
	if (ptr)
		ft_printf("LARGE : %016p\n", ptr->data - CHS);
	while (ptr)
	{
		addr = ptr->data - CHS;
		ft_printf("%016p - %016p : %d octets\n", \
				addr, addr + ptr->size, ptr->size);
		ptr = ptr->next;
	}
}

void		show_alloc_mem(void)
{
	show_tiny();
	show_small();
	show_large();
}
