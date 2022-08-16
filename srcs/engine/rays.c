/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 20:52:40 by abastos           #+#    #+#             */
/*   Updated: 2022/08/16 05:59:16 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

typedef struct s_findw {
	double	part;
	double	first_y;
	double	first_x;
	double	y_a;
	double	x_a;
	double	next_x;
	double	next_y;
}	t_findw;

double	get_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

t_ray	*create_ray(t_ctx *c, t_findw *findw, double angle, bool vertically)
{
	t_ray	*new_ray;

	new_ray = malloc(sizeof(t_ray));
	new_ray->angle = angle;
	new_ray->distance = get_distance(c->player->x, c->player->y, findw->next_x, findw->next_y);
	printf("next x: %f | next y: %f | distance: %f\n", findw->next_x, findw->next_y, new_ray->distance);
	new_ray->vertical = vertically;
	// new_ray->facing = facing_v(); // todo: chect in circle position of the angle
	return (new_ray);
}

int	get_cell_y(t_findw *findw, bool vertical)
{
	if (!vertical)
	{
		if (findw->part)
			return (floor(findw->next_y / CELL_SIZE) - 1);
	}
	return (floor(findw->next_y / CELL_SIZE));
}

int	get_cell_x(t_findw *findw, bool vertical)
{
	if (vertical)
	{
		if (findw->part)
			return (floor(findw->next_x / CELL_SIZE));
		return (floor(findw->next_x / CELL_SIZE) - 1);
	}
	return (floor(findw->next_x / CELL_SIZE));
}

t_ray	*find_wall(t_ctx *c, t_findw *findw, double angle, bool vertically)
{
	char	wall;
	int		cell_x;
	int		cell_y;

	wall = false;
	findw->next_x = findw->first_x;
	findw->next_y = findw->first_y;
	while (wall == '0')
	{
		cell_x = get_cell_x(findw, vertically);
		cell_y = get_cell_y(findw, vertically);
		if (out_of_bounds(c, cell_x, cell_y))
			break ;
		wall = c->map->raw[cell_y][cell_x];
		if (wall == '0')
		{
			findw->next_x += findw->x_a;
			findw->next_y += findw->x_a;
		}
	}
	return (create_ray(c, findw, angle, vertically));
}

t_ray	*get_v_col(t_ctx *c, double angle)
{
	t_findw	findw;

	findw.part = abs((int)floor((angle - M_PI / 2) / M_PI) % 2); // facing right
	if (findw.part)
	{
		findw.first_x = floor(c->player->x / CELL_SIZE) * CELL_SIZE;
		findw.x_a = CELL_SIZE;
	}
	else
	{
		findw.first_x = floor(c->player->x / CELL_SIZE);
		findw.x_a = -CELL_SIZE;
	}
	findw.first_y = c->player->y + (findw.first_x - c->player->x) / tan(angle);
	findw.y_a = findw.x_a / tan(angle);
	return (find_wall(c, &findw, angle, true));
}

t_ray	*get_h_col(t_ctx *c, double angle)
{
	t_findw	findw;

	findw.part = abs((int)floor(angle / M_PI) % 2);
	if (findw.part) // facing up
	{
		findw.first_y = floor(c->player->y / CELL_SIZE) * CELL_SIZE;
		findw.y_a = -CELL_SIZE;
	}
	else
	{
		findw.first_y = floor(c->player->y / CELL_SIZE);
		findw.y_a = CELL_SIZE;
	}
	findw.first_x = c->player->x + (findw.first_y - c->player->y) / tan(angle);
	findw.x_a = findw.y_a / tan(angle);
	return (find_wall(c, &findw, angle, false));
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

	initial_angle = c->player->angle - to_radians(FOV) / 2;
	rays_num = c->window->width;
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
