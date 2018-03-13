/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataguiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:24:33 by ataguiro          #+#    #+#             */
/*   Updated: 2018/03/13 17:10:32 by ataguiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int	check_vars(void)
{
	extern char	**environ;
	char		*ptr;
	int			i;

	i = -1;
	while (environ[++i])
	{
		ptr = ft_strchr(environ[i], '=');
		ptr ? *ptr = 0 : 0;
		if (!ft_strcmp(environ[i], "DMALLOC_LOGS"))
			return (1);
	}
	return (open(LOGFILE, O_WRONLY | O_CREAT | O_TRUNC, 0644));
}

static char	*get_type(int fd)
{
	time_t t;

	t = time(NULL);
	if (fd != 1)
		return ("History");
	else
		return ("Debug");
	return (NULL);
}

void		mlog(size_t size, uint8_t type, void *addr)
{
	static int		fd = -1;
	char	*s;

	fd = (-1 == fd) ? check_vars() : fd;
	fd = (-1 == fd) ? 1 : fd;
	s = get_type(fd);
	if (type == MALLOC)
	{
		ft_dprintf(fd, "%s: [%s] Initiated MALLOC of %lu bytes.\n", s, \
				size ? "INFO" : "WARNING", size);
	}
	else if (type == FREE)
	{
		ft_dprintf(fd, "%s: [%s] Initiated FREE of address %p.\n", s, \
				addr ? "INFO" : "CRITICAL", addr);
	}
	else if (type == REALLOC)
	{
		ft_dprintf(fd, "%s: [%s] Initiated REALLOC of zone %p to %lu bytes.\n", \
				s, addr ? "INFO" : "CRITICAL", addr, size);
	}
}
