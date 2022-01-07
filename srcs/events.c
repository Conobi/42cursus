/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 23:23:05 by conobi            #+#    #+#             */
/*   Updated: 2022/01/05 18:48:27 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	key_event(int keycode, t_context *con)
{
	printf("Key number: %d for %p\n", keycode, con->win);
	if (keycode == 124 && con->midx > 0)
		con->midx -= 0.1 * con->inzoom;
	else if (keycode == 123 && con->midx < 1)
		con->midx += 0.1 * con->inzoom;
	else if (keycode == 126 && con->midy < 1)
		con->midy += 0.1 * con->inzoom;
	else if (keycode == 125 && con->midy > 0)
		con->midy -= 0.1 * con->inzoom;
	else if (keycode == 49)
	{
		printf("Debug alignement av: %f, %f\n", con->midx, con->midy);
		if (con->midx == 0.5)
			con->midx = 1;
		else if (con->midx == 1)
			con->midx = 0;
		else
			con->midx = 0.5;
		if (con->midy == 0.5)
			con->midy = 1;
		else if (con->midy == 1)
			con->midy = 0;
		else
			con->midy = 0.5;
		mlx_destroy_image(con->mlx, con->img.img);
	}
	con->img = thread_handler(con);
	mlx_put_image_to_window(con->mlx, con->win, con->img.img, 0, 0);
	printf("Debug alignement ap: %f, %f\n", con->midx, con->midy);
	return (0);
}

static int	mouse_event(int button, int x, int y, t_context *con)
{
	x += 0;
	y += 0;
	if (button == 4 && con->inzoom > 0)
		con->inzoom -= 0.05;
	else if (button == 5 && con->inzoom < 1)
		con->inzoom += 0.05;
	if (button == 4 || button == 5)
	{
		// printf("Debug alignement av: %f, %f\n", con->midx, con->midy);
		con->midx = 1 - (float)x / con->s.x;
		con->midy = 1 - (float)y / con->s.y;
		// if (button == 4 && con->inzoom <= 0)
		// 	printf("Limite min atteinte \n");
		// else if (button == 5 && con->inzoom >= 1)
		// 	printf("Limite max atteinte \n");
		// mlx_destroy_image(con->mlx, con->img.img);
		con->img = thread_handler(con);
		mlx_put_image_to_window(con->mlx, con->win, con->img.img, 0, 0);
		// printf("Debug alignement ap: %f, %f\n", con->midx, con->midy);
	}
	return (0);
}

void	event_listener(t_context *con)
{
	mlx_key_hook(con->win, key_event, con);
	mlx_mouse_hook(con->win, mouse_event, con);
}
