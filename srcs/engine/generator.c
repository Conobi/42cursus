/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:48:12 by abastos           #+#    #+#             */
/*   Updated: 2022/08/17 18:43:53 by conobi           ###   ########lyon.fr   */
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
	if (out_of_bounds(c, floor(new_x / CELL_SIZE), floor(new_y / CELL_SIZE)))
		return ;
	c->player.x = new_x;
	c->player.y = new_y;
}

int	generate_frame(t_ctx *c)
{
	move_player(c);
	draw_map(c, (t_rmap){0, 0, SCALE, create_rays(c)});
	return (0);
}
