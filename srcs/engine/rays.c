/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 20:52:40 by abastos           #+#    #+#             */
/*   Updated: 2022/08/25 17:39:46 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_temp {
	double	part;
	double	first_y;
	double	first_x;
	double	y_a;
	double	x_a;
	double	next_x;
	double	next_y;
}	t_temp;

double	get_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

t_ray	create_ray(t_ctx *c, t_temp *t, double angle, bool is_vertical)
{
	t_ray	new_ray;

	new_ray.angle = angle;
	new_ray.distance = get_distance(c->player.x, c->player.y, t->next_x, t->next_y);
	printf("next x: %f | next y: %f | distance: %f\n", t->next_x, t->next_y, new_ray.distance);
	new_ray.vertical = is_vertical;
	// new_ray->facing = facing_v(); // todo: chect in circle position of the angle
	return (new_ray);
}

int	get_cell_y(t_temp *t, bool vertical)
{
	if (!vertical)
	{
		if (t->part)
			return (floor(t->next_y / CELL_SIZE) - 1);
	}
	return (floor(t->next_y / CELL_SIZE));
}

int	get_cell_x(t_temp *t, bool vertical)
{
	if (vertical)
	{
		if (t->part)
			return (floor(t->next_x / CELL_SIZE));
		return (floor(t->next_x / CELL_SIZE) - 1);
	}
	return (floor(t->next_x / CELL_SIZE));
}

t_ray	find_wall(t_ctx *c, t_temp *t, double angle, bool is_vertical)
{
	char	wall;
	int		cell_x;
	int		cell_y;

	wall = 0;
	t->next_x = t->first_x;
	t->next_y = t->first_y;
	while ((wall == 0 || wall == '0') && t->next_x < (c->window.width * c->window.width) && t->next_y > (c->window.height * c->window.height))
	{
		printf("salut ^^\n");
		cell_x = get_cell_x(t, is_vertical);
		cell_y = get_cell_y(t, is_vertical);
		if (out_of_bounds(c, cell_x, cell_y))
			break ;
		wall = c->map.raw[cell_y][cell_x];
		if (wall == '0')
		{
			t->next_x += t->x_a;
			t->next_y += t->x_a;
		}
	}
	if (t->next_x > (c->window.width * c->window.width) || t->next_x < -1 * (c->window.width * c->window.width))
	{
		t->next_x = c->player.x + 50;
		printf("alors euh %f\n", t->first_x);
	}
	if (t->next_y > (c->window.width * c->window.width) || t->next_y < -1 * (c->window.width * c->window.width))
	{
		t->next_y = c->player.y + 50;
		printf("alors euh %f\n", t->first_y);
	}
	return (create_ray(c, t, angle, is_vertical));
}

// t_ray	get_v_col(t_ctx *c, double angle)
// {
// 	t_temp	t;

// 	t.part = abs((int)floor((angle - M_PI / 2) / M_PI) % 2); // facing right
// 	if (t.part)
// 	{
// 		t.first_x = floor(c->player.x / CELL_SIZE);
// 		t.x_a = CELL_SIZE;
// 	}
// 	else
// 	{
// 		t.first_x = floor(c->player.x / CELL_SIZE);
// 		t.x_a = -CELL_SIZE;
// 	}
// 	t.first_y = c->player.y + (t.first_x - c->player.x) / tan(angle);
// 	t.y_a = t.x_a / tan(angle);
// 	return (find_wall(c, &t, angle, true));
// }

// t_ray	get_h_col(t_ctx *c, double angle)
// {
// 	t_temp	t;

// 	t.part = abs((int)floor(angle / M_PI) % 2);
// 	if (t.part) // facing up
// 	{
// 		t.first_y = floor(c->player.y / CELL_SIZE) * CELL_SIZE;
// 		t.y_a = -CELL_SIZE;
// 	}
// 	else
// 	{
// 		t.first_y = floor(c->player.y / CELL_SIZE);
// 		t.y_a = CELL_SIZE;
// 	}
// 	t.first_x = c->player.x + (t.first_y - c->player.y) / tan(angle);
// 	t.x_a = t.y_a / tan(angle);
// 	return (find_wall(c, &t, angle, false));
// }

t_ray	test_col(t_ctx *c, double angle)
{
	t_temp	t;

	t.first_x = c->player.x + 100;
	t.first_y = c->player.y + 100;
	t.x_a = 20;
	t.y_a = 20;
	return (find_wall(c, &t, angle, true));
}

t_ray	cast_ray(t_ctx *c, double angle)
{
	// v_col = get_v_col(c, angle);
	// h_col = get_h_col(c, angle);
	// if (h_col.distance >= v_col.distance)
	// 	return (v_col);
	return (test_col(c, angle));
}

t_ray *create_rays(t_ctx *c)
{
	double	initial_angle;
	double	angle;
	double	angle_step;
	int		i;
	t_ray	*rays;

	initial_angle = c->player.angle - to_radians(FOV) / 2;
	angle_step = to_radians(FOV) / c->rays_num;
	rays = ft_calloc(sizeof(t_ray), c->rays_num + 1);
	if (!rays)
		return (NULL);
	i = -1;
	while (++i < c->rays_num)
	{
		angle = initial_angle + angle_step * i;
		rays[i] = cast_ray(c, angle);
	}
	return (rays);
}
