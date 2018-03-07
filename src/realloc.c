/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 14:02:03 by ataguiro          #+#    #+#             */
/*   Updated: 2018/03/07 18:16:00 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static size_t	check_resize(t_chunks *ptr, void *addr, size_t size)
{
	size_t	diff;

	while (ptr)
	{
		if (ptr->data == addr)
		{
			if (ptr->next)
			{
				diff = (ptr->next->data) - (addr);
				if (size <= diff)
				{
					diff = ptr->size - size;
					ptr->size = size;
					return (diff);
				}
				else
					return (0);
			}
		}
	}
}

static int		try_to_resize(t_zone *zone, void *ptr, size_t size)
{
	int		ret;

	ret = 1;
	while (zone)
	{
		ret = check_resize(zone->chunks, ptr, size);
		if (ret)
		{
			zone->cursor += ret;
			return (0);
		}
		zone = zone->next;
	}
	return (1);
}

void			*realloc(void *ptr, size_t size)
{
	int		ret;
	t_zone	*zone;

	zone = g_tiny;
	ret = try_to_resize(zone, ptr, size);
	if (ret)
	{
		zone = g_small;
		ret = try_to_resize(zone, ptr, size);
	}
}
