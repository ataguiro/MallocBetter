/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tiny.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 19:05:38 by ataguiro          #+#    #+#             */
/*   Updated: 2018/02/25 19:50:17 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#define IS_TINY(x) (x <= TINY_LIMIT)
#define IS_SMALL(x) ((x > TINY_LIMIT) && (x <= SMALL_LIMIT))

int		check_tiny(t_tiny *ptr)
{
	size_t		total_size;
	t_chunks	*tmp;

	total_size = 0;
	tmp = g_chunks;
	while (tmp)
	{
		if (tmp->free && IS_TINY(tmp->size) && (tmp->data >= ptr->zone \
					&& tmp->data < (ptr->zone + ptr->cursor)))
			total_size += tmp->size;
		tmp = tmp->next;
	}
	if (total_size == ptr->cursor)
	{
		
	}
}
