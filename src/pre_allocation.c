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

t_zone	*g_tiny;
t_zone	*g_small;

/*
**	Allocates TINY and SMALL zones for futures malloc calls
*/

void	pre_allocation(void)
{
	void	*tiny;
	void	*small;

	if (!g_tiny)
	{
		tiny = mmap(AL(TINY + ZHS));
		g_tiny = (t_zone *)tiny;
		g_tiny->zone = tiny + ZHS;
		g_tiny->cursor = ZHS;
		g_tiny->next = NULL;
		g_tiny->chunks = NULL;
	}
	if (!g_small)
	{
		small = mmap(AL(SMALL + ZHS));
		g_small = (t_zone *)small;
		g_small->zone = small + ZHS;
		g_small->cursor = ZHS;
		g_small->next = NULL;
		g_small->chunks = NULL;
	}
}
