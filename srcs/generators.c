/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 15:38:01 by conobi            #+#    #+#             */
/*   Updated: 2021/12/31 15:43:19 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <complex.h>

int	gradient(float t, int a, int b, int chn)
{
	int	ret;
	int	color_a[4];
	int	color_b[4];

	ft_arrlcpy(color_a, hex2rgba(a), 3);
	ft_arrlcpy(color_b, hex2rgba(b), 3);
	ret = (color_a[chn] - color_b[chn]) * t + color_b[chn];
	return (ret);
}

int	linear(float t, int c, int d, int chn)
{
	float	ret;

	ret = (float)(hex2rgba(c)[chn]) / 255 * t;
	ret += (float)(hex2rgba(d)[chn]) / 255;
	ret = (0.5 + 0.5 * cos(6.28318 * ret)) * 255;
	return ((int)ret);
}

int	mandelbrot(const t_pos pos, const float zoom)
{
	t_complex	c;
	float		max;
	int			i;

	max = zoom * pos.sy / pos.sx;
	c.x = (-0.75 - zoom / 2) + pos.x * zoom / pos.sx;
	c.y = (0 + max / 2) - pos.y * max / pos.sy;
	c.ox = c.x;
	c.oy = c.y;
	i = -1;
	while (++i < 255)
	{
		c.a = c.x * c.x - c.y * c.y;
		c.b = 2 * c.x * c.y;
		c.x = c.a + c.ox;
		c.y = c.b + c.oy;
		if ((c.x * c.x + c.y * c.y) > 80)
			break ;
	}
	return (i);
}

// int	mandelbrot(int sx, int sy, int x, int y, float zoom)
// {
// 	long double	xr;
// 	long double	yr;
// 	long double	zx;
// 	long double	zy;
// 	long double	ox;
// 	long double	oy;
// 	long double	a;
// 	long double	b;
// 	long double	i;

// 	xr = zoom;
// 	yr = zoom;
// 	zx = (-0.65 - xr / 2) + x * xr / sx;
// 	zy = (0 + yr / 2) - y * yr / sy;
// 	ox = zx;
// 	oy = zy;
// 	i = -1;
// 	while (++i < 255)
// 	{
// 		a = zx * zx - zy * zy;
// 		b = 2 * zx * zy;
// 		zx = a + ox;
// 		zy = b + oy;
// 		// printf("%f %Lf\n", (double)(zx * zx + zy * zy), i);
// 		if ((zx * zx + zy * zy) > 4)
// 			break ;
// 	}
// 	return (i);
// }
