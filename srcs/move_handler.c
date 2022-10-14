/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:59:54 by conobi            #+#    #+#             */
/*   Updated: 2022/10/14 18:29:40 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	angle_from_facing(t_ctx *c, int facing)
{
	int	is_up;
	int	is_right;

	is_up = abs((int)floor(c->player.angle / M_PI) % 2);
	is_right = abs((int)floor((c->player.angle - M_PI / 2) / M_PI) % 2);
	if (is_right && facing == NORTH)
		return (to_radians(0));
	else if (is_right && facing == SOUTH)
		return (to_radians(360));
	else if (!is_right && facing == NORTH)
		return (to_radians(180));
	else if (!is_right && facing == SOUTH)
		return (to_radians(-180));
	else if (is_up && (facing == WEST || facing == EAST))
		return (to_radians(270));
	else if (facing == WEST || facing == EAST)
		return (to_radians(90));
	return (0);
}

static double	get_angle_from_rays(
	t_ray one, t_ray two, t_ray three, t_ctx *viva_lalgerie
)
{
	if (one.distance < viva_lalgerie->hitbox_max)
		return (angle_from_facing(viva_lalgerie, one.facing));
	else if (two.distance < viva_lalgerie->hitbox_max)
		return (angle_from_facing(viva_lalgerie, two.facing));
	else if (three.distance < viva_lalgerie->hitbox_max)
		return (angle_from_facing(viva_lalgerie, three.facing));
	return (viva_lalgerie->player.angle);
}

static double	wall_licker(t_ctx *c)
{
	if (c->player.direction == 'U')
		return (get_angle_from_rays(
				c->player.hitboxes[5],
				c->player.hitboxes[6],
				c->player.hitboxes[7], c
			));
	if (c->player.direction == 'D')
		return (get_angle_from_rays(
				c->player.hitboxes[11],
				c->player.hitboxes[0],
				c->player.hitboxes[1], c
			));
	if (c->player.direction == 'L')
		return (get_angle_from_rays(
				c->player.hitboxes[2],
				c->player.hitboxes[3],
				c->player.hitboxes[4], c
			));
	if (c->player.direction == 'R')
		return (get_angle_from_rays(
				c->player.hitboxes[8],
				c->player.hitboxes[9],
				c->player.hitboxes[10], c
			));
	return (c->player.angle);
}

static void	set_new_player_xy(
	t_ctx *c, char dir, double *new_x, double *new_y
)
{
	double	adjust;
	double	licked_angle;

	licked_angle = wall_licker(c);
	adjust = 0;
	if (dir != '\0')
		c->player.speed = c->target_speed;
	if (dir == 'D')
		c->player.speed = -c->target_speed;
	else if (dir == 'L')
		adjust = to_radians(-90);
	else if (dir == 'R')
		adjust = to_radians(90);
	*new_x = c->player.x + (cos(licked_angle + adjust) * c->player.speed);
	*new_y = c->player.y + (sin(licked_angle + adjust) * c->player.speed);
}

void	move_player(t_ctx *c)
{
	double	new_x;
	double	new_y;

	set_new_player_xy(c, c->player.direction, &new_x, &new_y);
	if (!is_air(c, floor(new_x / c->cell_size), floor(new_y / c->cell_size)))
		return ;
	c->player.direction = '\0';
	c->player.x = new_x;
	c->player.y = new_y;
}
