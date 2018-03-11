/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 14:02:03 by ataguiro          #+#    #+#             */
/*   Updated: 2018/03/11 15:50:05 by ataguiro         ###   ########.fr       */
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
					ptr->size = size;
					return (0);
				}
				else
					return (1);
			}
		}
		ptr = ptr->next;
	}
	return (1);
}

static int		try_to_resize(t_zone *zone, void *ptr, size_t size)
{
	int		ret;

	ret = 1;
	while (zone)
	{
		ret = check_resize(zone->chunks, ptr, size);
		if (!ret)
			return (0);
		zone = zone->next;
	}
	return (1);
}

void			*realloc(void *ptr, size_t size)
{
	int		ret;
	t_zone	*zone;
	void	*new_zone;

	pthread_mutex_lock(&g_mutex);
	zone = g_tiny;
	new_zone = NULL;
	if (!ptr || !size)
	{
		free(ptr);
		pthread_mutex_lock(&g_mutex);
		return (malloc(size));
	}
	ret = try_to_resize(zone, ptr, size);
	if (ret)
	{
		zone = g_small;
		ret = try_to_resize(zone, ptr, size);
	}
	if (ret)
	{
		new_zone = malloc(size);
		ft_memcpy(new_zone, ptr, size);
		free(ptr);
		pthread_mutex_lock(&g_mutex);
		return (new_zone);
	}
	else
	{
		pthread_mutex_lock(&g_mutex);
		return (ptr);
	}
}
