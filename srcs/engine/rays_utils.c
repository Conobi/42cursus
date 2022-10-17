/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:02:14 by abastos           #+#    #+#             */
/*   Updated: 2022/10/17 15:04:44 by abastos          ###   ########lyon.fr   */
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
		computed_x > 0 && computed_x < c->map_size_x
		&& computed_y > 0 && computed_y < c->map_size_y
		&& c->map[computed_y][computed_x] == 0
	)
		return (true);
	return (false);
}

t_ray	create_ray(t_ctx *c, t_calc calc, double angle, int id)
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

void	find_wall(t_ctx *c, t_calc *calc)
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
