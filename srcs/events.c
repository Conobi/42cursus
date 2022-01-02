/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 23:23:05 by conobi            #+#    #+#             */
/*   Updated: 2022/01/01 22:14:26 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	key_event(int keycode, t_context *con)
{
	printf("Key number: %d for %p\n", keycode, con->win);
	return (0);
}

static int	mouse_event(int button, int x, int y, t_context *con)
{
	// printf("Button [%d] ; Coords: (%d, %d)\n", button, x, y);
	// printf("Zoom: %f\n", con->zoom);
	x = x;
	y = y;
	if (button == 4 && con->inzoom < 1)
		con->inzoom -= 0.05;
	else if (button == 5 && con->inzoom > 0)
		con->inzoom += 0.05;
	if (button == 4 || button == 5)
	{
		// mlx_destroy_image(con->mlx, con->img.img);
		con->img = handler(con);
		mlx_put_image_to_window(con->mlx, con->win, con->img.img, 0, 0);
		// printf("Nouveau zoom: %f\n", con->zoom);
	}
	return (0);
}

void	event_listener(t_context *con)
{
	mlx_key_hook(con->win, key_event, con);
	mlx_mouse_hook(con->win, mouse_event, con);
}
