/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 17:56:37 by conobi            #+#    #+#             */
/*   Updated: 2022/01/05 13:29:02 by conobi           ###   ########lyon.fr   */
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

	ret.s.x = sx;
	ret.s.y = sy;
	ret.i.x = x;
	ret.i.y = y;
	return (ret);
}

t_context	*set_func(t_context *con,
				short (*func)(const t_pos, const t_context*))
{
	con->fractal_func = func;
	return (con);
}

// float	zoom_calc(float input)
// {
// 	float	ret;

// 	ret = 0.005 + input * (1.8 - 0.005);
// 	return (ret);
// }

float	remap(float input, float low, float high)
{
	float	ret;

	ret = low + input * (high - low);
	return (ret);
}

t_vec2	vec2(int x, int y)
{
	t_vec2	ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}

// t_chunk	chunk(t_vec2 s, t_vec2 e, t_context *con)
// {
// 	t_chunk	ret;

// 	ret.s = s;
// 	ret.e = e;
// 	ret.con = con;
// 	return (ret);
// }
