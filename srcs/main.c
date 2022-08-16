/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:47:54 by abastos           #+#    #+#             */
/*   Updated: 2022/08/16 05:13:51 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	**load_map(int fd)
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

t_window	*init_window(void)
{
	t_window	*window;

	window = malloc(sizeof(t_window));
	window->mlx = mlx_init();
	window->id = mlx_new_window(window->mlx, WIN_W, WIN_H, "minimap");
	window->width = WIN_W;
	window->height = WIN_H;
	return (window);
}

t_player	*init_player(int pos_x, int pos_y, char facing)
{
	t_player	*player;

	(void)facing;
	player = malloc(sizeof(t_player));
	player->x = pos_x;
	player->y = pos_y;
	player->speed = 0;
	player->angle = 0;
	return (player);
}

t_map	*init_map(t_player *player)
{
	t_map	*map;
	int		fd;
	int		x;
	int		y;

	map = malloc(sizeof(t_map));
	fd = open("./map2", O_RDONLY);
	if (fd < 0 || !map)
		return (NULL);
	map->raw = load_map(fd);
	// todo: rewrite in parsing
	y = 0;
	while (map->raw[y])
	{
		x = 0;
		while (map->raw[y][x])
		{
			if (map->raw[y][x] == 'N') // just for testing
			{
				player->x = x * CELL_SIZE;
				player->y = y * CELL_SIZE;
			}
			x++;
		}
		y++;
	}
	map->height = y;
	map->width = x;
	return (map);
}

void	init_ctx(t_ctx *c)
{
	c->window = init_window();
	c->player = init_player(0, 0, 'N');
	c->map = init_map(c->player);
}

int	main(void)
{
	t_ctx	ctx;

	init_ctx(&ctx);
	gameloop(&ctx);
}
