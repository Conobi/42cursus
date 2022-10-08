/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:01:46 by abastos           #+#    #+#             */
/*   Updated: 2022/10/07 20:56:47 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	fix_fisheye(double distance, double angle, double player_angle)
{
	double	diff;

	diff = angle - player_angle;
	return (distance * cos(diff));
}

static void	draw_textures(t_ctx *c, t_ray ray, int x, int y, int wall_height)
{
	double	text_y;
	double	text_x;
	int		color;
	int		px;

	text_y = c->map.cell_size;
	text_x = (((int)ray.x_hit + (int)ray.y_hit) % c->map.cell_size);
	px = 0;
	while (px++ < wall_height)
	{
		text_y -= ((double)c->map.cell_size / wall_height);
		color = view_distance(
				get_pixel_color_from_texture(
					c->wall_north, text_x, text_y),
				-(ray.distance / (c->map.cell_size * 10)));
		pixel_put(c, x, y++, color);
	}
}

void	render(t_ctx *c, t_ray *rays)
{
	int		i;
	double	distance;
	int		wall_height;

	i = 0;
	while (i < c->rays_num)
	{
		distance = fix_fisheye(rays[i].distance, rays[i].angle, c->player.angle);
		wall_height = (c->window.width / distance) * c->map.cell_size;
		draw_textures(c, rays[i],
			i, c->window.height / 2 - wall_height / 2, wall_height);
		draw_rect(c, (t_rect){i, c->window.height / 2 + wall_height / 2,
			1, c->window.height / 2 - wall_height / 2, 0x262626});
		draw_rect(c, (t_rect){i, 0, 1,
			c->window.height / 2 - wall_height / 2, 0x262626});
		i++;
	}
}
