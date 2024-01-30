/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:43:23 by abastos           #+#    #+#             */
/*   Updated: 2022/10/17 15:04:39 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_ray	get_h_ray(t_ctx *c, double angle, int id)
{
	t_calc	calc;

	calc.is_vertical = false;
	calc.up = abs((int)floor(angle / M_PI) % 2);
	calc.first_y = floor(c->player.y / c->cell_size) * c->cell_size;
	if (!calc.up)
		calc.first_y += c->cell_size;
	calc.first_x = c->player.x + (calc.first_y - c->player.y) / tan(angle);
	if (calc.up)
		calc.y_step = -c->cell_size;
	else
		calc.y_step = c->cell_size;
	calc.x_step = calc.y_step / tan(angle);
	calc.next_x = calc.first_x;
	calc.next_y = calc.first_y;
	find_wall(c, &calc);
	return (create_ray(c, calc, angle, id));
}

static t_ray	get_v_ray(t_ctx *c, double angle, int id)
{
	t_calc	calc;

	calc.is_vertical = true;
	calc.right = abs((int)floor((angle - M_PI * 0.5) / M_PI) % 2);
	calc.first_x = floor(c->player.x / c->cell_size) * c->cell_size;
	if (calc.right)
		calc.first_x += c->cell_size;
	calc.first_y = c->player.y + (calc.first_x - c->player.x) * tan(angle);
	if (calc.right)
		calc.x_step = c->cell_size;
	else
		calc.x_step = -c->cell_size;
	calc.y_step = calc.x_step * tan(angle);
	calc.next_x = calc.first_x;
	calc.next_y = calc.first_y;
	find_wall(c, &calc);
	return (create_ray(c, calc, angle, id));
}

static t_ray	cast_ray(t_ctx *c, double angle, int id)
{
	t_ray	v_ray;
	t_ray	h_ray;

	v_ray = get_v_ray(c, angle, id);
	h_ray = get_h_ray(c, angle, id);
	if (h_ray.distance >= v_ray.distance)
		return (v_ray);
	return (h_ray);
}

t_ray	*create_rays(t_ctx *c, int fov, int rays_num)
{
	double	initial_angle;
	double	angle;
	double	angle_step;
	int		i;
	t_ray	*rays;

	initial_angle = c->player.angle - to_radians(fov) * 0.5;
	angle_step = to_radians(fov) / rays_num;
	rays = ft_calloc(sizeof(t_ray), rays_num + 1);
	if (!rays)
	{
		print_err(NULL, strerror(12), 12);
		exit(1);
		return (NULL);
	}
	i = -1;
	while (++i < rays_num)
	{
		angle = initial_angle + angle_step * i;
		rays[i] = cast_ray(c, angle, i);
	}
	return (rays);
}
