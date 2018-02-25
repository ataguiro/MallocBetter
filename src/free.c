/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 14:03:58 by ataguiro          #+#    #+#             */
/*   Updated: 2018/02/25 16:59:19 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#define IS_TINY(x) (x <= TINY_LIMIT)
#define IS_SMALL(x) ((x > TINY_LIMIT) && (x <= SMALL_LIMIT))

static void	pop_freed(t_chunks *ptr)
{
	t_chunks *tmp;

	tmp = g_chunks;
	while (tmp->next)
	{
		if (tmp->next == ptr)
		{
			tmp->next = ptr->next;
			ptr->next = NULL;
			munmap(ptr, sizeof(t_chunks));
			break ;
		}
		tmp = tmp->next;
	}
}

static void	check_tiny(t_tiny *ptr)
{
	t_chunks	*tmp;
	t_tiny		*tiny_node;
	size_t		total_size;

	total_size = 0;
	tmp = g_chunks;
	tiny_node = g_tiny;
	while (tmp)
	{
		if (tmp->free && IS_TINY(tmp->size) && (tmp->data >= ptr->zone \
					&& tmp->data < (ptr->zone + ptr->cursor)))
			total_size += tmp->size;
		tmp = tmp->next;
	}
	printf("total_size: %zu\n", total_size);
	if (total_size == ptr->cursor)
	{
		munmap(ptr->zone, ptr->cursor);
		if (!tiny_node->next)
		{
			
		}
		while (tiny_node->next)
		{
			if (tiny_node == ptr)
			{
				tiny_node->next = ptr->next;
				munmap(ptr, sizeof(t_tiny));
				break ;
			}
			tiny_node = tiny_node->next;
		}
	}
}

static void	check_small(t_small *ptr)
{
	t_chunks	*tmp;
	t_small		*small_node;
	size_t		total_size;

	total_size = 0;
	tmp = g_chunks;
	small_node = g_small;
	while (tmp)
	{
		if (tmp->free && IS_SMALL(tmp->size) && (tmp->data >= ptr->zone \
					&& tmp->data < (ptr->zone + ptr->cursor)))
			total_size += tmp->size;
		tmp = tmp->next;
	}
	if (total_size == ptr->cursor)
	{
		munmap(ptr->zone, ptr->cursor);
		while (small_node->next)
		{
			if (small_node == ptr)
			{
				small_node->next = ptr->next;
				munmap(ptr, sizeof(t_small));
				break ;
			}
			small_node = small_node->next;
		}
	}
}

static void	return_pages(void)
{
	t_tiny	*p1;
	t_small	*p2;

	p1 = g_tiny;
	p2 = g_small;
	while (p1)
	{
		if (p1->cursor == TINY)
			check_tiny(p1);
		p1 = p1->next;
	}
	while (p2)
	{
		if (p2->cursor == SMALL)
			check_small(p2);
		p2 = p2->next;
	}
}

void		ft_free(void *ptr)
{
	t_chunks	*tmp;

	tmp = g_chunks;
	if (!ptr)
		return ;
	while (tmp)
	{
		if (tmp->data == ptr)
		{
			if (tmp->size <= SMALL_LIMIT)
			{
				tmp->free = 1;
				break ;
			}
			else
			{
				munmap(tmp->data, tmp->size);
				pop_freed(tmp);
				break ;
			}
		}
		tmp = tmp->next;
	}
	return_pages();
/*
	t_chunks *pt;

	pt = g_chunks;
	while (pt)
	{
		printf("========================\nsize: \033[1m%zu\033[0m\nfree: %s\ndata: %p\n========================\n||||||||||||||||||||||||\n", pt->size, pt->free ? "\033[1;32mYES\033[0m" : "\033[1;31mNO\033[0m", pt->data);
		pt = pt->next;
	}
	printf("\n\n\n");*/
}
