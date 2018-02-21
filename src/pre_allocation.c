/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_allocation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:15:43 by ataguiro          #+#    #+#             */
/*   Updated: 2018/02/21 16:10:47 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_tiny	*g_tiny;
t_small	*g_small;

/*
**	Allocates TINY and SMALL zones for futures malloc calls
*/

void	pre_allocation(void)
{
	g_tiny = (t_tiny *) mmap(AL(sizeof(t_tiny)));
	g_smaller = (t_small *) mmap(AL(sizeof(t_small)));
	g_tiny->zone = mmap(AL(TINY));
	g_small->zone = mmap(AL(SMALL));
	g_tiny->next = NULL;
	g_small->next = NULL;
}
