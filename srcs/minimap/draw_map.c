/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:41:55 by abastos           #+#    #+#             */
/*   Updated: 2022/08/16 19:11:40 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rays(t_ctx *c, t_rmap rmap)
{
	t_list	*head;
	t_ray	*ray;
	int		i;

	head = rmap.rays;
	i = 0;
	while (head->next)
	{
		ray = head->content;
		if (i % 100 == 0)
		{
			draw_line(c, (t_line){
				c->player.x * rmap.scale + rmap.pos_x,
				c->player.y * rmap.scale + rmap.pos_y,
				(c->player.x + cos(ray->angle) * ray->distance) * rmap.scale,
				(c->player.y + sin(ray->angle) * ray->distance) * rmap.scale,
				0xFFFFFF
			});
			printf("drawing ray %d | angle -> %f | distance %f\n",
				i, ray->angle, ray->distance);
		}
		i++;
		head = head->next;
	}
}

//todo: add t_rays
void	draw_map(t_ctx *c, t_rmap rmap)
{
	int	x;
	int	y;
	int	cell_size;

	cell_size = CELL_SIZE * rmap.scale;
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
					0xFF
				});
			}
			else if (c->map.raw[y][x] == '0' || c->map.raw[y][x] == 'N')
			{
				draw_rect(c, (t_rect){
					rmap.pos_x + x * cell_size,
					rmap.pos_y + y * cell_size,
					cell_size,
					cell_size,
					0xFF0000
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
			// if (y == c->map->height - 1)
			// {
			// 	draw_line(c, (t_line){
			// 		x * cell_size * rmap.scale + rmap.pos_x,
			// 		0,
			// 		x * cell_size * rmap.scale + rmap.pos_x,
			// 		600,
			// 		0xFFFFFF
			// 	});
			// }
			x++;
		}
		// printf("\n");
		y++;
	}
	draw_line(c, (t_line){
		c->player.x * rmap.scale + rmap.pos_x,
		c->player.y * rmap.scale + rmap.pos_y,
		(c->player.x + cos(c->player.angle) * (PLAYER_SIZE * 2)) * rmap.scale,
		(c->player.y + sin(c->player.angle) * (PLAYER_SIZE * 2)) * rmap.scale,
		0xFFFFFF
	});
	draw_rect(c, (t_rect){
		rmap.pos_x + c->player.x * rmap.scale - PLAYER_SIZE / 2,
		rmap.pos_y + c->player.y * rmap.scale - PLAYER_SIZE / 2,
		PLAYER_SIZE,
		PLAYER_SIZE,
		0x03f4fc
	});
	draw_rays(c, rmap);
}
