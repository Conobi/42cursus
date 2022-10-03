/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 19:25:11 by conobi            #+#    #+#             */
/*   Updated: 2022/10/03 16:15:50 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	rgba2hex(int r, int g, int b, int a)
{
	return ((255 - a) << 24 | r << 16 | g << 8 | b);
}

bool	free_split(char **str_split)
{
	int	i;

	i = -1;
	if (!str_split)
		return (false);
	while (str_split[++i])
		free(str_split[i]);
	free(str_split);
	return (false);
}
