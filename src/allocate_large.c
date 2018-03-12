/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_large.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 14:13:08 by ataguiro          #+#    #+#             */
/*   Updated: 2018/03/04 14:53:48 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*allocate_large(size_t size)
{
	void		*ret;
	t_chunks	*ptr;
	t_chunks	*new;

	ret = mmap(AL(size));
	new = (t_chunks *)ret;
	new->next = NULL;
	new->size = size;
	new->free = 0;
	new->data = ret + CHS;
	ptr = g_alloc.large;
	if (!ptr)
		g_alloc.large = new;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	ret += CHS;
	return (ret);
}
