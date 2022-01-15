/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 23:23:05 by conobi            #+#    #+#             */
/*   Updated: 2022/01/15 19:53:44 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	kb_event(int key, t_context *con)
{
	zoom_move_reset(key, con);
	palette_change(key, con);
	lockers(key, con);
	resol_iter_change(key, con);
	if (key == KB_ESC)
		ender();
	refresh_handler(con);
	return (0);
}

static int	zoom_mouse(int btn, int x, int y, t_context *con)
{
	if (con->pznum < 0 && con->pzlock == 1)
		con->pzdir *= -1;
	if (btn == 4)
	{
		con->zoom = (double long)con->zoom * 0.9;
		if (con->pzlock == 1)
			con->pznum += 0.05 * con->pzdir;
	}
	else if (btn == 5)
	{
		con->zoom = (double long)con->zoom / 0.9;
		if (con->pzlock == 1)
			con->pznum -= 0.05 * con->pzdir;
	}
	if (btn == 4 || btn == 5)
	{
		con->midx += remap(1 - (double long)x / con->s.x, -0.5, 0.5)
			* con->zoom / 4;
		con->midy += remap(1 - (double long)y / con->s.y, -0.5, 0.5)
			* con->zoom / 4;
	}
	refresh_handler(con);
	return (0);
}

static int	mouse_hover(int x, int y, t_context *con)
{
	float	box;
	float	boy;
	float	nox;
	float	noy;

	if (con->holock == 1)
	{
		box = con->ox;
		boy = con->oy;
		nox = x;
		noy = y;
		if (nox >= box + 5 || nox <= box - 5)
			con->ox = nox;
		if (noy >= boy + 5 || noy <= boy - 5)
			con->oy = noy;
		if ((nox >= box + 5 || nox <= box - 5)
			|| (noy >= boy + 5 || noy <= boy - 5))
		{
			con->cox = (con->ox * con->zoom) / (con->s.x) - 0.204756;
			con->coy = (con->oy - con->s.y * 0.5
					* con->zoom) / (con->s.y) + 0.63;
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
	mlx_key_hook(con->win, kb_event, con);
	mlx_mouse_hook(con->win, zoom_mouse, con);
	mlx_hook(con->win, 2, 1L, zoom_kb, con);
	mlx_hook(con->win, CLOSE_EVENT, CLOSE_MASK, ender, con);
	if (con->func_i == 0)
		mlx_hook(con->win, 6L, 64L, mouse_hover, con);
}
