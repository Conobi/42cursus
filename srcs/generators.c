/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 15:38:01 by conobi            #+#    #+#             */
/*   Updated: 2022/01/01 20:39:25 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <complex.h>

short	mandelbrot(const t_pos pos, const float zoom)
{
	t_complex	c;
	int			i;
	float		max;
	float		szoom;

	szoom = 4.3;
	max = zoom * szoom * pos.sy / pos.sx;
	c.x = (pos.mx - zoom * szoom / 2) + pos.x * zoom * szoom / pos.sx;
	c.y = (pos.my + max / 2) - pos.y * max / pos.sy;
	c.ox = c.x;
	c.oy = c.y;
	i = -1;
	while (++i < 255)
	{
		c.a = c.x * c.x - c.y * c.y;
		if (c.a >= 2)
			break ;
		c.b = 2 * c.x * c.y;
		c.x = c.a + c.ox;
		c.y = c.b + c.oy;
	}
	return (i);
}

short	julia(const t_pos pos, const float zoom)
{
	t_complex	c;
	int			i;
	float		max;
	float		szoom;

	szoom = 3.4;
	max = zoom * szoom * pos.sy / pos.sx;
	c.x = (0.75 + pos.mx - zoom * szoom / 2) + pos.x * zoom * szoom / pos.sx;
	c.y = (0 + max / 2) - pos.y * max / pos.sy;
	i = -1;
	while (++i < 255)
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

short	burning_ship(const t_pos pos, const float zoom)
{
	t_complex	c;
	int			i;
	float		max;
	float		szoom;

	szoom = 4.3;
	max = zoom * szoom * -1 * pos.sy / pos.sx;
	c.x = (0.4 + pos.mx - zoom * szoom / 2) + pos.x * zoom * szoom / pos.sx;
	c.y = (-0.55 + pos.my + max / 2) - pos.y * max / pos.sy;
	c.ox = c.x;
	c.oy = c.y;
	i = -1;
	while (++i < 255)
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
