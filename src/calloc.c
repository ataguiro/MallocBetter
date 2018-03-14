/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:24:12 by ataguiro          #+#    #+#             */
/*   Updated: 2018/03/14 13:59:47 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*calloc(size_t nelem, size_t size)
{
	void	*ptr;

	ptr = malloc(nelem * size);
	if (ptr)
		ft_memset(ptr, 0, nelem * size);
	return (ptr);
}
