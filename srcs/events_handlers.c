/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:47:11 by conobi            #+#    #+#             */
/*   Updated: 2022/08/28 02:18:49 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	key_press(int keycode, t_ctx *c)
{
	if (keycode == KB_W)
		c->player.speed = c->target_speed;
	else if (keycode == KB_S)
		c->player.speed = -c->target_speed;
	else if (keycode == KB_A)
		c->player.angle -= to_radians(c->target_speed + 2);
	else if (keycode == KB_D)
		c->player.angle += to_radians(c->target_speed + 2);
	else if (keycode == KB_ESC)
		exit (0);
	refresh_handler(c);
	return (0);
}

static int	key_release(int keycode, t_ctx *c)
{
	if (keycode == KB_W)
		c->player.speed = 0;
	else if (keycode == KB_S)
		c->player.speed = 0;
	refresh_handler(c);
	return (0);
}

void	event_listener(t_ctx *c)
{
	mlx_hook(c->window.id, 2, 1L, key_press, c);
	mlx_hook(c->window.id, 3, 1L << 1, key_release, c);
}
