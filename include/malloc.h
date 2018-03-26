/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 14:30:15 by ataguiro          #+#    #+#             */
/*   Updated: 2018/03/26 19:17:03 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Include guard MALLOC_H
*/

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/types.h>
# include <sys/mman.h>

# include <stdint.h>
# include <unistd.h>
# include <fcntl.h>

# include <pthread.h>

# include "libft.h"

# define COEFF 200
# define PAGE_SIZE		getpagesize()
# define CHS sizeof(t_chunks)
# define ZHS sizeof(t_zone)

# define ALIGN_MOD(x) ((x % 16) || !x) ? (x + 16) - (x % 16) : x
# define ALIGN(x) ALIGN_MOD((x + CHS))

/*
**	mmap() call parameters
*/

# define AL(x) NULL, x, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0

/*
**	TINY zone : getpagesize() * 16 (pre-allocated)
**	SMALL zone : getpagesize() * 128 (pre-allocated)
**	TINY and SMALL should contain both at least COEFF allocations.
**	TINY_LIMIT and SMALL_LIMIT are respectively
**	the max size allocation that'll fit into those zones.
*/

# define TINY			(size_t)(PAGE_SIZE * 16 * 1024)
# define SMALL			(size_t)(PAGE_SIZE * 128 * 1024)
# define TINY_LIMIT		(TINY / COEFF)
# define SMALL_LIMIT	(SMALL / COEFF)

/*
**	Logging defines
*/

# define LOGFILE		"/tmp/.malloc_log"

# define INFO			0b01
# define WARNING		0b10
# define CRITICAL		0b11

# define MALLOC		1
# define FREE		2
# define REALLOC	3

/*
**	s_chunks is a double linked list containing information
**	on all malloc'd chunks
**	~ 49 bytes == 392 bits
*/

typedef struct			s_chunks
{
	size_t				checksum_begin;
	struct s_chunks		*next;
	size_t				size;
	uint8_t				free;
	void				*data;
	size_t				checksum_end;
}						t_chunks;

/*
**	s_tiny and s_small are linked lists storing pre_allocated zones
*/

typedef struct			s_zone
{
	struct s_zone		*next;
	struct s_chunks		*chunks;
	uint64_t			cursor;
	void				*zone;
}						t_zone;

typedef struct			s_alloc
{
	t_zone				*tiny;
	t_zone				*small;
	t_chunks			*large;
}						t_alloc;

extern t_alloc			g_alloc;
extern pthread_mutex_t	g_mutex;

void					*malloc(size_t size);
void					*calloc(size_t nelem, size_t size);
void					*realloc(void *ptr, size_t size);
void					*reallocf(void *ptr, size_t size);
void					free(void *ptr);

/*
**	For thread safety
*/

void					*safe_malloc(size_t size);
void					safe_free(void *ptr);

void					pre_allocation(size_t size);
void					*get_tiny(size_t size);
void					*get_small(size_t size);
void					*allocate_large(size_t size);
void					show_alloc_mem(void);
void					show_alloc_mem_ex(void);

void					mlog(size_t size, uint8_t type, void *addr);

/*
**	Hash function
*/

size_t					tl_hash(void *ptr, size_t size);

#endif
