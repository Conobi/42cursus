/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 15:38:01 by conobi            #+#    #+#             */
/*   Updated: 2022/04/06 17:42:56 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <complex.h>

float	mandelbrot(const t_pos pos, const t_context *con)
{
	t_complex	c;
	int			i;
	double long	szoom;

	szoom = 4.3;
	c.x = remap(con->midx, 2, -3.5) - con->zoom * szoom / 2;
	c.x += pos.i.x * con->zoom * szoom / pos.s.x;
	c.y = con->zoom * szoom * pos.s.y / pos.s.x;
	c.y = c.y / 2 - remap(con->midy, 1.25, -1.25) - pos.i.y * c.y / pos.s.y;
	c.ox = c.x;
	c.oy = c.y;
	i = -1;
	while (++i < con->miters)
	{
		c.a = c.x * c.x - c.y * c.y;
		if (c.x * c.x + c.y * c.y >= 4)
			break ;
		c.b = c.x * c.y;
		c.b += c.b;
		c.x = c.a + c.ox;
		c.y = c.b + c.oy;
	}
	return ((float)i / con->miters - con->pznum - con->pal.o);
}

float	julia(const t_pos pos, const t_context *con)
{
	t_complex	c;
	int			i;
	double long	szoom;

	szoom = 3.4;
	c.x = remap(con->midx, 1, -1) - con->zoom * szoom / 2;
	c.x += pos.i.x * con->zoom * szoom / pos.s.x;
	c.y = con->zoom * szoom * pos.s.y / pos.s.x;
	c.y = c.y / 2 - remap(con->midy, 1, -1) - pos.i.y * c.y / pos.s.y;
	i = -1;
	while (++i < con->miters)
	{
		c.a = c.x * c.x - c.y * c.y;
		if (c.x * c.x + c.y * c.y >= 4)
			break ;
		c.b = 2 * c.x * c.y;
		c.x = c.a + con->cox;
		c.y = c.b + con->coy;
	}
	return ((float)i / con->miters - con->pznum - con->pal.o);
}
