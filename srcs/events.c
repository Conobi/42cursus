/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 23:23:05 by conobi            #+#    #+#             */
/*   Updated: 2022/01/14 19:11:48 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	key_event(int key, t_context *con)
{
	zoom_move_reset(key, con);
	palette_change(key, con);
	palette_locker(key, con);
	resol_change(key, con);
	if (key == KB_ESC)
		ender();
	// printf("Touche %d appuyée\n", key);
	refresh_handler(con);
	return (0);
}

int	key_hook(int button, int x, int y, t_context *con)
{
	zoom_mouse(button, x, y, con);
	refresh_handler(con);
	return (0);
}

static int	mouse_hover(int x, int y, t_context *con)
{
	float	box;
	float	boy;
	float	nox;
	float	noy;

	if (con->zoom > 0.30)
	{
		box = con->ox;
		boy = con->oy;
		nox = (double long)x / con->s.x;
		noy = (double long)y / con->s.y;
		if (nox >= box + 0.1 || nox <= box - 0.1)
			con->ox = nox;
		if (noy >= boy + 0.1 || noy <= boy - 0.1)
			con->oy = noy;
		if ((nox >= box + 0.1 || nox <= box - 0.1)
			|| (noy >= boy + 0.1 || noy <= boy - 0.1))
		{
			con->cox = remap(con->ox, 0.69, 0.71);
			con->coy = remap(con->oy, 0.27015, 0.27515);
			refresh_handler(con);
		}
	}
	return (0);
}

int	zoom_kb(int key, t_context *con)
{
	if ((key == KB_PAD_MINUS || key == KB_PAD_PLUS)
		&& con->pznum < 0 && con->pzlock == 1)
		con->pzdir *= -1;
	if (key == KB_PAD_MINUS)
	{
		con->zoom = (double long)con->zoom / 0.9;
		if (con->pzlock == 1)
			con->pznum -= 0.02 * con->pzdir;
	}
	if (key == KB_PAD_PLUS)
	{
		con->zoom = (double long)con->zoom * 0.9;
		if (con->pzlock == 1)
			con->pznum += 0.02 * con->pzdir;
	}
	return (0);
}

void	event_listener(t_context *con)
{
	mlx_key_hook(con->win, key_event, con);
	mlx_mouse_hook(con->win, key_hook, con);
	mlx_hook(con->win, 2, 1L, zoom_kb, con);
	mlx_hook(con->win, CLOSE_EVENT, CLOSE_MASK, ender, con);
	if (con->func_i == 0)
		mlx_hook(con->win, 6L, 64L, mouse_hover, con);
}
