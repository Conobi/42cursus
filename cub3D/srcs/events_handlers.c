/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:47:11 by conobi            #+#    #+#             */
/*   Updated: 2022/10/20 18:37:00 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	exit_process(t_ctx *c)
{
	free_ctx(c);
	exit(0);
	return (0);
}

static int	key_press(int keycode, t_ctx *c)
{
	if (keycode == KB_W)
		c->player.direction = 'U';
	else if (keycode == KB_S)
		c->player.direction = 'D';
	else if (keycode == KB_A)
		c->player.direction = 'L';
	else if (keycode == KB_D)
		c->player.direction = 'R';
	else if (keycode == KB_LEFT)
		c->player.angle -= to_radians(c->turn_speed);
	else if (keycode == KB_RIGHT)
		c->player.angle += to_radians(c->turn_speed);
	else if (keycode == KB_ESC)
		exit_process(c);
	refresh_handler(c);
	return (0);
}

static int	key_release(int keycode, t_ctx *c)
{
	if (keycode == KB_W
		|| keycode == KB_S
		|| keycode == KB_A
		|| keycode == KB_D
	)
		c->player.speed = 0;
	refresh_handler(c);
	return (0);
}

static int	mouse_move(int x, int y, t_ctx *c)
{
	(void)y;
	c->player.speed = 0;
	if (x < c->window.width * 0.5)
		c->player.angle -= to_radians(c->turn_speed);
	else
		c->player.angle += to_radians(c->turn_speed);
	refresh_handler(c);
	return (0);
}

void	event_listener(t_ctx *c)
{
	mlx_hook(c->window.id, ON_MOUSEMOVE, 1L << 6, mouse_move, c);
	mlx_hook(c->window.id, ON_KEYDOWN, 1L, key_press, c);
	mlx_hook(c->window.id, ON_KEYUP, 1L << 1, key_release, c);
	mlx_hook(c->window.id, ON_DESTROY, 0L, exit_process, c);
}
