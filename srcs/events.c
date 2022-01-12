/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 23:23:05 by conobi            #+#    #+#             */
/*   Updated: 2022/01/12 03:27:46 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	key_event(int key, t_context *con)
{
	printf("Key number: %d for %p\n", key, con->win);
	printf("Debug alignement av: %Lf, %Lf\n", con->midx, con->midy);
	if ((key == KB_RIGHT || key == KB_D) && con->midx > 0)
		con->midx -= 0.1 * con->zoom;
	else if ((key == KB_LEFT || key == KB_A) && con->midx < 1)
		con->midx += 0.1 * con->zoom;
	else if ((key == KB_UP || key == KB_W) && con->midy < 1)
		con->midy += 0.1 * con->zoom;
	else if ((key == KB_DOWN || key == KB_S) && con->midy > 0)
		con->midy -= 0.1 * con->zoom;
	else if (key == KB_SPACE)
		space_debug(con);
	refresh_handler(con);
	printf("Debug alignement ap: %Lf, %Lf\n", con->midx, con->midy);
	return (0);
}

static int	mouse_event(int button, int x, int y, t_context *con)
{
	zoom_mouse(button, x, y, con);
	refresh_handler(con);
	return (0);
}

static int	mouse_hover(int x, int y, t_context *con)
{
	// double long	box;
	// double long	boy;

	// box = con->ox;
	// boy = con->oy;
	con->ox = 1 - (double long)x / con->s.x;
	con->oy = 1 - (double long)y / con->s.y;
	printf("(%Lf, %Lf)\n", con->ox, con->oy);
	refresh_handler(con);
	return (0);
}

void	event_listener(t_context *con)
{
	mlx_key_hook(con->win, key_event, con);
	mlx_mouse_hook(con->win, mouse_event, con);
	mlx_hook(con->win, CLOSE_EVENT, CLOSE_MASK, ender, con);
	mlx_hook(con->win, 6, 8192L, mouse_hover, con);
}
