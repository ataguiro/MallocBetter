/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 14:03:58 by ataguiro          #+#    #+#             */
/*   Updated: 2018/03/13 16:58:20 by ataguiro         ###   ########.fr       */
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
					g_alloc.large = ptr->next;
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

void		safe_free(void *ptr)
{
	t_zone	*zone;
	int		ret;

//	mlog(0, FREE, ptr);
	zone = g_alloc.tiny;
	ret = check_zone(zone, ptr);
	if (ret)
	{
		zone = g_alloc.small;
		ret = check_zone(zone, ptr);
	}
	if (ret)
		ret = check_and_free(g_alloc.large, ptr);
}

void		free(void *ptr)
{
	t_zone	*zone;
	int		ret;

	pthread_mutex_lock(&g_mutex);
//	mlog(0, FREE, ptr);
	zone = g_alloc.tiny;
	ret = check_zone(zone, ptr);
	if (ret)
	{
		zone = g_alloc.small;
		ret = check_zone(zone, ptr);
	}
	if (ret)
		ret = check_and_free(g_alloc.large, ptr);
	pthread_mutex_unlock(&g_mutex);
}
