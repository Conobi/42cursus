/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 20:52:40 by abastos           #+#    #+#             */
/*   Updated: 2022/10/05 14:42:38 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

int	get_mfacing(double angle)
{
	int	ret;

	ret = 0;
	if (abs((int)floor(angle / M_PI) % 2)) // facing up
		ret += 2;
	if (abs((int)floor((angle - M_PI / 2) / M_PI) % 2)) // facing right
		ret += 1;
	return (ret);
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

void	find_wall_h(t_ctx *c, t_ray *ray)
{
	int		computed_x;
	int		computed_y;
	int		x_factor;
	int		y_factor;
	int		rev;
	double	tan_x;

	x_factor = 1;
	y_factor = 1;
	rev = 0;
	if (ray->mfacing == NEAST || ray->mfacing == NWEST)
	{
		x_factor *= -1;
		y_factor *= -1;
		rev = 1;
	}
	tan_x = tan(ray->angle);
	computed_x = floor((ray->h_x - rev) / c->map.cell_size);
	computed_y = floor((ray->h_y - rev) / c->map.cell_size);
	// while (is_air(c, computed_x, computed_y))
	// {
	// 	if (ray->h_x * c->window.res < c->window.width
	// 		&& ray->h_y * c->window.res < c->window.height)
	// 		draw_rect(c, (t_rect){
	// 			(ray->h_x - 1) * c->window.res,
	// 			(ray->h_y - 1) * c->window.res,
	// 			2,
	// 			2,
	// 			0x9333ea
	// 		});
	// 	// printf("Rayon violet N°%d (%d, %d) [%d,%d]\n", ray->id, ray->h_x, ray->h_y, computed_x, computed_y);
	// 	ray->h_x += c->map.cell_size / tan_x * x_factor;
	// 	ray->h_y += c->map.cell_size * y_factor;
	// 	computed_x = floor((ray->h_x - rev) / c->map.cell_size);
	// 	computed_y = floor((ray->h_y - rev) / c->map.cell_size);
	// }
	// if (ray->h_x * c->window.res < c->window.width
	// 	&& ray->h_y * c->window.res < c->window.height)
	// 	draw_rect(c, (t_rect){
	// 		(ray->h_x - 1) * c->window.res,
	// 		(ray->h_y - 1) * c->window.res,
	// 		2,
	// 		2,
	// 		0xff00ff
	// 	});
	ray->h_distance = get_distance(
			c->player.x, c->player.y, ray->h_x, ray->h_y);
}

void	find_wall_v(t_ctx *c, t_ray *ray)
{
	int		computed_x;
	int		computed_y;
	int		x_factor;
	int		y_factor;
	int		rev;
	double	tan_x;

	x_factor = 1;
	y_factor = 1;
	rev = 0;
	if (ray->mfacing == SWEST || ray->mfacing == NWEST)
	{
		x_factor *= -1;
		y_factor *= -1;
		rev = 1;
	}
	tan_x = tan(ray->angle);
	computed_x = floor((ray->v_x - rev) / c->map.cell_size);
	computed_y = floor((ray->v_y - rev) / c->map.cell_size);
	// while (is_air(c, computed_x, computed_y))
	// {
	// 	if (ray->v_x * c->window.res < c->window.width
	// 		&& ray->v_y * c->window.res < c->window.height)
	// 		draw_rect(c, (t_rect){
	// 			(ray->v_x - 1) * c->window.res,
	// 			(ray->v_y - 1) * c->window.res,
	// 			2,
	// 			2,
	// 			0xfb7185
	// 		});
	// 	ray->v_x += c->map.cell_size * x_factor;
	// 	ray->v_y += tan_x * c->map.cell_size * y_factor;
	// 	computed_x = floor((ray->v_x - rev) / c->map.cell_size);
	// 	computed_y = floor((ray->v_y - rev) / c->map.cell_size);
	// 	// printf("Rayon rose N°%d [%d,%d]\n", ray->id, computed_x, computed_y);
	// }
	// if (ray->v_x * c->window.res < c->window.width
	// 	&& ray->v_y * c->window.res < c->window.height)
	// 	draw_rect(c, (t_rect){
	// 		(ray->v_x - 1) * c->window.res,
	// 		(ray->v_y - 1) * c->window.res,
	// 		2,
	// 		2,
	// 		0xfacc15
	// 	});
	ray->v_distance = get_distance(
			c->player.x, c->player.y, ray->v_x, ray->v_y);
}

typedef struct s_temp {
	double	h_distance;
	double	v_distance;
	int		hor_x_init;
	int		hor_y_init;
	int		ver_x_init;
	int		ver_y_init;
}	t_temp;

void	init_distance_h(t_ctx *c, t_ray *ray)
{
	ray->h_y = floor(c->player.y / c->map.cell_size) * c->map.cell_size;
	if (ray->mfacing == NEAST || ray->mfacing == NWEST)
		ray->h_y += c->map.cell_size;
	ray->h_x = floor(c->player.x + (ray->h_y - c->player.y) / tan(ray->angle));
	ray->h_distance = get_distance(
			c->player.x, c->player.y, ray->h_x, ray->h_y);
}

void	init_distance_v(t_ctx *c, t_ray *ray)
{
	ray->v_x = floor(c->player.x / c->map.cell_size) * c->map.cell_size;
	if (ray->mfacing == SEAST || ray->mfacing == NEAST)
		ray->v_x += c->map.cell_size;
	ray->v_y = c->player.y + (ray->v_x - c->player.x) * tan(ray->angle);
	ray->v_distance = get_distance(
			c->player.x, c->player.y, ray->v_x, ray->v_y);
}

t_ray	cast_ray(t_ctx *c, double angle, int id)
{
	t_ray	ray;

	ray.id = id;
	ray.angle = angle;
	ray.mfacing = get_mfacing(angle);
	init_distance_h(c, &ray);
	init_distance_v(c, &ray);
	draw_rect(c, (t_rect){
		(ray.h_x - 1) * c->window.res,
		(ray.h_y - 1) * c->window.res,
		2,
		2,
		0x00d0ff
	});
	draw_rect(c, (t_rect){
		(ray.v_x - 1) * c->window.res,
		(ray.v_y - 1) * c->window.res,
		2,
		2,
		0x0000ff
	});
	find_wall_h(c, &ray);
	find_wall_v(c, &ray);
	if (ray.h_distance < ray.v_distance)
	{
		ray.distance = ray.h_distance;
		ray.x = ray.h_x;
		ray.y = ray.h_y;
	}
	else
	{
		ray.distance = ray.v_distance;
		ray.x = ray.v_x;
		ray.y = ray.v_y;
	}
	draw_rect(c, (t_rect){
		(ray.x - 1) * c->window.res,
		(ray.y - 1) * c->window.res,
		2,
		2,
		0x0000ff
	});
	return (ray);
}

t_ray *create_rays(t_ctx *c)
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
		// printf("Rayon N°%d, j'ai une distance de %fpx\n", i, rays[i].distance);
	}
	return (rays);
}
