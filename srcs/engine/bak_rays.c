/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bak_rays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:01:53 by conobi            #+#    #+#             */
/*   Updated: 2022/10/07 15:04:06 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_cell_y(t_ctx *c, t_temp *t, bool vertical)
{
	if (!vertical)
	{
		if (t->part)
			return (floor(t->next_y / c->cell_size) - 1);
	}
	return (floor(t->next_y / c->cell_size));
}

int	get_cell_x(t_ctx *c, t_temp *t, bool vertical)
{
	if (vertical)
	{
		if (t->part)
			return (floor(t->next_x / c->cell_size));
		return (floor(t->next_x / c->cell_size) - 1);
	}
	return (floor(t->next_x / c->cell_size));
}

t_ray	create_ray(t_ctx *c, t_temp *t, double angle, bool is_vertical)
{
	t_ray	new_ray;

	new_ray.angle = angle;
	new_ray.distance = get_distance(c->player.x, c->player.y, t->next_x, t->next_y);
	// printf("next x: %f | next y: %f | distance: %f\n", t->next_x, t->next_y, new_ray.distance);
	new_ray.vertical = is_vertical;
	// new_ray->facing = facing_v(); // todo: chect in circle position of the angle
	return (new_ray);
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
		cell_x = get_cell_x(c, t, is_vertical);
		cell_y = get_cell_y(c, t, is_vertical);
		if (out_of_bounds(c, cell_x, cell_y))
			break ;
		wall = c->map.raw[cell_y][cell_x];
		if (wall == '0')
		{
			t->next_x += t->x_a;
			t->next_y += t->x_a;
		}
	}
	return (create_ray(c, t, angle, is_vertical));
}

t_ray	get_v_col(t_ctx *c, double angle)
{
	t_temp	t;

	t.part = abs((int)floor((angle - M_PI / 2) / M_PI) % 2); // facing right
	if (t.part)
	{
		t.first_x = floor(c->player.x / c->cell_size);
		t.x_a = c->cell_size;
	}
	else
	{
		t.first_x = floor(c->player.x / c->cell_size);
		t.x_a = -c->cell_size;
	}
	t.first_y = c->player.y + (t.first_x - c->player.x) / tan(angle);
	t.y_a = t.x_a / tan(angle);
	return (find_wall(c, &t, angle, true));
}

t_ray	get_h_col(t_ctx *c, double angle)
{
	t_temp	t;

	t.part = abs((int)floor(angle / M_PI) % 2);
	if (t.part) // facing up
	{
		t.first_y = floor(c->player.y / c->cell_size) * c->cell_size;
		t.y_a = -c->cell_size;
	}
	else
	{
		t.first_y = floor(c->player.y / c->cell_size);
		t.y_a = c->cell_size;
	}
	t.first_x = c->player.x + (t.first_y - c->player.y) / tan(angle);
	t.x_a = t.y_a / tan(angle);
	return (find_wall(c, &t, angle, false));
}

int	find_wall2(t_ctx *c, t_ray *ray, int x, int y)
{
	int	computed_x;
	int	computed_y;
	int	x_factor;
	int	y_factor;

	computed_x = (int)(x / c->cell_size);
	computed_y = (int)(y / c->cell_size);
	x_factor = 1;
	y_factor = -1;
	if (ray->mfacing == SWEST || ray->mfacing == NWEST)
		x_factor *= -1;
	if (ray->mfacing == SEAST || ray->mfacing == SWEST)
		y_factor *= -1;
	printf("Rayon N°%d, facteurs: [%d,%d], computed: [%d,%d], Windowed: [%d, %d], Map: [%d,%d]\n", ray->id, x_factor, y_factor, computed_x, computed_y, x, y, c->map_size_y, c->map_size_x);
	while (
		computed_x > 0 && computed_x < c->map_size_y
		&& computed_y > 0 && computed_y < c->map_size_x
		&& c->map.raw[computed_y][computed_x] == '0'
	)
	{
		x += c->cell_size * x_factor;
		y += c->cell_size * y_factor;
		printf("Rayon N°%d [%d,%d] -> ", ray->id, computed_x, computed_y);
		computed_x += x_factor;
		computed_y += y_factor;
		printf("[%d,%d]\n", computed_x, computed_y);
		// draw_rect(c, (t_rect){
		// 	(x - 2) * c->window.res,
		// 	(y - 2) * c->window.res,
		// 	4,
		// 	4,
		// 	0xFF00FF
		// });
		draw_rect(c, (t_rect){
				(x - 2) * c->window.res,
				(y - 2) * c->window.res,
				4,
				4,
				0x00f055
			});
	}
	if (
		computed_x > 0 && computed_x < c->map_size_y
		&& computed_y > 0 && computed_y < c->map_size_x
		&& c->map.raw[computed_y][computed_x] == '1'
	)
		printf("Rayon N°%d, map [%d, %d] == 1\n", ray->id, computed_x, computed_y);
	// ray->final_x = floor(x / c->cell_size) * c->cell_size;
	// ray->final_y = floor(y / c->cell_size) * c->cell_size;
	draw_rect(c, (t_rect){
		(x - 2) * c->window.res,
		(y - 2) * c->window.res,
		4,
		4,
		0xff00ff
	});
	return (get_distance(c->player.x, c->player.y, x, y));
}

// int	distance_hor(t_ctx *c, t_ray *ray)
// {
// 	int		x_init;
// 	int		y_init;

// 	y_init = floor(c->player.y / c->cell_size) * c->cell_size;
// 	if (ray->mfacing == SWEST || ray->mfacing == SEAST)
// 		y_init = floor(c->player.y / (c->cell_size + c->cell_size)) * c->cell_size;
// 	x_init = floor(c->player.x + tan(ray->angle) * (y_init - c->player.y));
// 	printf("Rayon N°%d, dda_init for x: [%d, %d]\n", ray->id, x_init, y_init);
// 	draw_rect(c, (t_rect){
// 		x_init - 2,
// 		y_init,
// 		4,
// 		4,
// 		0xff0000
// 	});
// 	return (get_distance(c->player.x, c->player.y, x_init, y_init));
// 	// return (find_wall2(c, ray, x_init, y_init));
// }

int	distance_hor(t_ctx *c, t_ray *ray, int *x_init, int *y_init)
{
	*y_init = floor(c->player.y / c->cell_size) * c->cell_size;
	if (ray->mfacing == SWEST || ray->mfacing == SEAST)
		*y_init += c->cell_size;
	*x_init = floor(c->player.x + (*y_init - c->player.y) / tan(ray->angle));
	printf("Rayon N°%d, dda_init for hor: [%d, %d], facing: %d\n", ray->id, *x_init, *y_init, ray->mfacing);
	// return (get_distance(c->player.x, c->player.y, x_init, y_init));
	return (get_distance(c->player.x, c->player.y, *x_init, *y_init));
}

int	distance_ver(t_ctx *c, t_ray *ray, int *x_init, int *y_init)
{
	*x_init = floor(c->player.x / c->cell_size) * c->cell_size;
	if (ray->mfacing == SEAST || ray->mfacing == NEAST)
		*x_init += c->cell_size;
	// y_init = floor(c->player.y + (x_init - c->player.x) / tan(ray->angle));
	*y_init = c->player.y + (*x_init - c->player.x) * tan(ray->angle);
	printf("Rayon N°%d, dda_init for hor: [%d, %d], facing: %d\n", ray->id, *x_init, *y_init, ray->mfacing);
	// draw_rect(c, (t_rect){
	// 	(*x_init - 2) * c->window.res,
	// 	(*y_init - 2) * c->window.res,
	// 	4,
	// 	4,
	// 	0x00ff
	// });
	return (get_distance(c->player.x, c->player.y, *x_init, *y_init));
}

t_ray	cast_ray(t_ctx *c, double angle, int id)
{
	t_ray	ray;
	int		ver_x;
	int		ver_y;
	int		hor_x;
	int		hor_y;

	ray.id = id;
	ray.angle = angle;
	ray.mfacing = get_mfacing(angle);
	init_distance(c, &ray);
	find_wall2(c, &ray);
	return (ray);
	// printf("Face: %d\n", ray.mfacing);
	// v_col = get_v_col(c, angle);
	// h_col = get_h_col(c, angle);
	// if (h_col.distance >= v_col.distance)
	// 	return (v_col);
	// if (distance_hor(c, &ray, &hor_x, &hor_y) < distance_ver(c, &ray, &ver_x, &ver_y))
	// {
	// 	draw_rect(c, (t_rect){
	// 		(hor_x - 2) * c->window.res,
	// 		(hor_y - 2) * c->window.res,
	// 		4,
	// 		4,
	// 		0xff0000
	// 	});
	// 	ray.distance = find_wall2(c, &ray, hor_x, hor_y);
	// }
	// else
	// {
	// 	draw_rect(c, (t_rect){
	// 		(ver_x - 2) * c->window.res,
	// 		(ver_y - 2) * c->window.res,
	// 		4,
	// 		4,
	// 		0x00ff
	// 	});
	// 	ray.distance = find_wall2(c, &ray, ver_x, ver_y);
	// }

}
