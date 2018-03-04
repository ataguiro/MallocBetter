/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 14:03:58 by ataguiro          #+#    #+#             */
/*   Updated: 2018/03/04 19:05:34 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#define IS_TINY(x) (x <= TINY_LIMIT)
#define IS_SMALL(x) ((x > TINY_LIMIT) && (x <= SMALL_LIMIT))

static void	return_pages(void)
{
}

void		ft_free(void *ptr)
{
	t_zone	*tiny;
	t_zone	*small;


}
