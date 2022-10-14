/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 19:25:11 by conobi            #+#    #+#             */
/*   Updated: 2022/10/14 14:44:12 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_fd(char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		perror(NULL);
		return (-1);
	}
	return (fd);
}

int	print_err(char *line, char *err, int errno)
{
	ft_putstr_fd("cub3D: ", 2);
	if (line)
	{
		ft_putstr_fd(line, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(RED_TXT, 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd(RESET_TXT, 2);
	ft_putstr_fd("\n", 2);
	return (errno);
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

char	*nl_remove(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len >= 1 && str[len - 1] == '\n')
		str[len - 1] = '\0';
	return (str);
}
