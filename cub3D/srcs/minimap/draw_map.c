/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:41:55 by abastos           #+#    #+#             */
/*   Updated: 2022/10/17 15:00:43 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw(t_ctx *c, t_drawmap draw_map, int x, int y)
{
	if ((x >= 0 && y >= 0) && (x < c->map_size_x && y < c->map_size_y))
	{
		if (c->map[y][x] == 1)
			draw_rect_dim(c, (t_rectdim){draw_map.pos_x + draw_map.draw_x,
				draw_map.pos_y + draw_map.draw_y, c->cell_map_size,
				c->cell_map_size, draw_map.pos_x, draw_map.pos_y,
				draw_map.pos_x + draw_map.width,
				draw_map.pos_y + draw_map.height, c->f_color});
		else
			draw_rect_dim(c, (t_rectdim){draw_map.pos_x + draw_map.draw_x,
				draw_map.pos_y + draw_map.draw_y, c->cell_map_size,
				c->cell_map_size, draw_map.pos_x, draw_map.pos_y,
				draw_map.pos_x + draw_map.width,
				draw_map.pos_y + draw_map.height, 0xFFFFFF});
	}
	else
		draw_rect_dim(c, (t_rectdim){draw_map.pos_x + draw_map.draw_x,
			draw_map.pos_y + draw_map.draw_y, c->cell_map_size,
			c->cell_map_size, draw_map.pos_x, draw_map.pos_y,
			draw_map.pos_x + draw_map.width,
			draw_map.pos_y + draw_map.height, 0x000});
}

static void	draw_cells(t_ctx *c, t_drawmap draw_map)
{
	int	x;
	int	y;

	draw_map.draw_x = -c->player.size * 0.5;
	draw_map.draw_y = -c->player.size * 0.5;
	y = (int)floor((c->player.y - c->cell_size * 5) / c->cell_size);
	while (draw_map.draw_y < draw_map.height)
	{
		x = (int)floor((c->player.x - c->cell_size * 5) / c->cell_size);
		draw_map.draw_x = -c->player.size * 0.5;
		while (draw_map.draw_x < draw_map.width)
		{
			draw(c, draw_map, x, y);
			draw_map.draw_x += c->cell_map_size;
			x++;
		}
		draw_map.draw_y += c->cell_map_size;
		y++;
	}
}

void	draw_map(t_ctx *c, int pos_x, int pos_y)
{
	t_drawmap	draw_map;

	draw_map.height = c->cell_map_size * 10;
	draw_map.width = c->cell_map_size * 10;
	draw_map.weight = 4;
	draw_map.pos_x = pos_x;
	draw_map.pos_y = pos_y;
	draw_cells(c, draw_map);
	draw_grid(c, draw_map);
	draw_player(c, draw_map);
	draw_frame(c, draw_map);
}
