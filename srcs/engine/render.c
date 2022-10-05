/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:01:46 by abastos           #+#    #+#             */
/*   Updated: 2022/10/05 20:30:27 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	fix_fisheye(double distance, double angle, double player_angle)
{
	double	diff;

	diff = angle - player_angle;
	return (distance * cos(diff));
}

static void	draw_textures(t_ctx *c, int x, int y, int wall_height)
{
	int	color;

	while (y < wall_height)
	{
		// color = get_pixel_color_from_texture(c->wall_north, x, y);
		color = 0xfff;
		pixel_put(c, x, y, color);
		y++;
	}
}

void	render(t_ctx *c, t_ray *rays)
{
	int		i;
	double	distance;
	int		wall_height;
	int		color;

	i = 0;
	while (i < c->rays_num - 2)
	{
		distance = fix_fisheye(rays[i].distance, rays[i].angle, c->player.angle);
		wall_height = (c->window.width / distance) * c->map.cell_size;
		if (wall_height > c->window.height)
			wall_height = c->window.height;
		color = view_distance(0xffffff, -(rays[i].distance / 100));
		if (rays[i].facing == NORTH)
			color = view_distance(0xeb4034, -(rays[i].distance / 100));
		else if (rays[i].facing == SOUTH)
			color = view_distance(0x32a852, -(rays[i].distance / 100));
		else if (rays[i].facing == EAST)
			color = view_distance(0x4287f5, -(rays[i].distance / 100));
		// draw_rect(c, (t_rect){i, c->window.height / 2 - wall_height / 2, 1, wall_height, color});
		draw_textures(c, i, c->window.height / 2 - wall_height / 2, wall_height);
		draw_rect(c, (t_rect){i, c->window.height / 2 + wall_height / 2, 1, c->window.height / 2 - wall_height / 2, 0x262626});
		draw_rect(c, (t_rect){i, 0, 1, c->window.height / 2 - wall_height / 2, 0x262626});
		i++;
	}
}
