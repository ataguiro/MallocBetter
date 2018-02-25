/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tiny.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 16:12:29 by ataguiro          #+#    #+#             */
/*   Updated: 2018/02/25 15:46:07 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		*search_free_slot(size_t size)
{
	t_chunks	*ptr;
	t_chunks	*prev;
	void		*ret;
	size_t		min;

	ptr = g_chunks;
	prev = NULL;
	ret = NULL;
	min = TINY;
	while (ptr)
	{
		if (ptr->free && (size <= ptr->size) && ((ptr->size - size) < min))
		{
			prev ? prev->free = 1 : 0;
			prev = ptr;
			ptr->free = 0;
			ret = ptr->data;
			min = ABS(ptr->size - size);
		}
		ptr = ptr->next;
	}
	return (ret);
}

static void		append_zone(void)
{
	t_tiny	*ptr;
	t_tiny	*new;

	ptr = g_tiny;
	while (ptr->next)
		ptr = ptr->next;
	new = (t_tiny *)mmap(AL(sizeof(t_tiny)));
	new->zone = mmap(AL(TINY));
	new->next = NULL;
	new->cursor = 0;
	ptr->next = new;
}

void			*get_tiny(size_t size)
{
	void	*ret;
	t_tiny	*ptr;

	ptr = g_tiny;
	ret = search_free_slot(size);
	if (!ret)
	{
		while (ptr)
		{
			if ((ptr->cursor + size) <= TINY)
			{
				ret = &ptr->zone[ptr->cursor];
				ptr->cursor += size;
				break ;
			}
			if (!ptr->next)
				append_zone();
			ptr = ptr->next;
		}
	}
	return (ret);
}
