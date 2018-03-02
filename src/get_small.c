/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_small.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 16:12:29 by ataguiro          #+#    #+#             */
/*   Updated: 2018/02/25 17:45:33 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		*best_fit(size_t size, t_chunks *ptr)
{
	size_t		min;
	void		*ret;
	t_chunks	*prev;

	ret = NULL;
	prev = NULL;
	min = SMALL;
	while (ptr)
	{
		if (ptr->free && (size <= ptr->size) && ((ptr->size - size) < min))
		{
			prev ? prev->free = 1 : 0;
			prev = ptr;
			ptr->free = 0;
			ret = ptr->data;
			min = ptr->size - size;
		}
		ptr = ptr->next;
	}
	return (ret);
}

static void		*search_free_slot(size_t size)
{
	t_zone		*zone_ptr;
	t_chunks	*chunks_ptr;
	void		*ret;

	zone_ptr = g_small;
	while (zone_ptr)
	{
		chunks_ptr = zone_ptr->chunks;
		ret = best_fit(size, chunks_ptr);
		if (ret)
			break ;
		zone_ptr = zone_ptr->next;
	}
	return (ret);
}

static void		append_zone(void)
{
	t_zone	*new;
	t_zone	*ptr;
	void	*new_zone;

	ptr = g_small;
	while (ptr->next)
		ptr = ptr->next;
	new_zone = mmap(AL(SMALL + ZHS));
	new = (t_zone *)new_zone;
	new->zone = new_zone + ZHS;
	new->cursor = ZHS;
	new->next = NULL;
	new->chunks = NULL;
	ptr->next = new;
}

static void		add_chunk(void *ret, size_t size)
{
	t_chunks	*new;
	t_chunks	*tmp;
	t_zone		*ptr;

	new = ret;
	new->size = size;
	new->free = 0;
	new->data = ret + CHS;
	ptr = g_small;
	while (ptr->next)
		ptr = ptr->next;
	if (!ptr->chunks)
		ptr->chunks = new;
	else
	{
		tmp = ptr->chunks;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void			*get_small(size_t size)
{
	void	*ret;
	t_zone	*ptr;

	ptr = g_small;
	if ((ret = search_free_slot(size)))
		return (ret);
	while (ptr)
	{
		if ((ptr->cursor + size) <= SMALL)
		{
			ret = &ptr->zone[ptr->cursor];
			add_chunk(ret, size);
			ret += CHS;
			ptr->cursor += size;
			break ;
		}
		if (!ptr->next)
			append_zone();
		ptr = ptr->next;
	}
	return (ret);
}
