/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:01:46 by abastos           #+#    #+#             */
/*   Updated: 2022/10/13 19:39:14 by conobi           ###   ########lyon.fr   */
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
	int		y;
	int		color;
	int		px;

	text_y = c->cell_size;
	text_x = (((int)ray.x_hit + (int)ray.y_hit) % c->cell_size);
	y = c->window.height / 2 - wall_height / 2;
	px = 0;
	while (px++ < wall_height)
	{
		if (y > c->window.height)
			break ;
		text_y -= ((double)c->cell_size / wall_height);
		if (text_y < 0)
			continue ;
		if (y > 0 && px < wall_height)
		{
			color = view_distance(
					get_pixel_color_from_texture(
						select_texture(c, ray), text_x, text_y),
					-(ray.distance / (c->cell_size * 10)));
			pixel_put(c, x, y - 1, color);
		}
		y++;
	}
}

static void	draw_cursor(t_ctx *c)
{
	draw_rect(c, (t_rect){c->window.width / 2,
		c->window.height / 2, 2, 2, 0xffffff});
	draw_rect(c, (t_rect){c->window.width / 2 - 10,
		c->window.height / 2, 5, 2, 0xffffff});
	draw_rect(c, (t_rect){c->window.width / 2 + 7,
		c->window.height / 2, 5, 2, 0xffffff});
	draw_rect(c, (t_rect){c->window.width / 2,
		c->window.height / 2 - 10, 2, 5, 0xffffff});
	draw_rect(c, (t_rect){c->window.width / 2,
		c->window.height / 2 + 7, 2, 5, 0xffffff});
}

void	render(t_ctx *c, t_ray *rays)
{
	int		i;
	double	distance;
	int		wall_height;

	i = 0;
	while (i < c->rays_num)
	{
		distance = fix_fisheye(rays[i].distance,
				rays[i].angle, c->player.angle);
		wall_height = (c->window.width / distance) * c->cell_size;
		render_wall(c, rays[i], i, wall_height);
		draw_rect(c, (t_rect){i, (c->window.height / 2 + wall_height / 2) - 2,
			1, (c->window.height / 2 - wall_height / 2) + 2, c->f_color});
		draw_rect(c, (t_rect){i, 0, 1,
			c->window.height / 2 - wall_height / 2, c->c_color});
		i++;
	}
	draw_cursor(c);
}
