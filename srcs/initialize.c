/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:47:50 by conobi            #+#    #+#             */
/*   Updated: 2022/09/08 18:57:22 by conobi           ###   ########lyon.fr   */
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
	x = 0;
	y = 0;
	while (c->map.raw[y])
	{
		x = 0;
		while (c->map.raw[y][x])
		{
			if (c->map.raw[y][x] == 'N') // just for testing
			{
				c->player.x = x * c->map.cell_size;
				c->player.y = y * c->map.cell_size;
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
	c->window.height = 720;
	c->window.width = 720;
	c->window.res = 3;
	c->player.speed = 0;
	c->player.angle = 0;
	c->player.size = 8;
	c->player.fov = 60;
	c->map.cell_size = 20;
	c->rays_num = 8;
	c->target_speed = 2;
	c->tick = 60;
	init_map(c);
}
