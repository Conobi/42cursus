/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:04:35 by conobi            #+#    #+#             */
/*   Updated: 2022/01/12 02:50:03 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	space_debug(t_context *con)
{
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
}

void	zoom_mouse(int btn, int x, int y, t_context *con)
{
	static double	debugcnt = 1;

	if (btn == 4)
	{
		con->zoom = (double long)con->zoom * 0.9;
		debugcnt /= 0.9;
	}
	else if (btn == 5)
	{
		con->zoom = (double long)con->zoom / 0.9;
		debugcnt *= 0.9;
	}
	if (btn == 4 || btn == 5)
	{
		printf("Debug zoom: %Lf\net %Lf\n", con->zoom, (double long)0.9 * (double long)0.9);
		printf("On a zoomé %f fois \n", debugcnt);
		printf("Debug alignement av: %Lf, %Lf\n", con->midx, con->midy);
		con->midx += remap(1 - (double long)x / con->s.x, -0.5, 0.5)
			* con->zoom / 5;
		con->midy += remap(1 - (double long)y / con->s.y, -0.5, 0.5)
			* con->zoom / 5;
		printf("Debug alignement ap: %Lf, %Lf\n", con->midx, con->midy);
	}
}
