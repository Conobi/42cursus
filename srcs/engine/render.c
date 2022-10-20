/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:01:46 by abastos           #+#    #+#             */
/*   Updated: 2022/10/20 16:45:22 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	fix_fisheye(double distance, double angle, double player_angle)
{
	double	diff;

	diff = angle - player_angle;
	return (distance * cos(diff));
}

static t_img	select_texture(t_ctx *c, t_ray ray)
{
	t_img	texture;

	if (ray.facing == NORTH)
		texture = c->no_texture;
	else if (ray.facing == SOUTH)
		texture = c->so_texture;
	else if (ray.facing == EAST)
		texture = c->ea_texture;
	else
		texture = c->we_texture;
	return (texture);
}

static void	render_wall(t_ctx *c, t_ray ray, int x, int wall_height)
{
	double	text_y;
	double	text_x;
	double	step;
	int		y;
	int		px;

	text_y = 0;
	text_x = (((int)ray.x_hit + (int)ray.y_hit) % c->cell_size);
	y = c->window.height * 0.5 - wall_height * 0.5;
	step = (float)ray.distance / (c->cell_size * 10);
	px = 0;
	while (px++ < wall_height)
	{
		if (y > c->window.height)
			break ;
		text_y += ((double)c->cell_size / wall_height);
		if (text_y > c->cell_size)
			continue ;
		if (y > 0 && px < wall_height)
			pixel_put(c, x, y - 1, linear_gradient(
					get_pixel_color_from_texture(
						select_texture(c, ray), text_x, text_y),
					c->fog_color, step, false));
		y++;
	}
}

static void	draw_cursor(t_ctx *c)
{
	draw_rect(c, (t_rect){c->window.width * 0.5,
		c->window.height * 0.5, 2, 2, 0xffffff});
	draw_rect(c, (t_rect){c->window.width * 0.5 - 10,
		c->window.height * 0.5, 5, 2, 0xffffff});
	draw_rect(c, (t_rect){c->window.width * 0.5 + 7,
		c->window.height * 0.5, 5, 2, 0xffffff});
	draw_rect(c, (t_rect){c->window.width * 0.5,
		c->window.height * 0.5 - 10, 2, 5, 0xffffff});
	draw_rect(c, (t_rect){c->window.width * 0.5,
		c->window.height * 0.5 + 7, 2, 5, 0xffffff});
}

void	render(t_ctx *c, t_ray *rays)
{
	int		i;
	double	distance;
	int		wall_height;

	i = 0;
	draw_rect_gradient(c, (t_rect){0, 0, c->window.width,
		c->window.height * 0.5, 0}, c->c_color, c->fog_color);
	draw_rect_gradient(c, (t_rect){0, c->window.height * 0.5,
		c->window.width, c->window.height * 0.5, 0}, c->fog_color, c->f_color);
	while (i < c->rays_num)
	{
		distance = fix_fisheye(rays[i].distance,
				rays[i].angle, c->player.angle);
		wall_height = (c->window.width / distance) * c->cell_size;
		render_wall(c, rays[i], i, wall_height);
		i++;
	}
	draw_cursor(c);
}
