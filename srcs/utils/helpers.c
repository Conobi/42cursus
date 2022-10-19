/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:33:52 by conobi            #+#    #+#             */
/*   Updated: 2022/10/17 19:28:31 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pixel_put(t_ctx *c, int x, int y, int color)
{
	char	*dst;

	dst = NULL;
	if (y >= 0 && x >= 0 && y < c->window.height && x < c->window.width)
	{
		dst = c->img.addr + (y * c->img.line_length
				+ x * (c->img.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	upscale(t_ctx *c)
{
	t_img	upscaled;
	char	*dst;
	int		x;
	int		y;
	int		xx;
	int		yy;
	int		draw_x;
	int		draw_y;
	int		color;

	upscaled.img = mlx_new_image(c->window.mlx,
			c->window.width * c->window.res, c->window.height * c->window.res);
	upscaled.addr = mlx_get_data_addr(upscaled.img, &upscaled.bits_per_pixel,
			&upscaled.line_length, &upscaled.endian);
	y = 0;
	draw_y = 0;
	c->img.width = c->window.width;
	c->img.height = c->window.height;
	while (y < c->window.height)
	{
		x = 0;
		draw_x = 0;
		while (x < c->window.width)
		{
			yy = 0;
			color = get_pixel_color_from_texture(c->img, x, y);
			while (yy < c->window.res)
			{
				xx = 0;
				while (xx < c->window.res)
				{
					if (yy >= 0 && xx >= 0 && yy < c->window.height * c->window.res && xx < c->window.width * c->window.res)
					{
						dst = upscaled.addr + ((draw_y + yy) * upscaled.line_length
								+ (draw_x + xx) * (upscaled.bits_per_pixel / 8));
						*(unsigned int *)dst = color;
					}
					xx++;
				}
				yy++;
			}
			x++;
			draw_x += c->window.res;
		}
		draw_y += c->window.res;
		y++;
	}
	c->img = upscaled;
}

double long	remap(double long input, double long low, double long high)
{
	double long	ret;

	ret = low + input * (high - low);
	return (ret);
}
