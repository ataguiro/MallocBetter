/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tl_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 19:12:21 by ataguiro          #+#    #+#             */
/*   Updated: 2018/03/26 19:16:50 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#define _BLOCK 0x811c9dc5
#define COEFF  0x01000193

size_t	tl_hash(void *ptr, size_t size)
{
	size_t	hash;
	char	*str;

	str = (char *)ptr;
	hash = _BLOCK1;
	while (size)
	{
		hash ^= *str++;
		hash *= COEFF;
		--size;
	}

	hash = (size_t)hash;
	return (hash);
}
