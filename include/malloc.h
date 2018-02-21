/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 14:30:15 by ataguiro          #+#    #+#             */
/*   Updated: 2018/02/21 15:05:40 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Include guard MALLOC_H
*/

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/types.h>
# include <sys/mman.h>

# include <unistd.h>
# include <fcntl.h>

# include "libft.h"

# define PAGE_SIZE		getpagesize()

/*
**	mmap() call parameters
*/

# define AL(x) NULL, x, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0

/*
**	TINY zone : getpagesize() * 2 (pre-allocated)
**	SMALL zone : getpagesize() * 4 (pre-allocated)
**	TINY and SMALL should contain both at least COEFF allocations.
**	TINY_LIMIT and SMALL_LIMIT are respectively
**	the max size allocation that'll fit into those zones.
*/

# define TINY			(size_t) (PAGE_SIZE * 4)
# define SMALL			(size_t) (PAGE_SIZE * 8)
# define TINY_LIMIT		(TINY / COEFF)
# define SMALL_LIMIT	(SMALL / COEFF)

/*
**	Logging defines
*/

# define LOGFILE		"/tmp/.malloc_log"

# define INFO			0b01
# define WARNING		0b10
# define CRITICAL		0b11

/*
**	s_tiny and s_small are linked lists storing pre_allocated zones
*/

typedef struct			s_tiny
{
	void				*zone;
	struct s_tiny		*next;
}						t_tiny;

typedef struct			s_small
{
	void				*zone;
	struct s_small		*next;
}						t_small;

/*
**	s_chunks is a double linked list containing information
**	on all malloc'd chunks
*/

typedef struct			s_chunks
{
	struct s_chunks		*prev;
	struct s_chunks		*next;
	t_tiny				*tiny_head;
	t_small				*small_head;
	uint64_t			size;
	uint8_t				free;
	void				*data;
}						t_chunks;

#endif
