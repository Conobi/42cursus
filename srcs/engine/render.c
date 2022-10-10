/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:01:46 by abastos           #+#    #+#             */
/*   Updated: 2022/10/09 15:38:29 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	fix_fisheye(double distance, double angle, double player_angle)
{
	double	diff;

	diff = angle - player_angle;
	return (distance * cos(diff));
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
		text_y -= ((double)c->cell_size / wall_height);
		color = view_distance(
				get_pixel_color_from_texture(
					c->no_texture, text_x, text_y),
				-(ray.distance / (c->cell_size * 10)));
		if ((int)text_x % c->cell_size == 0)
			color = 0xff;
		pixel_put(c, x, y++, color);
	}
}

typedef struct s_elipse
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
	int	modifier;
}	t_elipse;

void	draw_elipse(t_ctx *c, t_elipse e)
{
	int		x;
	int		y;
	double	dx;
	double	dy;

	y = -e.height;
	while (y++ <= e.height)
	{
		x = -e.width;
		while (x++ <= e.width)
		{
			dx = (double)x / (double)e.width;
			dy = (double)y / (double)e.height;
			if (dx * dx + dy * dy <= 1)
				pixel_put(c, e.x + x, e.y + y,
					view_distance(e.color,
						e.modifier * ((double)y / (c->cell_size))));
		}
	}
}

void	render(t_ctx *c, t_ray *rays)
{
	int		i;
	double	distance;
	int		wall_height;

	draw_elipse(c, (t_elipse){c->window.width / 2, c->window.height + 20,
		c->window.width, c->window.height / 2, 0xd3d374, 1});
	draw_elipse(c, (t_elipse){c->window.width / 2, 0,
		c->window.width, c->window.height / 2, 0xd3d374, -1});
	i = 0;
	while (i < c->rays_num)
	{
		distance = fix_fisheye(rays[i].distance, rays[i].angle, c->player.angle);
		wall_height = (c->window.width / distance) * c->cell_size;
		(void)wall_height;
		render_wall(c, rays[i], i, wall_height);
		i++;
	}
}
