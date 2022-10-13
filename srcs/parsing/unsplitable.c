/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsplitable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:29:07 by conobi            #+#    #+#             */
/*   Updated: 2022/10/13 17:44:11 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_file_lines(char *filename)
{
	char	*line;
	int		fd;
	int		nb_lines;

	fd = load_fd(filename);
	if (fd < 0)
		return (0);
	line = ft_gnl(fd);
	nb_lines = 1;
	if (!line)
		return (0);
	while (line)
	{
		free(line);
		line = ft_gnl(fd);
		if (!line)
			break ;
		nb_lines++;
	}
	free(line);
	close(fd);
	return (nb_lines);
}

static void	push_lines(char *filename, char **str_array)
{
	int		fd;
	int		i;

	fd = load_fd(filename);
	if (fd < 0)
		return ;
	i = 0;
	str_array[i] = ft_gnl(fd);
	if (!str_array[i])
		return ;
	while (str_array[i])
	{
		i++;
		str_array[i] = ft_gnl(fd);
		if (!str_array[i])
			break ;
	}
	close(fd);
}

char	**unsplitable_file(char *filename)
{
	char	**ret;
	int		nb_lines;

	nb_lines = count_file_lines(filename);
	if (nb_lines <= 0)
		return (NULL);
	ret = ft_calloc(nb_lines + 1, sizeof(void *));
	if (!ret)
		return (NULL);
	push_lines(filename, ret);
	return (ret);
}
