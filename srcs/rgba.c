/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgba.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 13:47:17 by conobi            #+#    #+#             */
/*   Updated: 2022/01/13 00:12:11 by conobi           ###   ########lyon.fr   */
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

int	rgba(int r, int g, int b, int a)
{
	t_rgba	color;

	color.arr[0] = r;
	color.arr[1] = g;
	color.arr[2] = b;
	color.arr[3] = a;
	return (rgba2hex(color));
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
// static int	palette(double long t)
// {
// 	int		a;
// 	int		b;
// 	int		c;
// 	int		d;
// 	double long	ret;

// 	a = rgba(127, 127, 127, 255);
// 	b = rgba(127, 127, 127, 255);
// 	c = rgba(0, 511, 255, 255);
// 	d = rgba(127, 50, 63, 255);
// 	ret = a + b * cos(6.28318 * (c * t + d));
// 	return ((int)ret);
// }

// static int	palette(double long t)
// {
// 	int		a;
// 	int		b;
// 	double long	ret;

// 	a = rgba(0, 255, 255, 255);
// 	b = rgba(65, 208, 117, 255);
// 	ret = a + (b - a) * t;
// 	return ((int)ret);
// }
