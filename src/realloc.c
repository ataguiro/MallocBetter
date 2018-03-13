/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 14:02:03 by ataguiro          #+#    #+#             */
/*   Updated: 2018/03/13 16:59:16 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#define IS_TINY(x) (x <= TINY_LIMIT)
#define IS_SMALL(x) ((x > TINY_LIMIT) && (x <= SMALL_LIMIT))

#define NOT_FOUND 1

static size_t	check_resize(t_chunks *ptr, void *addr, size_t size, size_t *o)
{
	size_t	diff;

	while (ptr)
	{
		if (ptr->data == addr)
		{
			*o = ptr->size;
			if (ptr->next)
			{
				diff = (ptr->next->data) - (addr);
				if (size <= diff && \
					(IS_TINY(ptr->size) || IS_SMALL(ptr->size)))
				{
					ptr->size = size;
					return (0);
				}
			}
			return (2);
		}
		ptr = ptr->next;
	}
	return (NOT_FOUND);
}

static int		try_to_resize(t_zone *zone, void *ptr, size_t size, size_t *o)
{
	int		ret;

	ret = 1;
	while (zone)
	{
		ret = check_resize(zone->chunks, ptr, size, o);
		if (!ret)
			return (0);
		else if (2 == ret)
			return (2);
		zone = zone->next;
	}
	return (NOT_FOUND);
}

static void		*unlock_and_return(void *to_free, void *addr)
{
	safe_free(to_free);
	pthread_mutex_unlock(&g_mutex);
	return (addr);
}

void			*realloc(void *ptr, size_t size)
{
	size_t		old_size;
	void	*new_zone;
	int		ret;

	old_size = size;
	pthread_mutex_lock(&g_mutex);
	mlog(size, REALLOC, ptr);
	new_zone = NULL;
	if (!ptr || !size)
		return (unlock_and_return(ptr, safe_malloc(size)));
	ret = try_to_resize(g_alloc.tiny, ptr, size, &old_size);
	if (NOT_FOUND == ret)
		ret = try_to_resize(g_alloc.small, ptr, size, &old_size);
	if (NOT_FOUND == ret)
		ret = check_resize(g_alloc.large, ptr, size, &old_size);
	if (ret)
	{
		new_zone = (NOT_FOUND != ret) ? safe_malloc(size) : NULL;
		(ret != NOT_FOUND) ? ft_memcpy(new_zone, ptr, old_size) : 0;
		return (unlock_and_return(ptr, new_zone));
	}
	else
		return (unlock_and_return(NULL, ptr));
}
