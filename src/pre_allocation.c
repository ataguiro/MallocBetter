/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_allocation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:15:43 by ataguiro          #+#    #+#             */
/*   Updated: 2018/02/25 17:15:51 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#define IS_TINY(x) (x <= TINY_LIMIT)
#define IS_SMALL(x) ((x > TINY_LIMIT) && (x <= SMALL_LIMIT))

/*
**	Allocates TINY and SMALL zones for futures malloc calls
*/

void	pre_allocation(size_t size)
{
	void	*tiny;
	void	*small;

	if (!g_alloc.tiny && IS_TINY(size))
	{
		tiny = mmap(AL(TINY + ZHS));
		g_alloc.tiny = (t_zone *)tiny;
		g_alloc.tiny->zone = tiny + ZHS;
		g_alloc.tiny->cursor = ZHS;
		g_alloc.tiny->next = NULL;
		g_alloc.tiny->chunks = NULL;
	}
	if (!g_alloc.small && IS_SMALL(size))
	{
		small = mmap(AL(SMALL + ZHS));
		g_alloc.small = (t_zone *)small;
		g_alloc.small->zone = small + ZHS;
		g_alloc.small->cursor = ZHS;
		g_alloc.small->next = NULL;
		g_alloc.small->chunks = NULL;
	}
}
