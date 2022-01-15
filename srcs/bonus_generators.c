/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_generators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 16:17:24 by conobi            #+#    #+#             */
/*   Updated: 2022/01/15 18:53:53 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

float	burning_ship(const t_pos pos, const t_context *con)
{
	t_complex	c;
	int			i;
	double long	szoom;

	szoom = 0.25;
	c.x = remap(con->midx, -1.685, -1.830) - con->zoom * szoom / 2;
	c.x += pos.i.x * con->zoom * szoom / pos.s.x;
	c.y = con->zoom * szoom * pos.s.y / pos.s.x;
	c.y = -1 * (c.y / 2 - remap(con->midy, 0, -0.065)
			- pos.i.y * c.y / pos.s.y);
	c.ox = c.x;
	c.oy = c.y;
	i = -1;
	while (++i < con->miters)
	{
		c.a = c.x * c.x - c.y * c.y;
		if (c.a >= 4)
			break ;
		c.b = fabs(2 * (double)c.x * (double)c.y);
		c.x = c.a + c.ox;
		c.y = c.b + c.oy;
	}
	return ((float)i / con->miters - con->pznum - con->pal.o);
}

// Aigle: (cox: -0.501401 coy: 0.254440) | c.b: 1.5 * fabs((double)c.x) * c.y;
float	eagle_brain(const t_pos pos, const t_context *con)
{
	t_complex	c;
	int			i;
	double long	szoom;

	szoom = 6;
	c.x = remap(con->midx, 1.75, -1.75) - con->zoom * szoom / 2;
	c.x += pos.i.x * con->zoom * szoom / pos.s.x;
	c.y = con->zoom * szoom * pos.s.y / pos.s.x;
	c.y = c.y / 2 - remap(con->midy, 1, -1) - pos.i.y * c.y / pos.s.y;
	i = -1;
	while (++i < con->miters)
	{
		c.a = c.x * c.x - c.y * c.y;
		if (c.a >= 4)
			break ;
		c.b = 1.5 * fabs((double)c.x) * c.y;
		c.x = c.a + 0.501401;
		c.y = c.b + 0.254440;
	}
	return ((float)i / con->miters - con->pznum - con->pal.o);
}

// Baobab (cox: -0.062032 coy: 0.341111)
// c.a: 2 * fabs((double)c.x) * c.y;
float	baobab(const t_pos pos, const t_context *con)
{
	t_complex	c;
	int			i;
	double long	szoom;

	szoom = 3.4;
	c.x = remap(con->midx, 1, -1) - con->zoom * szoom / 2;
	c.x += pos.i.x * con->zoom * szoom / pos.s.x;
	c.y = -1 * con->zoom * szoom * pos.s.y / pos.s.x;
	c.y = c.y / 2 - remap(con->midy, -0.8, 1.2) - pos.i.y * c.y / pos.s.y;
	i = -1;
	while (++i < con->miters)
	{
		c.a = c.x * c.x - c.y * c.y;
		if (c.a >= 4)
			break ;
		c.b = 2 * fabs((double)c.x) * c.y;
		c.x = c.a + 0.062932;
		c.y = c.b + 0.341111;
	}
	return ((float)i / con->miters - con->pznum - con->pal.o);
}

// Wobbly (cox: 1.096181 coy: 0.260977)
// -1.5 * fabs((double)c.x) * c.y; Mettre une palette multicolore
float	wobble(const t_pos pos, const t_context *con)
{
	t_complex	c;
	int			i;
	double long	szoom;

	szoom = 4.2;
	c.x = remap(con->midx, 1, -1) - con->zoom * szoom / 2;
	c.x += pos.i.x * con->zoom * szoom / pos.s.x;
	c.y = con->zoom * szoom * pos.s.y / pos.s.x;
	c.y = c.y / 2 - remap(con->midy, 0.8, -1.2) - pos.i.y * c.y / pos.s.y;
	i = -1;
	while (++i < con->miters)
	{
		c.a = c.x * c.x - c.y * c.y;
		if (c.a >= 4)
			break ;
		c.b = -1.5 * fabs((double)c.x) * c.y;
		c.x = c.a - 1.096181;
		c.y = c.b + 0.260977;
	}
	return ((float)i / con->miters - con->pznum - con->pal.o);
}
