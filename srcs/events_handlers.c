/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:04:35 by conobi            #+#    #+#             */
/*   Updated: 2022/01/15 19:47:47 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom_move_reset(int key, t_context *con)
{
	if ((key == KB_RIGHT || key == KB_D))
		con->midx -= 0.1 * con->zoom;
	else if ((key == KB_LEFT || key == KB_A))
		con->midx += 0.1 * con->zoom;
	else if ((key == KB_UP || key == KB_W))
		con->midy += 0.1 * con->zoom;
	else if ((key == KB_DOWN || key == KB_S))
		con->midy -= 0.1 * con->zoom;
	else if (key == KB_SPACE)
	{
		con->zoom = 1;
		con->midx = 0.5;
		con->midy = 0.5;
		info_printer("Resetting the view");
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
	else if (key == KB_PAD_4)
		palette_set(con, 3);
	else if (key == KB_PAD_5)
		palette_set(con, 4);
	else if (key == KB_PAD_6)
		palette_set(con, 5);
}

void	lockers(int key, t_context *con)
{
	if (key == KB_BACKSPACE)
	{
		con->pzlock *= -1;
		if (con->pzlock == -1)
			info_printer("Locking the palette roller");
		else
			info_printer("Unlocking the palette roller");
	}
	if (key == KB_PAD_DOT && con->func_i == 0)
	{
		con->holock *= -1;
		if (con->holock == -1)
			info_printer("Locking the julia roller");
		else
			info_printer("Unlocking the julia roller");
		printf("The roller is set at (cox: %f coy: %f)\n", con->cox, con->coy);
	}
}

void	resol_iter_change(int key, t_context *con)
{
	if (key == KB_PAD_DIVIDE && con->miters > 32)
	{
		con->miters -= 32;
		info_printer("Reducing iterations...");
	}
	else if (key == KB_PAD_MULTIPLY && con->miters < 384)
	{
		con->miters += 32;
		info_printer("Increasing iterations...");
	}
	else if (key == KB_PAGE_DOWN && con->res < 5)
	{
		con->res += 1;
		info_printer("Reducing the resolution...");
	}
	else if (key == KB_PAGE_UP && con->res > 1)
	{
		con->res -= 1;
		info_printer("Increasing the resolution...");
	}
}

// void	space_debug(int key, t_context *con)
// {
// 	if (key == KB_SPACE)
// 	{
// 		if (con->midx == 0.5)
// 			con->midx = 1;
// 		else if (con->midx == 1)
// 			con->midx = 0;
// 		else
// 			con->midx = 0.5;
// 		if (con->midy == 0.5)
// 			con->midy = 1;
// 		else if (con->midy == 1)
// 			con->midy = 0;
// 		else
// 			con->midy = 0.5;
// 	}
// }
