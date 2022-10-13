/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:59:54 by conobi            #+#    #+#             */
/*   Updated: 2022/10/13 19:30:34 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_new_player_xy(
	t_ctx *c, char dir, double *new_x, double *new_y
)
{
	double	adjust;

	adjust = 0;
	if (dir != '\0')
		c->player.speed = c->target_speed;
	if (dir == 'D')
		c->player.speed = -c->target_speed;
	else if (dir == 'L')
		adjust = to_radians(-90);
	else if (dir == 'R')
		adjust = to_radians(90);
	*new_x = c->player.x + (cos(c->player.angle + adjust) * c->player.speed);
	*new_y = c->player.y + (sin(c->player.angle + adjust) * c->player.speed);
}

bool	is_too_close(t_ctx *c)
{
	if (c->player.direction == 'U')
		if (
			c->player.hitboxes[5].distance < c->cell_size / 4
			|| c->player.hitboxes[6].distance < c->cell_size / 4
			|| c->player.hitboxes[7].distance < c->cell_size / 4
		)
			return (true);
	if (c->player.direction == 'D')
		if (
			c->player.hitboxes[11].distance < c->cell_size / 4
			|| c->player.hitboxes[0].distance < c->cell_size / 4
			|| c->player.hitboxes[1].distance < c->cell_size / 4
		)
			return (true);
	if (c->player.direction == 'L')
		if (
			c->player.hitboxes[2].distance < c->cell_size / 4
			|| c->player.hitboxes[3].distance < c->cell_size / 4
			|| c->player.hitboxes[4].distance < c->cell_size / 4
		)
			return (true);
	if (c->player.direction == 'R')
		if (
			c->player.hitboxes[8].distance < c->cell_size / 4
			|| c->player.hitboxes[9].distance < c->cell_size / 4
			|| c->player.hitboxes[10].distance < c->cell_size / 4
		)
			return (true);
	return (false);
}

void	move_player(t_ctx *c)
{
	double	new_x;
	double	new_y;

	set_new_player_xy(c, c->player.direction, &new_x, &new_y);
	if (!is_air(c, floor(new_x / c->cell_size), floor(new_y / c->cell_size)))
		return ;
	if (is_too_close(c))
		return ;
	c->player.direction = '\0';
	c->player.x = new_x;
	c->player.y = new_y;
}
