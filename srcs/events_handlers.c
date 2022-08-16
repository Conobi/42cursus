/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:47:11 by conobi            #+#    #+#             */
/*   Updated: 2022/08/16 19:10:50 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	key_press(int keycode, t_ctx *c)
{
	if (keycode == MVUP_KEY)
		c->player.speed = PLAYER_SPEED;
	else if (keycode == DVDW_KEY)
		c->player.speed = -PLAYER_SPEED;
	else if (keycode == MVR_KEY)
		c->player.angle -= to_radians(PLAYER_SPEED + 2);
	else if (keycode == MVL_KEY)
		c->player.angle += to_radians(PLAYER_SPEED + 2);
	else if (keycode == EXIT_KEY)
		exit (0);
	refresh_handler(c);
	return (0);
}

static int	key_release(int keycode, t_ctx *c)
{
	if (keycode == MVUP_KEY)
		c->player.speed = 0;
	else if (keycode == DVDW_KEY)
		c->player.speed = 0;
	refresh_handler(c);
	return (0);
}

void	event_listener(t_ctx *c)
{
	mlx_hook(c->window.id, 2, 0, key_press, c);
	mlx_hook(c->window.id, 3, 0, key_release, c);
}
