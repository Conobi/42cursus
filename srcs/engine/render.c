/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:01:46 by abastos           #+#    #+#             */
/*   Updated: 2022/10/04 18:57:23 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	fix_fisheye(double distance, double angle, double player_angle)
{
	double	diff;

	diff = angle - player_angle;
	return (distance * cos(diff));
}

void	render(t_ctx *c, t_ray *rays)
{
	int		i;
	double	distance;
	int		wall_height;

	i = 0;
	while (i < c->rays_num)
	{
		distance = fix_fisheye(rays[i].distance, rays[i].angle, c->player.angle);
		// printf("distance %f\n", distance);
		wall_height = ((c->map.cell_size * 5) / distance) * 277;
		// printf("wall_height %d\n", wall_height);
		draw_rect(c, (t_rect){i, c->window.height / 2 - wall_height / 2, 1, wall_height, 0xffffff});
		draw_rect(c, (t_rect){i, c->window.height / 2 + wall_height / 2, 1, c->window.height / 2 - wall_height / 2, 0x262626});
		draw_rect(c, (t_rect){i, 0, 1, c->window.height / 2 - wall_height / 2, 0x262626});
		i++;
	}
}
