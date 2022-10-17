/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:41:55 by abastos           #+#    #+#             */
/*   Updated: 2022/10/17 14:09:59 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_drawmap
{
	int	width;
	int	height;
	int	weight;
	int	pos_x;
	int	pos_y;
}	t_drawmap;

static void	draw_frame(t_ctx *c, t_drawmap draw_map)
{
	draw_rect(c, (t_rect){draw_map.pos_x, draw_map.pos_y,
		draw_map.weight,
		draw_map.height, c->f_color});
	draw_rect(c, (t_rect){draw_map.pos_x + draw_map.width, draw_map.pos_y,
		draw_map.weight,
		draw_map.height, c->f_color});
	draw_rect(c, (t_rect){draw_map.pos_x, draw_map.pos_y,
		draw_map.width + draw_map.weight,
		draw_map.weight, c->f_color});
	draw_rect(c, (t_rect){draw_map.pos_x, draw_map.height + draw_map.pos_y,
		draw_map.width + draw_map.weight,
		draw_map.weight, c->f_color});
}

static void	draw_grid(t_ctx *c, t_drawmap draw_map, int cell_size)
{
	int	x;
	int	y;

	y = -c->player.size * 0.5;
	while (y < draw_map.height)
	{
		x = -c->player.size * 0.5;
		while (x < draw_map.width)
		{
			if (x > 0)
			{
				draw_line(c, (t_line){
					draw_map.pos_x + x,
					draw_map.pos_y,
					draw_map.pos_x + x,
					draw_map.pos_y + draw_map.height,
					0x000
				});
			}
			x += cell_size;
		}
		if (y > 0)
		{
			draw_line(c, (t_line){
				draw_map.pos_x,
				draw_map.pos_y + y,
				draw_map.pos_x + draw_map.width,
				draw_map.pos_y + y,
				0x000
			});
		}
		y += cell_size;
	}
}

static void	draw_player(t_ctx *c, t_drawmap draw_map)
{
	int	player_x;
	int	player_y;

	player_x = draw_map.pos_x + draw_map.width * 0.5;
	player_y = draw_map.pos_y + draw_map.height * 0.5;
	draw_line(c, (t_line){
		player_x + c->player.size * 0.5,
		player_y + c->player.size * 0.5,
		((player_x + c->player.size * 0.5) + cos(c->player.angle)
			* (c->player.size * 2)),
		((player_y + c->player.size * 0.5) + sin(c->player.angle)
			* (c->player.size * 2)),
		0xFF00FF
	});
	draw_rect(c, (t_rect){
		player_x,
		player_y,
		c->player.size,
		c->player.size,
		0x03f4fc
	});
}

typedef struct s_rectdim
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	x_min;
	int	y_min;
	int	x_max;
	int	y_max;
	int	color;
}	t_rectdim;

static void	draw_rect_dim(t_ctx *c, t_rectdim rect)
{
	int	x;
	int	y;

	y = rect.y;
	while (y < rect.y + rect.height)
	{
		x = rect.x;
		while (x < rect.x + rect.width)
		{
			if (x > rect.x_min && x < rect.x_max && y > rect.y_min && y < rect.y_max)
				pixel_put(c, x, y, rect.color);
			x++;
		}
		++y;
	}
}

static void	draw_cells(t_ctx *c, t_drawmap draw_map)
{
	int	x;
	int	y;
	int	draw_x;
	int	draw_y;
	int	cell_size;

	cell_size = c->cell_map_size;
	draw_x = -c->player.size * 0.5;
	draw_y = -c->player.size * 0.5;
	y = (int)floor((c->player.y - c->cell_size * 5) / c->cell_size);
	while (draw_y < draw_map.height)
	{
		x = (int)floor((c->player.x - c->cell_size * 5) / c->cell_size);
		draw_x = -c->player.size * 0.5;
		while (draw_x < draw_map.width)
		{
			if ((x >= 0 && y >= 0) && (x < c->map_size_x && y < c->map_size_y))
			{
				if (c->map[y][x] == 1)
				{
					draw_rect_dim(c, (t_rectdim){
						draw_map.pos_x + draw_x,
						draw_map.pos_y + draw_y,
						cell_size,
						cell_size,
						draw_map.pos_x,
						draw_map.pos_y,
						draw_map.pos_x + draw_map.width,
						draw_map.pos_y + draw_map.height,
						c->f_color
					});
				}
				else
				{
					draw_rect_dim(c, (t_rectdim){
						draw_map.pos_x + draw_x,
						draw_map.pos_y + draw_y,
						cell_size,
						cell_size,
						draw_map.pos_x,
						draw_map.pos_y,
						draw_map.pos_x + draw_map.width,
						draw_map.pos_y + draw_map.height,
						0xFFFFFF
					});
				}
			}
			else
			{
				draw_rect_dim(c, (t_rectdim){
					draw_map.pos_x + draw_x,
					draw_map.pos_y + draw_y,
					cell_size,
					cell_size,
					draw_map.pos_x,
					draw_map.pos_y,
					draw_map.pos_x + draw_map.width,
					draw_map.pos_y + draw_map.height,
					0x000
				});
			}
			draw_x += cell_size;
			x++;
		}
		draw_y += cell_size;
		y++;
	}
	draw_grid(c, draw_map, cell_size);
	draw_player(c, draw_map);
	draw_frame(c, draw_map);
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
}
