/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:48:12 by abastos           #+#    #+#             */
/*   Updated: 2022/10/05 19:51:05 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	draw_rays(t_ctx *c, t_ray *rays)
// {
// 	t_ray	ray;
// 	int		i;

// 	i = 0;
// 	while (i < c->rays_num)
// 	{
// 		ray = rays[i];
// 		// if (ray.id % 10 == 0)
// 		// {
// 		draw_line(c, (t_line){
// 			c->player.x * c->window.res,
// 			c->player.y * c->window.res,
// 			(c->player.x + cos(ray.angle) * ray.distance) * c->window.res,
// 			(c->player.y + sin(ray.angle) * ray.distance) * c->window.res,
// 			0xFF6C34
// 		});
// 		// }
// 		i++;
// 	}
// }

static void	move_player(t_ctx *c)
{
	double	new_x;
	double	new_y;

	new_x = c->player.x + (cos(c->player.angle) * c->player.speed);
	new_y = c->player.y + (sin(c->player.angle) * c->player.speed);
	if (!is_air(c, floor(new_x / c->map.cell_size), floor(new_y / c->map.cell_size)))
		return ;
	c->player.x = new_x;
	c->player.y = new_y;
}

int	generate_frame(t_ctx *c)
{
	t_ray	*rays;

	move_player(c);
	rays = create_rays(c);
	render(c, rays);
	draw_map(c, (t_rmap){0, 0, NULL});
	// draw_rays(c, rays);
	return (0);
}
