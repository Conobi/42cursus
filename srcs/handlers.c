/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:23:09 by conobi            #+#    #+#             */
/*   Updated: 2021/12/28 20:24:39 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

t_data	test_handler(void *mlx, int size_x, int size_y)
{
	t_data	img;
	int		isx;
	int		isy;
	double	transparency;

	img.img = mlx_new_image(mlx, size_x, size_y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	isx = size_x;
	while (--isx >= 0)
	{
		isy = size_y;
		while (--isy >= 0)
		{
			transparency = (double)isx / (double)size_x;
			pixel_put(&img, isx, isy, interpolate(rgba(0, 255, 255, 255), rgba(65, 208, 117, 255), transparency));
		}
	}
	printf("\e[92m\e[1mDone\e[0m\n");
	return (img);
}
