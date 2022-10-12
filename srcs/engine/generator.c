/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:48:12 by abastos           #+#    #+#             */
/*   Updated: 2022/10/12 18:11:56 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_player(t_ctx *c, t_ray *rays)
{
	double	new_x;
	double	new_y;

	new_x = c->player.x + (cos(c->player.angle) * c->player.speed);
	new_y = c->player.y + (sin(c->player.angle) * c->player.speed);
	if (!is_air(c, floor(new_x / c->cell_size), floor(new_y / c->cell_size)))
		return ;
	if (c->player.speed > 0
		&& (rays[c->rays_num / 2].distance < c->cell_size / 2
			|| rays[c->rays_num / 4].distance < c->cell_size / 2
			|| rays[c->window.width - c->rays_num / 4].distance < c->cell_size / 2))
		return ;
	c->player.x = new_x;
	c->player.y = new_y;
}

int	generate_frame(t_ctx *c)
{
	t_ray	*rays;

	rays = create_rays(c);
	if (rays)
	{
		move_player(c, rays);
		render(c, rays);
		free(rays);
		draw_map(c, (t_rmap){0, 0, NULL});
	}
	return (0);
}
