/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgba.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 13:47:17 by conobi            #+#    #+#             */
/*   Updated: 2021/12/30 21:46:36 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	rgba2hex(int *color)
{
	return ((255 - color[3]) << 24 | color[0] << 16 | color[1] << 8 | color[2]);
}

int	*hex2rgba(int color)
{
	static int	ret[4];

	ret[3] = ((color >> 24) & 0xff) + 255;
	ret[0] = (color >> 16) & 0xff;
	ret[1] = (color >> 8) & 0xff;
	ret[2] = color & 0xff;
	return (ret);
}

int	rgba(int r, int g, int b, int a)
{
	static int	color[4];

	color[0] = r;
	color[1] = g;
	color[2] = b;
	color[3] = a;
	return (rgba2hex(color));
}

int	generate(float t, int a, int b, int (*gen)(float, int, int, int))
{
	int	color[4];
	int	chn;

	chn = -1;
	while (++chn < 4)
		color[chn] = (*gen)(t, a, b, chn);
	return (rgba2hex(color));
}
// static int	palette(float t)
// {
// 	int		a;
// 	int		b;
// 	int		c;
// 	int		d;
// 	float	ret;

// 	a = rgba(127, 127, 127, 255);
// 	b = rgba(127, 127, 127, 255);
// 	c = rgba(0, 511, 255, 255);
// 	d = rgba(127, 50, 63, 255);
// 	ret = a + b * cos(6.28318 * (c * t + d));
// 	return ((int)ret);
// }

// static int	palette(float t)
// {
// 	int		a;
// 	int		b;
// 	float	ret;

// 	a = rgba(0, 255, 255, 255);
// 	b = rgba(65, 208, 117, 255);
// 	ret = a + (b - a) * t;
// 	return ((int)ret);
// }
