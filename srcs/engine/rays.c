/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 20:52:40 by abastos           #+#    #+#             */
/*   Updated: 2022/09/13 19:25:37 by conobi           ###   ########lyon.fr   */
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

void	find_wall_3(t_ctx *c, t_ray *ray)
{
	int	computed_x;
	int	computed_y;
	int	x_factor;
	int	y_factor;
	double	tan_y;

	tan_y = tan(ray->angle);
	computed_x = floor(ray->x / c->map.cell_size);
	computed_y = floor(ray->y / c->map.cell_size);
	printf("[%d, %d], player: (%d, %d) [%d, %d]\n", computed_x, computed_y, (int)c->player.x, (int)c->player.y, (int)floor(c->player.x / c->map.cell_size), (int)floor(c->player.y / c->map.cell_size));
	x_factor = 1;
	y_factor = 1;
	// if (ray->mfacing == SWEST || ray->mfacing == NWEST)
	// 	x_factor *= -1;
	// if (ray->mfacing == SEAST || ray->mfacing == SWEST)
	// 	y_factor *= -1;
	while (
		computed_x > 0 && computed_x < c->map.width
		&& computed_y > 0 && computed_y < c->map.height
		&& c->map.raw[computed_y][computed_x] == '0'
	)
	{
		ray->y += tan_y * c->map.cell_size * y_factor;
		ray->x += c->map.cell_size * x_factor;
		// printf("Rayon N°%d [%d,%d] -> ", ray->id, computed_x, computed_y);
		if (ray->x * c->window.res < c->window.width && ray->y * c->window.res < c->window.height)
			draw_rect(c, (t_rect){
				(ray->x - 2) * c->window.res,
				(ray->y - 2) * c->window.res,
				4,
				4,
				0x00f055
			});
		computed_x += x_factor;
		computed_y += y_factor;
	}
	if (ray->x * c->window.res < c->window.width && ray->y * c->window.res < c->window.height)
		draw_rect(c, (t_rect){
			(ray->x - 2) * c->window.res,
			(ray->y - 2) * c->window.res,
			4,
			4,
			0xff00ff
		});
	ray->distance = get_distance(c->player.x, c->player.y, ray->x, ray->y);
}

typedef struct s_temp {
	double	h_distance;
	double	v_distance;
	int		hor_x_init;
	int		hor_y_init;
	int		ver_x_init;
	int		ver_y_init;
}	t_temp;

void	init_distance(t_ctx *c, t_ray *ray)
{
	t_temp	t;

	t.hor_y_init = floor(c->player.y / c->map.cell_size) * c->map.cell_size;
	if (ray->mfacing == SWEST || ray->mfacing == SEAST)
		t.hor_y_init += c->map.cell_size;
	t.hor_x_init = floor(c->player.x
			+ (t.hor_y_init - c->player.y) / tan(ray->angle));
	t.ver_x_init = floor(c->player.x / c->map.cell_size) * c->map.cell_size;
	if (ray->mfacing == SEAST || ray->mfacing == NEAST)
		t.ver_x_init += c->map.cell_size;
	t.ver_y_init = c->player.y + (t.ver_x_init - c->player.x) * tan(ray->angle);
	t.h_distance = get_distance(
			c->player.x, c->player.y, t.hor_x_init, t.hor_y_init);
	t.v_distance = get_distance(
			c->player.x, c->player.y, t.ver_x_init, t.ver_y_init);
	ray->distance = t.v_distance;
	ray->x = t.ver_x_init;
	ray->y = t.ver_y_init;
	if (t.h_distance < t.v_distance)
	{
		ray->distance = t.h_distance;
		ray->x = t.hor_x_init;
		ray->y = t.hor_y_init;
	}
}

t_ray	cast_ray(t_ctx *c, double angle, int id)
{
	t_ray	ray;

	ray.id = id;
	ray.angle = angle;
	ray.mfacing = get_mfacing(angle);
	init_distance(c, &ray);
	draw_rect(c, (t_rect){
		(ray.x - 2) * c->window.res,
		(ray.y - 2) * c->window.res,
		4,
		4,
		0x0000ff
	});
	find_wall_3(c, &ray);
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
