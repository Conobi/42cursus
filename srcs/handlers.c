/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:23:09 by conobi            #+#    #+#             */
/*   Updated: 2021/12/30 02:42:16 by conobi           ###   ########lyon.fr   */
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
			pixel = generate(t, 0x00FFFF, 0x41D075, &gradient);
			pixel_put(&img, isx, isy, pixel);
		}
	}
	printf("\e[92m\e[1mDone\e[0m\n");
	return (img);
}
