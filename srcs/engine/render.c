/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:01:46 by abastos           #+#    #+#             */
/*   Updated: 2022/10/07 15:07:34 by conobi           ###   ########lyon.fr   */
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
	int	text_y;
	int	color;

	text_y = 0;
	while (wall_height)
	{
		color = view_distance(
			get_pixel_color_from_texture(c->no_texture, ray.cell_percent, text_y++),
			-(ray.distance / 200));
		pixel_put(c, x, y++, color);
		--wall_height;
	}
}

void	render(t_ctx *c, t_ray *rays)
{
	int		i;
	double	distance;
	int		wall_height;
	// int		color;

	i = 0;
	while (i < c->rays_num)
	{
		distance = fix_fisheye(rays[i].distance, rays[i].angle, c->player.angle);
		wall_height = (c->window.width / distance) * c->cell_size; // todo: fix big wall size bug when stick on a wall
		// color = view_distance(0xffffff, -(rays[i].distance / 100));
		// if (rays[i].facing == NORTH)
		// 	color = view_distance(0xeb4034, -(rays[i].distance / 100));
		// else if (rays[i].facing == SOUTH)
		// 	color = view_distance(0x32a852, -(rays[i].distance / 100));
		// else if (rays[i].facing == EAST)
		// 	color = view_distance(0x4287f5, -(rays[i].distance / 100));
		// draw_rect(c, (t_rect){i, c->window.height / 2 - wall_height / 2, 1, wall_height, color});
		draw_textures(c, rays[i], i, c->window.height / 2 - wall_height / 2, wall_height);
		draw_rect(c, (t_rect){i, c->window.height / 2 + wall_height / 2, 1, c->window.height / 2 - wall_height / 2, 0x262626});
		draw_rect(c, (t_rect){i, 0, 1, c->window.height / 2 - wall_height / 2, 0x262626});
		i++;
	}
}
