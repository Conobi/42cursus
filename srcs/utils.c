/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 17:56:37 by conobi            #+#    #+#             */
/*   Updated: 2021/12/28 20:09:11 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	rgba(int r, int g, int b, int a)
{
	return ((255 - a) << 24 | r << 16 | g << 8 | b);
}

int	interpolate(int color1, int color2, float fraction)
{
	unsigned char	r1;
	unsigned char	r2;
	unsigned char	g1;
	unsigned char	g2;
	unsigned char	b1;
	unsigned char	b2;

	r1 = (color1 >> 16) & 0xff;
	r2 = (color2 >> 16) & 0xff;
	g1 = (color1 >> 8) & 0xff;
	g2 = (color2 >> 8) & 0xff;
	b1 = color1 & 0xff;
	b2 = color2 & 0xff;
	return ((int)((r2 - r1) * fraction + r1) << 16 |
		(int)((g2 - g1) * fraction + g1) << 8 |
		(int)((b2 - b1) * fraction + b1));
}
