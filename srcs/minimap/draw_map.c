/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:41:55 by abastos           #+#    #+#             */
/*   Updated: 2022/10/13 15:06:16 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map(t_ctx *c, t_rmap rmap)
{
	int	x;
	int	y;
	int	cell_size;

	cell_size = c->cell_map_size * c->window.res;
	y = 0;
	while (y < c->map_size_y)
	{
		x = 0;
		while (x < c->map_size_x)
		{
			if (c->map[y][x] == 1)
			{
				draw_rect(c, (t_rect){
					rmap.pos_x + x * cell_size,
					rmap.pos_y + y * cell_size,
					cell_size,
					cell_size,
					0x21D075
				});
			}
			else if (c->map[y][x] == 0)
			{
				draw_rect(c, (t_rect){
					rmap.pos_x + x * cell_size,
					rmap.pos_y + y * cell_size,
					cell_size,
					cell_size,
					0xFFFFFF
				});
			}
			if (y == c->map_size_y - 1)
			{
				draw_line(c, (t_line){
					x * cell_size + rmap.pos_x,
					0,
					x * cell_size + rmap.pos_x,
					c->map_size_y * cell_size,
					0x00
				});
			}
			if (x == c->map_size_x - 1)
			{
				draw_line(c, (t_line){
					0,
					y * cell_size + rmap.pos_x,
					c->map_size_x * cell_size,
					y * cell_size + rmap.pos_x,
					0x00
				});
			}
			x++;
		}
		y++;
	}
	draw_line(c, (t_line){
		c->player.x / (c->cell_size / c->cell_map_size) * c->window.res + rmap.pos_x,
		c->player.y / (c->cell_size / c->cell_map_size) * c->window.res + rmap.pos_y,
		(c->player.x / (c->cell_size / c->cell_map_size) + cos(c->player.angle) * (c->player.size * 2)) * c->window.res,
		(c->player.y / (c->cell_size / c->cell_map_size) + sin(c->player.angle) * (c->player.size * 2)) * c->window.res,
		0xFF00FF
	});
	draw_rect(c, (t_rect){
		rmap.pos_x + c->player.x / (c->cell_size / c->cell_map_size) * c->window.res - c->player.size * 0.5,
		rmap.pos_y + c->player.y / (c->cell_size / c->cell_map_size) * c->window.res - c->player.size * 0.5,
		c->player.size,
		c->player.size,
		0x03f4fc
	});
	x = -1;
	while (++x < 12)
	{
		if (x == 11 || x == 0 || x == 1)
			draw_line(c, (t_line){
				c->player.x / (c->cell_size / c->cell_map_size) * c->window.res + rmap.pos_x,
				c->player.y / (c->cell_size / c->cell_map_size) * c->window.res + rmap.pos_y,
				c->player.hitboxes[x].x_hit / (c->cell_size / c->cell_map_size) * c->window.res + rmap.pos_x,
				c->player.hitboxes[x].y_hit / (c->cell_size / c->cell_map_size) * c->window.res + rmap.pos_y,
				0x3255FF
			});
		if (x == 2 || x == 3 || x == 4)
			draw_line(c, (t_line){
				c->player.x / (c->cell_size / c->cell_map_size) * c->window.res + rmap.pos_x,
				c->player.y / (c->cell_size / c->cell_map_size) * c->window.res + rmap.pos_y,
				c->player.hitboxes[x].x_hit / (c->cell_size / c->cell_map_size) * c->window.res + rmap.pos_x,
				c->player.hitboxes[x].y_hit / (c->cell_size / c->cell_map_size) * c->window.res + rmap.pos_y,
				0xFF5532
			});
		if (x == 5 || x == 6 || x == 7)
			draw_line(c, (t_line){
				c->player.x / (c->cell_size / c->cell_map_size) * c->window.res + rmap.pos_x,
				c->player.y / (c->cell_size / c->cell_map_size) * c->window.res + rmap.pos_y,
				c->player.hitboxes[x].x_hit / (c->cell_size / c->cell_map_size) * c->window.res + rmap.pos_x,
				c->player.hitboxes[x].y_hit / (c->cell_size / c->cell_map_size) * c->window.res + rmap.pos_y,
				0x881099
			});
		if (x == 8 || x == 9 || x == 10)
			draw_line(c, (t_line){
				c->player.x / (c->cell_size / c->cell_map_size) * c->window.res + rmap.pos_x,
				c->player.y / (c->cell_size / c->cell_map_size) * c->window.res + rmap.pos_y,
				c->player.hitboxes[x].x_hit / (c->cell_size / c->cell_map_size) * c->window.res + rmap.pos_x,
				c->player.hitboxes[x].y_hit / (c->cell_size / c->cell_map_size) * c->window.res + rmap.pos_y,
				0x55FF55
			});

	}
}
