/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:43:23 by abastos           #+#    #+#             */
/*   Updated: 2022/10/13 14:34:13 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_calc
{
	double	first_x;
	double	first_y;
	double	x_step;
	double	y_step;
	double	next_x;
	double	next_y;
	bool	is_wall;
	bool	is_vertical;
	int		up;
	int		right;
	int		cell_x;
	int		cell_y;
}	t_calc;

double	get_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

bool	is_air(t_ctx *c, int computed_x, int computed_y)
{
	if (
		computed_x > 0 && computed_x < c->map_size_x
		&& computed_y > 0 && computed_y < c->map_size_y
		&& c->map[computed_y][computed_x] == 0
	)
		return (true);
	return (false);
}

static t_ray	create_ray(t_ctx *c, t_calc calc, double angle, int id)
{
	t_ray	ray;

	ray.id = id;
	ray.angle = angle;
	ray.distance = get_distance(c->player.x, c->player.y,
			calc.next_x, calc.next_y);
	ray.is_vertical = calc.is_vertical;
	ray.x_hit = calc.next_x;
	ray.y_hit = calc.next_y;
	ray.cell_percent = ray.id % c->cell_size;
	ray.facing = get_facing(angle, ray.is_vertical);
	return (ray);
}

static void	find_wall(t_ctx *c, t_calc *calc)
{
	calc->is_wall = false;
	while (!calc->is_wall)
	{
		calc->cell_x = floor(calc->next_x / c->cell_size);
		if (calc->is_vertical && !calc->right)
			calc->cell_x -= 1;
		calc->cell_y = floor(calc->next_y / c->cell_size);
		if (!calc->is_vertical && calc->up)
			calc->cell_y -= 1;
		if (out_of_bounds(c, calc->cell_x, calc->cell_y))
			break ;
		if (c->map[calc->cell_y][calc->cell_x] == 1)
			calc->is_wall = true;
		else
		{
			calc->next_x += calc->x_step;
			calc->next_y += calc->y_step;
		}
	}
}

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
	calc.right = abs((int)floor((angle - M_PI / 2) / M_PI) % 2);
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

	initial_angle = c->player.angle - to_radians(fov) / 2;
	angle_step = to_radians(fov) / rays_num;
	rays = ft_calloc(sizeof(t_ray), rays_num + 1);
	if (!rays) // todo: exit cub
		return (NULL);
	i = -1;
	while (++i < rays_num)
	{
		angle = initial_angle + angle_step * i;
		rays[i] = cast_ray(c, angle, i);
	}
	return (rays);
}
