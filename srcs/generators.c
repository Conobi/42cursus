/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 15:38:01 by conobi            #+#    #+#             */
/*   Updated: 2022/01/02 18:43:17 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <complex.h>

short	mandelbrot(const t_pos pos, const t_context *con)
{
	t_complex	c;
	int			i;
	float		szoom;

	szoom = 4.3;
	c.x = remap(con->midx, 2, -3.5) - con->zoom * szoom / 2;
	c.x += pos.x * con->zoom * szoom / pos.sx;
	c.y = con->zoom * szoom * pos.sy / pos.sx;
	c.y = c.y / 2 - remap(con->midy, 1.25, -1.25) - pos.y * c.y / pos.sy;
	c.ox = c.x;
	c.oy = c.y;
	i = -1;
	while (++i < 512)
	{
		c.a = c.x * c.x - c.y * c.y;
		if (c.x * c.x + c.y * c.y >= 2)
			break ;
		c.b = 2 * c.x * c.y;
		c.x = c.a + c.ox;
		c.y = c.b + c.oy;
	}
	return (i);
}

short	julia(const t_pos pos, const t_context *con)
{
	t_complex	c;
	int			i;
	float		szoom;

	szoom = 3.4;
	c.x = remap(con->midx, 1, -1) - con->zoom * szoom / 2;
	c.x += pos.x * con->zoom * szoom / pos.sx;
	c.y = con->zoom * szoom * pos.sy / pos.sx;
	c.y = c.y / 2 - remap(con->midy, 1, -1) - pos.y * c.y / pos.sy;
	i = -1;
	while (++i < 512)
	{
		c.a = c.x * c.x - c.y * c.y;
		if (c.a >= 2)
			break ;
		c.b = 2 * c.x * c.y;
		c.x = c.a - 0.7;
		c.y = c.b + 0.27015;
	}
	return (i);
}

short	burning_ship(const t_pos pos, const t_context *con)
{
	t_complex	c;
	int			i;
	float		szoom;

	szoom = 4.3;
	c.x = (0.4 + con->midx - con->zoom * szoom / 2);
	c.x += pos.x * con->zoom * szoom / pos.sx;
	c.y = con->zoom * szoom * -1 * pos.sy / pos.sx;
	c.y = (-0.55 + con->midy + c.y / 2) - pos.y * c.y / pos.sy;
	c.ox = c.x;
	c.oy = c.y;
	i = -1;
	while (++i < 512)
	{
		c.a = c.x * c.x - c.y * c.y;
		if (c.a >= 2)
			break ;
		c.b = fabs(2 * c.x * c.y);
		c.x = c.a + c.ox;
		c.y = c.b + c.oy;
	}
	return (i);
}
