/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgba.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 13:47:17 by conobi            #+#    #+#             */
/*   Updated: 2021/12/29 16:21:20 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	rgba2hex(t_rgba color)
{
	return ((255 - color.a) << 24 | color.r << 16 | color.g << 8 | color.b);
}

t_rgba	hex2rgba(int color)
{
	t_rgba	ret;

	ret.a = ((color >> 24) & 0xff) + 255;
	ret.r = (color >> 16) & 0xff;
	ret.g = (color >> 8) & 0xff;
	ret.b = color & 0xff;
	return (ret);
}

int	rgba(int r, int g, int b, int a)
{
	t_rgba	color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return (rgba2hex(color));
}

int	generate(float t, int a, int b, int (*gen)(float, int, int, char))
{
	t_rgba	color;

	color.r = (*gen)(t, a, b, 'r');
	color.g = (*gen)(t, a, b, 'g');
	color.b = (*gen)(t, a, b, 'b');
	color.a = (*gen)(t, a, b, 'a');
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
