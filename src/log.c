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

	i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		ptr = ft_strchr(environ[i], '=');
		ptr ? *ptr = 0 : 0;
		if (ft_strcmp(environ[i], "DMALLOC_PRINT_LOGS"))
			return (1);
	}
	return (open(LOGFILE, O_WRONLY | O_CREAT | O_TRUNC));
}

void		mlog(size_t size, uint8_t type, void *addr)
{
	int		fd;

	printf("LOL\n");
	fd = check_vars();
	fd = (fd == -1) ? 1 : fd;
	if (type == MALLOC)
	{
		ft_dprintf(fd, "[%s] Initiated MALLOC of %lu bytes.\n", \
				size ? "INFO" : "WARNING", size);
	}
	else if (type == FREE)
	{
		ft_dprintf(fd, "[%s] Initiated FREE of address %p.\n", \
				addr ? "INFO" : "CRITICAL", addr);
	}
	else if (type == REALLOC)
	{
		ft_dprintf(fd, "[%s] Initiated REALLOC of zone %p to %lu bytes.\n", \
				addr ? "INFO" : "CRITICAL", addr, size);
	}
}