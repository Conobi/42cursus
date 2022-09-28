/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 19:25:11 by conobi            #+#    #+#             */
/*   Updated: 2022/09/28 19:29:48 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*load_file(char *path)
{
	int		fd;
	char	*gnl;
	char	*tmp;
	char	*map;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		perror(NULL);
		return (NULL);
	}
	gnl = ft_gnl(fd);
	if (!gnl)
		return (NULL);
	map = ft_strdup(gnl);
	while (gnl)
	{
		free(gnl);
		gnl = ft_gnl(fd);
		if (!gnl)
			break ;
		tmp = map;
		map = ft_strjoin(tmp, gnl);
		free(tmp);
	}
	return (map);
}

int	print_err(int errno)
{
	ft_putstr_fd("cub3D: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	return (errno);
}
