/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 14:30:15 by ataguiro          #+#    #+#             */
/*   Updated: 2018/02/22 16:43:11 by ataguiro         ###   ########.fr       */
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

# define COEFF 100
# define PAGE_SIZE		getpagesize()
# define ALIGN_COEFF	16
# define ALIGN(x) (x + ALIGN_COEFF) - (x % ALIGN_COEFF)

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
	uint64_t			cursor;
	void				*zone;
	struct s_tiny		*next;
}						t_tiny;

typedef struct			s_small
{
	uint64_t			cursor;
	void				*zone;
	struct s_small		*next;
}						t_small;

/*
**	s_chunks is a double linked list containing information
**	on all malloc'd chunks
**	~ 49 bytes == 392 bits
*/

typedef struct			s_chunks
{
	struct s_chunks		*next;
	uint64_t			size;
	uint8_t				free;
	void				*data;
}						t_chunks;

extern t_tiny			*g_tiny;
extern t_small			*g_small;
extern t_chunks			*g_chunks;

void					pre_allocation(void);
void					*get_tiny(size_t);
void					*get_small(size_t);
void					*allocate_large(size_t);

#endif
