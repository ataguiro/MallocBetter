/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 14:03:58 by ataguiro          #+#    #+#             */
/*   Updated: 2018/03/07 18:16:03 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#define IS_TINY(x) (x <= TINY_LIMIT)
#define IS_SMALL(x) ((x > TINY_LIMIT) && (x <= SMALL_LIMIT))

static int	check_and_free(t_chunks *ptr, void *addr)
{
	t_chunks	*prev;

	prev = NULL;
	while (ptr)
	{
		if (ptr->data == addr)
		{
			if (IS_TINY(ptr->size) || IS_SMALL(ptr->size))
				ptr->free = 1;
			else
			{
				if (prev)
					prev->next = ptr->next;
				else
					g_large = ptr->next;
				munmap(ptr->data - CHS, ptr->size);
			}
			return (0);
		}
		prev = ptr;
		ptr = ptr->next;
	}
	return (1);
}

static int	check_zone(t_zone *zone, void *ptr)
{
	int	ret;

	ret = 1;
	while (zone)
	{
		ret = check_and_free(zone->chunks, ptr);
		if (!ret)
			break ;
		zone = zone->next;
	}
	return (ret);
}

void		free(void *ptr)
{
	t_zone	*zone;
	int		ret;

	zone = g_tiny;
	ret = check_zone(zone, ptr);
	if (ret)
	{
		zone = g_small;
		ret = check_zone(zone, ptr);
	}
	if (ret)
		ret = check_and_free(g_large, ptr);
}
