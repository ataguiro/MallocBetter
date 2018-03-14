/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 14:22:19 by ataguiro          #+#    #+#             */
/*   Updated: 2018/03/14 14:21:26 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;
t_alloc			g_alloc = {NULL, NULL, NULL};

void		*safe_malloc(size_t size)
{
	void			*ret;

	size = ALIGN(size);
	pre_allocation(size);
	mlog(size, MALLOC, NULL);
	if (size <= TINY_LIMIT)
		ret = get_tiny(size);
	else if (size <= SMALL_LIMIT)
		ret = get_small(size);
	else
		ret = allocate_large(size);
	return (ret);
}

void		*malloc(size_t size)
{
	void			*ret;

	pthread_mutex_lock(&g_mutex);
	size = ALIGN(size);
	pre_allocation(size);
	mlog(size, MALLOC, NULL);
	if (size <= TINY_LIMIT)
		ret = get_tiny(size);
	else if (size <= SMALL_LIMIT)
		ret = get_small(size);
	else
		ret = allocate_large(size);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}
