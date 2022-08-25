/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:33:52 by conobi            #+#    #+#             */
/*   Updated: 2022/08/25 18:36:21 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pixel_put(t_ctx *c, int x, int y, int color)
{
	char	*dst;
	int		i;
	int		j;

	i = -1;
	while (++i < c->window.res)
	{
		j = -1;
		while (++j < c->window.res)
		{
			if ((x + j) < c->window.width && (y + i) < c->window.height)
				dst = c->img.addr + ((y + i) * c->img.line_length
					+ (x + j) * (c->img.bits_per_pixel / 8));
			*(unsigned int *)dst = color;
		}
	}
}

double long	remap(double long input, double long low, double long high)
{
	double long	ret;

	ret = low + input * (high - low);
	return (ret);
}
