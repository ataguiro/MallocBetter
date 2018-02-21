/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tiny.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 16:12:29 by ataguiro          #+#    #+#             */
/*   Updated: 2018/02/21 16:35:56 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	*search_free_slot(size_t size)
{
	t_chunks	*ptr;

	ptr = g_chunks;
	while (ptr)
	{
		if (ptr->free && (size <= ptr->size))
		{
			ptr->free = 0;
			return (ptr->data);
		}
		ptr = ptr->next;
	}
	return (NULL);
}

void		*get_tiny(size_t size)
{
	void	*ret;

	ret = search_free_slot(size);
	if (!ret)
	{
		
	}
	return (ret);
}
