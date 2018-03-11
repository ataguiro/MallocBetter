/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 14:22:19 by ataguiro          #+#    #+#             */
/*   Updated: 2018/03/11 18:04:47 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

static void	presets(void)
{
	g_tiny = NULL;
	g_small = NULL;
	g_large = NULL;
}

void		*malloc(size_t size)
{
	void			*ret;
	static uint8_t	flag = 1;

	pthread_mutex_lock(&g_mutex);
	size = ALIGN(size);
	if (flag)
	{
		flag = 0;
		presets();
	}
	pre_allocation(size);
	if (size <= TINY_LIMIT)
		ret = get_tiny(size);
	else if (size <= SMALL_LIMIT)
		ret = get_small(size);
	else
		ret = allocate_large(size);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}
