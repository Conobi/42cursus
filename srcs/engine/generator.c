/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:48:12 by abastos           #+#    #+#             */
/*   Updated: 2022/09/01 16:17:04 by conobi           ###   ########lyon.fr   */
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
	// if (out_of_bounds(c, floor(new_x / c->map.cell_size), floor(new_y / c->map.cell_size)))
	// 	return ;
	c->player.x = new_x;
	c->player.y = new_y;
}

int	generate_frame(t_ctx *c)
{
	move_player(c);
	draw_map(c, (t_rmap){0, 0, NULL});
	return (0);
}
