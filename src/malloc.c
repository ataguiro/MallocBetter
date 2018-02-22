/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 14:22:19 by ataguiro          #+#    #+#             */
/*   Updated: 2018/02/22 14:11:47 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_chunks	*g_chunks;

static void	add_chunk(size_t size, void *ret)
{
	t_chunks	*ptr;
	t_chunks	*new;

	ptr = g_chunks;
	new = (t_chunks *)mmap(AL(sizeof(t_chunks)));
	new->next = NULL;
	new->size = size;
	new->free = 0;
	new->data = ret;
	if (!ptr)
		g_chunks = new;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

void		*ft_malloc(size_t size)
{
	void	*ret;

	pre_allocation();
	if (size <= TINY_LIMIT)
		ret = get_tiny(size);
	else if (size <= SMALL_LIMIT)
		ret = get_small(size);
	else
		ret = allocate_large(size);
	if (ret)
		add_chunk(size, ret);
	return (ret);
}
