/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:41:55 by abastos           #+#    #+#             */
/*   Updated: 2022/08/26 19:47:52 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rays(t_ctx *c, t_rmap rmap)
{
	t_ray	ray;
	int		i;

	i = 0;
	while (i < c->rays_num)
	{
		ray = rmap.rays[i];
		draw_line(c, (t_line){
			c->player.x * rmap.scale + rmap.pos_x,
			c->player.y * rmap.scale + rmap.pos_y,
			(c->player.x + cos(ray.angle) * ray.distance) * rmap.scale,
			(c->player.y + sin(ray.angle) * ray.distance) * rmap.scale,
			0xFFFF00
		});
		i++;
	}
}

// printf("drawing ray %d | angle -> %f | distance %f\n",
// 	i, ray.angle, ray.distance);

//todo: add t_rays
void	draw_map(t_ctx *c, t_rmap rmap)
{
	int	x;
	int	y;
	int	cell_size;

	cell_size = c->map.cell_size * rmap.scale;
	y = 0;
	while (c->map.raw[y])
	{
		x = 0;
		while (c->map.raw[y][x])
		{
			// printf("%c ", c->map[y][x]);
			if (c->map.raw[y][x] == '1')
			{
				draw_rect(c, (t_rect){
					rmap.pos_x + x * cell_size,
					rmap.pos_y + y * cell_size,
					cell_size,
					cell_size,
					0x21D075
				});
			}
			else if (c->map.raw[y][x] == '0' || c->map.raw[y][x] == 'N')
			{
				draw_rect(c, (t_rect){
					rmap.pos_x + x * cell_size,
					rmap.pos_y + y * cell_size,
					cell_size,
					cell_size,
					0xFFFFFF
				});
			}
			else
			{
				draw_rect(c, (t_rect){
					rmap.pos_x + x * cell_size,
					rmap.pos_y + y * cell_size,
					cell_size,
					cell_size,
					0x0
				});
			}
			if (y == c->map.height - 1)
			{
				draw_line(c, (t_line){
					x * cell_size + rmap.pos_x,
					0,
					x * cell_size + rmap.pos_x,
					c->map.height * cell_size,
					0x00
				});
			}
			if (x == c->map.width - 1)
			{
				draw_line(c, (t_line){
					0,
					y * cell_size + rmap.pos_x,
					c->map.width * cell_size,
					y * cell_size + rmap.pos_x,
					0x00
				});
			}
			x++;
		}
		// printf("\n");
		y++;
	}
	draw_line(c, (t_line){
		c->player.x * rmap.scale + rmap.pos_x,
		c->player.y * rmap.scale + rmap.pos_y,
		(c->player.x + cos(c->player.angle) * (c->player.size * 2)) * rmap.scale,
		(c->player.y + sin(c->player.angle) * (c->player.size * 2)) * rmap.scale,
		0xFF00FF
	});
	draw_rect(c, (t_rect){
		rmap.pos_x + c->player.x * rmap.scale - c->player.size * 0.5,
		rmap.pos_y + c->player.y * rmap.scale - c->player.size * 0.5,
		c->player.size,
		c->player.size,
		0x03f4fc
	});
	draw_rays(c, rmap);
}
