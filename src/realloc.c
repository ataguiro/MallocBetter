/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 14:02:03 by ataguiro          #+#    #+#             */
/*   Updated: 2018/03/07 17:34:24 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int	check_resize(t_chunks *ptr, void *addr, size_t size)
{
	size_t	max_possible;

	while (ptr)
	{
		if (ptr->data == addr)
		{
			if (ptr->next)
			{
				max_possible = (ptr->next->data) - (addr);
				if (size < max_possible)
				{

				}
			}
		}
	}
}

static int	try_to_resize(t_zone *zone, void *ptr, size_t size)
{
	int		ret;

	ret = 1;
	while (zone)
	{
		ret = check_resize(zone->chunks, ptr, size);
	}
}

void		*realloc(void *ptr, size_t size)
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
