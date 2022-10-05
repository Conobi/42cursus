/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:43:23 by abastos           #+#    #+#             */
/*   Updated: 2022/10/05 19:23:28 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

bool	is_air(t_ctx *c, int computed_x, int computed_y)
{
	if (
		computed_x > 0 && computed_x < c->map.width
		&& computed_y > 0 && computed_y < c->map.height
		&& (c->map.raw[computed_y][computed_x] == '0'
		|| c->map.raw[computed_y][computed_x] == 'N'
		|| c->map.raw[computed_y][computed_x] == 'S'
		|| c->map.raw[computed_y][computed_x] == 'W'
		|| c->map.raw[computed_y][computed_x] == 'E'
		)
	)
		return (true);
	return (false);
}

static double	get_h_dist(t_ctx *c, double angle)
{
	int		up;
	double	first_x;
	double	first_y;
	double	x_step;
	double	y_step;
	double	next_x;
	double	next_y;
	bool	is_wall;
	int		cell_x;
	int		cell_y;

	up = abs((int)floor(angle / M_PI) % 2);
	first_y = floor(c->player.y / c->map.cell_size) * c->map.cell_size;
	if (!up)
		first_y += c->map.cell_size;
	first_x = c->player.x + (first_y - c->player.y) / tan(angle);
	if (!out_of_bounds(c, floor(first_x / c->map.cell_size), floor(first_y / c->map.cell_size)))
	{
		draw_rect(c, (t_rect){
			(first_x) * c->window.res,
			(first_y) * c->window.res,
			2,
			2,
			0x00d0ff
		});
	}
	if (up)
		y_step = -c->map.cell_size;
	else
		y_step = c->map.cell_size;
	x_step = y_step / tan(angle);
	next_x = first_x;
	next_y = first_y;
	is_wall = false;
	while (!is_wall)
	{
		cell_x = floor(next_x / c->map.cell_size);
		cell_y = floor(next_y / c->map.cell_size);
		if (up)
			cell_y -= 1;
		if (out_of_bounds(c, cell_x, cell_y))
			break ;
		if (c->map.raw[cell_y][cell_x] == '1')
			is_wall = true;
		else
		{
			next_x += x_step;
			next_y += y_step;
		}
	}
	if (!out_of_bounds(c, floor(next_x / c->map.cell_size), floor(next_y / c->map.cell_size)))
	{
		draw_rect(c, (t_rect){
			(next_x) * c->window.res,
			(next_y) * c->window.res,
			2,
			2,
			0xfff
		});
	}
	return (get_distance(c->player.x, c->player.y, next_x, next_y));
}

static double	get_v_dist(t_ctx *c, double angle)
{
	int		right;
	double	first_x;
	double	first_y;
	double	x_step;
	double	y_step;
	double	next_x;
	double	next_y;
	bool	is_wall;
	int		cell_x;
	int		cell_y;

	right = abs((int)floor((angle - M_PI / 2) / M_PI) % 2);
	first_x = floor(c->player.x / c->map.cell_size) * c->map.cell_size;
	if (right)
		first_x += c->map.cell_size;
	first_y = c->player.y + (first_x - c->player.x) * tan(angle);
	if (!out_of_bounds(c, floor(first_x / c->map.cell_size), floor(first_y / c->map.cell_size)))
	{
		draw_rect(c, (t_rect){
			(first_x) * c->window.res,
			(first_y) * c->window.res,
			2,
			2,
			0xfcba03
		});
	}
	if (right)
		x_step = c->map.cell_size;
	else
		x_step = -c->map.cell_size;
	y_step = x_step * tan(angle);
	next_x = first_x;
	next_y = first_y;
	is_wall = false;
	while (!is_wall)
	{
		cell_x = floor(next_x / c->map.cell_size);
		if (!right)
			cell_x -= 1;
		cell_y = floor(next_y / c->map.cell_size);
		if (out_of_bounds(c, cell_x, cell_y))
			break ;
		if (c->map.raw[cell_y][cell_x] == '1')
			is_wall = true;
		else
		{
			next_x += x_step;
			next_y += y_step;
		}
	}
	if (!out_of_bounds(c, floor(next_x / c->map.cell_size), floor(next_y / c->map.cell_size)))
	{
		draw_rect(c, (t_rect){
			(next_x) * c->window.res,
			(next_y) * c->window.res,
			2,
			2,
			0xe3fc03
		});
	}
	return (get_distance(c->player.x, c->player.y, next_x, next_y));
}

static t_ray	cast_ray(t_ctx *c, double angle, int id)
{
	t_ray	ray;
	double	v_dist;
	double	h_dist;

	ray.id = id;
	ray.angle = angle;
	v_dist = get_v_dist(c, angle);
	h_dist = get_h_dist(c, angle);
	if (h_dist >= v_dist)
	{
		ray.distance = v_dist;
		ray.is_vertical = true;
	}
	else
	{
		ray.distance = h_dist;
		ray.is_vertical = false;
	}
	ray.cell_percent = ray.id % c->map.cell_size;
	ray.facing = get_facing(angle, ray.is_vertical);
	return (ray);
}

t_ray	*create_rays(t_ctx *c)
{
	double	initial_angle;
	double	angle;
	double	angle_step;
	int		i;
	t_ray	*rays;

	initial_angle = c->player.angle - to_radians(c->player.fov) / 2;
	angle_step = to_radians(c->player.fov) / c->rays_num;
	rays = ft_calloc(sizeof(t_ray), c->rays_num + 1);
	if (!rays)
		return (NULL);
	i = -1;
	while (++i < c->rays_num)
	{
		angle = initial_angle + angle_step * i;
		rays[i] = cast_ray(c, angle, i);
	}
	return (rays);
}
