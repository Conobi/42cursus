/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:48:12 by abastos           #+#    #+#             */
/*   Updated: 2022/10/04 18:57:51 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_player(t_ctx *c)
{
	double	new_x;
	double	new_y;

	new_x = c->player.x + (cos(c->player.angle) * c->player.speed);
	new_y = c->player.y + (sin(c->player.angle) * c->player.speed);
	// todo: calculate distance for collisions here
	if (!is_air(c, floor(new_x / c->map.cell_size), floor(new_y / c->map.cell_size)))
		return ;
	c->player.x = new_x;
	c->player.y = new_y;
}

int	generate_frame(t_ctx *c)
{
	t_ray	*rays;

	move_player(c);
	printf("---\n");
	rays = create_rays(c);
	render(c, rays);
	draw_map(c, (t_rmap){0, 0, rays});
	return (0);
}
