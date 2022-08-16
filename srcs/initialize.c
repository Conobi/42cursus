/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:47:50 by conobi            #+#    #+#             */
/*   Updated: 2022/08/16 19:18:54 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**load_map(int fd)
{
	char	**map_splited;
	char	*gnl;
	char	*tmp;
	char	*rtn;

	gnl = ft_gnl(fd);
	if (!gnl)
		return (NULL);
	rtn = ft_strdup(gnl);
	while (gnl)
	{
		free(gnl);
		gnl = ft_gnl(fd);
		if (!gnl)
			break ;
		tmp = rtn;
		rtn = ft_strjoin(tmp, gnl);
		free(tmp);
	}
	map_splited = ft_split(rtn, '\n');
	free (rtn);
	return (map_splited);
}

static void	init_map(t_ctx *c)
{
	int		fd;
	int		x;
	int		y;

	fd = open("./map2", O_RDONLY);
	if (fd < 0 || !&(c->map))
		return ;
	c->map.raw = load_map(fd);
	// todo: rewrite in parsing
	y = 0;
	while (c->map.raw[y])
	{
		x = 0;
		while (c->map.raw[y][x])
		{
			if (c->map.raw[y][x] == 'N') // just for testing
			{
				c->player.x = x * CELL_SIZE;
				c->player.y = y * CELL_SIZE;
			}
			x++;
		}
		y++;
	}
	c->map.height = y;
	c->map.width = x;
	return ;
}

void	init_ctx(t_ctx *c)
{
	c->window.mlx = mlx_init();
	c->window.height = WIN_H;
	c->window.width = WIN_W;
	c->window.res = RESOLUTION;
	c->player.speed = 0;
	c->player.angle = 0;
	init_map(c);
}
