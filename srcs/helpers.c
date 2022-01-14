/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 17:56:37 by conobi            #+#    #+#             */
/*   Updated: 2022/01/14 19:00:23 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	pixel_put(t_context *con, int x, int y, int color)
{
	char	*dst;
	int		i;
	int		j;

	i = -1;
	while (++i < con->res)
	{
		j = -1;
		while (++j < con->res)
		{
			dst = con->img.addr + ((y + i) * con->img.line_length
					+ (x + j) * (con->img.bits_per_pixel / 8));
			*(unsigned int *)dst = color;
		}
	}
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

t_context	*set_func(int func_i, t_context *con,
				float (*func)(const t_pos, const t_context*))
{
	con->func_i = func_i;
	con->fractal_func = func;
	return (con);
}

double long	remap(double long input, double long low, double long high)
{
	double long	ret;

	ret = low + input * (high - low);
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
