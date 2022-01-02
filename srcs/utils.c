/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 17:56:37 by conobi            #+#    #+#             */
/*   Updated: 2022/01/01 21:13:10 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_pos	pos(int sx, int sy, int x, int y)
{
	t_pos	ret;

	ret.sx = sx;
	ret.sy = sy;
	ret.x = x;
	ret.y = y;
	ret.mx = -0.75;
	ret.my = 0;
	return (ret);
}

t_context	*set_func(t_context *con, short (*func)(t_pos, float))
{
	con->fractal_func = func;
	return (con);
}

float	zoom_calc(float input)
{
	float	ret;

	ret = 0.005 + input * (1.8 - 0.005);
	return (ret);
}
