/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:44:39 by abastos           #+#    #+#             */
/*   Updated: 2022/10/17 14:09:59 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(t_ctx *c, t_line line)
{
	double	delta_x;
	double	delta_y;
	double	pixel_x;
	double	pixel_y;
	int		pixels;

	delta_x = line.to_x - line.x;
	delta_y = line.to_y - line.y;
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta_x /= pixels;
	delta_y /= pixels;
	pixel_x = line.x;
	pixel_y = line.y;
	while (pixels)
	{
		pixel_put(c, pixel_x, pixel_y, line.color);
		pixel_x += delta_x;
		pixel_y += delta_y;
		--pixels;
	}
}

typedef struct s_tmp
{
	double	delta_x;
	double	delta_y;
	double	pixel_x;
	double	pixel_y;
	int		pixels;
	int		i;
}	t_tmp;

void	draw_line_gradient(
	t_ctx *c, t_line line, int from_color, int to_color
	)
{
	t_tmp	t;

	t.delta_x = line.to_x - line.x;
	t.delta_y = line.to_y - line.y;
	t.pixels = sqrt((t.delta_x * t.delta_x) + (t.delta_y * t.delta_y));
	t.delta_x /= t.pixels;
	t.delta_y /= t.pixels;
	t.pixel_x = line.x;
	t.pixel_y = line.y;
	t.i = -1;
	while (++t.i < t.pixels)
	{
		pixel_put(c, t.pixel_x, t.pixel_y,
			rgba2hex(linear_gradient(
					hex2rgba(from_color),
					hex2rgba(to_color),
					(float)t.i / t.pixels
					)
				)
			);
		t.pixel_x += t.delta_x;
		t.pixel_y += t.delta_y;
	}
}

void	draw_rect(t_ctx *c, t_rect rect)
{
	int	i;
	int	j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
		{
			pixel_put(c, j, i, rect.color);
			j++;
		}
		++i;
	}
}
