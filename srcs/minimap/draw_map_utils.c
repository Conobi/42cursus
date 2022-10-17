/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:55:30 by abastos           #+#    #+#             */
/*   Updated: 2022/10/17 14:56:26 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_frame(t_ctx *c, t_drawmap draw_map)
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

void	draw_grid(t_ctx *c, t_drawmap draw_map)
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
				draw_line(c, (t_line){draw_map.pos_x + x,
					draw_map.pos_y, draw_map.pos_x + x,
					draw_map.pos_y + draw_map.height, 0x000});
			x += c->cell_map_size;
		}
		if (y > 0)
			draw_line(c, (t_line){draw_map.pos_x,
				draw_map.pos_y + y, draw_map.pos_x + draw_map.width,
				draw_map.pos_y + y, 0x000});
		y += c->cell_map_size;
	}
}

void	draw_player(t_ctx *c, t_drawmap draw_map)
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
