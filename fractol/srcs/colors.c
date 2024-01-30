/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 19:02:13 by conobi            #+#    #+#             */
/*   Updated: 2022/04/06 18:16:03 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	rgba2hex(t_rgba color)
{
	return ((255 - color.arr[3]) << 24 | color.arr[0] << 16
		| color.arr[1] << 8 | color.arr[2]);
}

t_rgba	hex2rgba(int color)
{
	t_rgba	ret;

	ret.arr[3] = ((color >> 24) & 0xff) + 255;
	ret.arr[0] = (color >> 16) & 0xff;
	ret.arr[1] = (color >> 8) & 0xff;
	ret.arr[2] = color & 0xff;
	return (ret);
}

int	generate(double t, t_context *con, int (*gen)(double long, int, int, int))
{
	t_rgba	color;
	int		chn;
	int		a;
	int		b;

	a = con->pal.l;
	b = con->pal.r;
	chn = -1;
	while (++chn < 4)
		color.arr[chn] = (*gen)(t, a, b, chn);
	color.arr[3] = 255;
	return (rgba2hex(color));
}

int	linear(double long t, int c, int d, int chn)
{
	double long	ret;

	ret = (double long)(hex2rgba(c).arr[chn]) / 255 * t;
	ret += (double long)(hex2rgba(d).arr[chn]) / 255;
	ret = (0.5 + 0.5 * cos(6.28318 * ret)) * 255;
	return ((int)ret);
}

void	palette_set(t_context *con, int index)
{
	info_printer("Setting the palette...");
	if (index == 0)
		con->pal = (t_palette){0xFFFFFF, 0x0054AA, 0.10};
	else if (index == 1)
		con->pal = (t_palette){0xFFFFFF, 0x001933, 0.59};
	else if (index == 2)
		con->pal = (t_palette){0xFFFFFF, 0xDABDAB, 0.32};
	else if (index == 3)
		con->pal = (t_palette){0xFFFFFF, 0xAE7722, 1};
	else if (index == 4)
		con->pal = (t_palette){0xFFFFFF, 0x6645CC, 1};
	else if (index == 5)
		con->pal = (t_palette){0xFFFFFF, 0xEEAA33, 1};
}
