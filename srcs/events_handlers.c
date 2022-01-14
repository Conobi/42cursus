/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:04:35 by conobi            #+#    #+#             */
/*   Updated: 2022/01/13 20:05:22 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom_move_reset(int key, t_context *con)
{
	if ((key == KB_RIGHT || key == KB_D) && con->midx > 0)
		con->midx -= 0.1 * con->zoom;
	else if ((key == KB_LEFT || key == KB_A) && con->midx < 1)
		con->midx += 0.1 * con->zoom;
	else if ((key == KB_UP || key == KB_W) && con->midy < 1)
		con->midy += 0.1 * con->zoom;
	else if ((key == KB_DOWN || key == KB_S) && con->midy > 0)
		con->midy -= 0.1 * con->zoom;
	else if (key == KB_SPACE)
	{
		con->zoom = 1;
		con->midx = 0.5;
		con->midy = 0.5;
		rem_printer("Resetting the view");
	}
}

void	zoom_mouse(int btn, int x, int y, t_context *con)
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
			* con->zoom / 5;
		con->midy += remap(1 - (double long)y / con->s.y, -0.5, 0.5)
			* con->zoom / 5;
	}
}

void	palette_change(int key, t_context *con)
{
	if (key == KB_PAD_1)
		palette_set(con, 0);
	else if (key == KB_PAD_2)
		palette_set(con, 1);
	else if (key == KB_PAD_3)
		palette_set(con, 2);
}

void	palette_locker(int key, t_context *con)
{
	if (key == KB_BACKSPACE)
	{
		con->pzlock *= -1;
		if (con->pzlock == -1)
			rem_printer("Locking the palette roller");
		else
			rem_printer("Unlocking the palette roller");
	}
}

void	resol_change(int key, t_context *con)
{
	if (key == KB_PAGE_DOWN && con->upsc < 5)
	{
		con->upsc += 1;
		rem_printer("Reducing the resolution...");
	}
	else if (key == KB_PAGE_UP && con->upsc > 1)
	{
		con->upsc -= 1;
		rem_printer("Increasing the resolution...");
	}
}

// void	space_debug(t_context *con)
// {
// 	if (con->midx == 0.5)
// 		con->midx = 1;
// 	else if (con->midx == 1)
// 		con->midx = 0;
// 	else
// 		con->midx = 0.5;
// 	if (con->midy == 0.5)
// 		con->midy = 1;
// 	else if (con->midy == 1)
// 		con->midy = 0;
// 	else
// 		con->midy = 0.5;
// }
