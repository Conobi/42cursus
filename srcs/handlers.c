/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:23:09 by conobi            #+#    #+#             */
/*   Updated: 2021/12/31 17:29:13 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_data	test_handler(void *mlx, int size_x, int size_y)
{
	t_data	img;
	int		isx;
	int		isy;
	double	t;
	int		pixel;

	img.img = mlx_new_image(mlx, size_x, size_y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	isx = size_x;
	while (--isx >= 0)
	{
		isy = size_y;
		while (--isy >= 0)
		{
			t = (double)isx / (double)size_x;
			pixel = generate(t, 0xFFFFFF, 0x001933, &linear);
			pixel_put(&img, isx, isy, pixel);
		}
	}
	printf("\e[92m\e[1mDone\e[0m\n");
	return (img);
}

t_data	mandelbrot_handler(void *mlx, int size_x, int size_y)
{
	t_data	img;
	int		isx;
	int		isy;
	float	t;
	int		color;

	img.img = mlx_new_image(mlx, size_x, size_y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	isx = size_x;
	while (--isx >= 0)
	{
		isy = size_y;
		while (--isy >= 0)
		{
			t = (double)mandelbrot(pos(size_x, size_y, isx, isy), 3.4) / 255;
			color = generate(t - 0.59, 0xFFFFFF, 0x001933, &linear);
			pixel_put(&img, isx, isy, color);
		}
	}
	printf("\e[92m\e[1mDone\e[0m\n");
	return (img);
}

//	color = generate(t, 0xFFFFFF, 0x001933, &linear);
//	color = generate(t, 0xFFFFFF, 0x0054aa, &linear);
// color = generate(t - 1, 0x7f7f7f, 0x7f333f, &linear);
