/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 19:02:13 by conobi            #+#    #+#             */
/*   Updated: 2022/01/14 19:12:45 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	gradient(double long t, int a, int b, int chn)
{
	int	ret;

	ret = (hex2rgba(a).arr[chn] - hex2rgba(b).arr[chn])
		* t + hex2rgba(b).arr[chn];
	return (ret);
}

int	linear(double long t, int c, int d, int chn)
{
	double long	ret;

	ret = (double long)(hex2rgba(c).arr[chn]) / 255 * t;
	ret += (double long)(hex2rgba(d).arr[chn]) / 255;
	ret = (0.5 + 0.5 * cos(6.28318 * ret)) * 255;
	return ((int)ret);
}

static t_palette	palette(int pal_l, int pal_r, float pal_o)
{
	t_palette	ret;

	ret.l = pal_l;
	ret.r = pal_r;
	ret.o = pal_o;
	return (ret);
}

void	palette_set(t_context *con, int index)
{
	info_printer("Setting the palette...");
	if (index == 0)
		con->pal = palette(0xFFFFFF, 0x0054AA, 0.03);
	else if (index == 1)
		con->pal = palette(0xFFFFFF, 0x001933, 0.59);
	else if (index == 2)
		con->pal = palette(0xFFFFFF, 0xDABDAB, 1);
	else if (index == 3)
		con->pal = palette(0xFFFFFF, 0xDDAADD, 1);
	else if (index == 4)
		con->pal = palette(0x10FF00, 0xFF54AA, 1);
}
//		con->pal = palette(0xFFFFFF, 0x8855FF, 1);
