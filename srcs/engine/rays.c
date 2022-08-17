/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 20:52:40 by abastos           #+#    #+#             */
/*   Updated: 2022/08/17 18:44:29 by conobi           ###   ########lyon.fr   */
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

t_ray	*create_ray(t_ctx *c, t_temp *t, double angle, bool is_vertical)
{
	t_ray	*new_ray;

	new_ray = malloc(sizeof(t_ray));
	new_ray->angle = angle;
	new_ray->distance = get_distance(c->player.x, c->player.y, t->next_x, t->next_y);
	printf("next x: %f | next y: %f | distance: %f\n", t->next_x, t->next_y, new_ray->distance);
	new_ray->vertical = is_vertical;
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

t_ray	*find_wall(t_ctx *c, t_temp *t, double angle, bool is_vertical)
{
	char	wall;
	int		cell_x;
	int		cell_y;

	wall = 0;
	t->next_x = t->first_x;
	t->next_y = t->first_y;
	while (wall == 0 || wall == '0')
	{
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
		// if (t->next_x > c->map.width * c->window.res * CELL_SIZE)
	}
	return (create_ray(c, t, angle, is_vertical));
}

t_ray	*get_v_col(t_ctx *c, double angle)
{
	t_temp	t;

	t.part = abs((int)floor((angle - M_PI / 2) / M_PI) % 2); // facing right
	if (t.part)
	{
		t.first_x = floor(c->player.x / CELL_SIZE) * CELL_SIZE;
		t.x_a = CELL_SIZE;
	}
	else
	{
		t.first_x = floor(c->player.x / CELL_SIZE);
		t.x_a = -CELL_SIZE;
	}
	t.first_y = c->player.y + (t.first_x - c->player.x) / tan(angle);
	t.y_a = t.x_a / tan(angle);
	return (find_wall(c, &t, angle, true));
}

t_ray	*get_h_col(t_ctx *c, double angle)
{
	t_temp	t;

	t.part = abs((int)floor(angle / M_PI) % 2);
	if (t.part) // facing up
	{
		t.first_y = floor(c->player.y / CELL_SIZE) * CELL_SIZE;
		t.y_a = -CELL_SIZE;
	}
	else
	{
		t.first_y = floor(c->player.y / CELL_SIZE);
		t.y_a = CELL_SIZE;
	}
	t.first_x = c->player.x + (t.first_y - c->player.y) / tan(angle);
	t.x_a = t.y_a / tan(angle);
	return (find_wall(c, &t, angle, false));
}

t_ray	*cast_ray(t_ctx *c, double angle)
{
	t_ray	*v_col;
	t_ray	*h_col;

	v_col = get_v_col(c, angle);
	h_col = get_h_col(c, angle);
	if (h_col->distance >= v_col->distance)
		return (v_col);
	return (h_col);
}

t_list	*create_rays(t_ctx *c)
{
	double	initial_angle;
	double	angle;
	double	angle_step;
	int		rays_num;
	int		i;
	t_list	*rays;
	t_list	*new_ray;

	initial_angle = c->player.angle - to_radians(FOV) / 2;
	rays_num = c->window.width;
	angle_step = to_radians(FOV) / rays_num;
	i = 0;
	rays = ft_lstnew(NULL);
	while (i < rays_num)
	{
		angle = initial_angle + angle_step * i;
		// printf("new angle: %f\n", angle);
		// printf("create ray %f %d %f %f\n", initial_angle, rays_num, angle_step, angle);
		new_ray = ft_lstnew(cast_ray(c, angle));
		ft_lstadd_front(&rays, new_ray); // todo: just for testing pass to lstadd_front to improve perfs
		rays = new_ray;
		i++;
	}
	return (rays);
}
