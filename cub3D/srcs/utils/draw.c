/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:44:39 by abastos           #+#    #+#             */
/*   Updated: 2022/10/17 15:12:53 by abastos          ###   ########lyon.fr   */
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
			linear_gradient(
				from_color,
				to_color,
				(float)t.i / t.pixels,
				false
				)
			);
		t.pixel_x += t.delta_x;
		t.pixel_y += t.delta_y;
	}
}

void	draw_rect_dim(t_ctx *c, t_rectdim rect)
{
	int	x;
	int	y;

	y = rect.y;
	while (y < rect.y + rect.height)
	{
		x = rect.x;
		while (x < rect.x + rect.width)
		{
			if (x > rect.x_min && x < rect.x_max
				&& y > rect.y_min && y < rect.y_max)
				pixel_put(c, x, y, rect.color);
			x++;
		}
		++y;
	}
}

void	draw_rect(t_ctx *c, t_rect rect)
{
	int	x;
	int	y;

	y = rect.y;
	while (y < rect.y + rect.height)
	{
		x = rect.x;
		while (x < rect.x + rect.width)
		{
			pixel_put(c, x, y, rect.color);
			x++;
		}
		++y;
	}
}

void	draw_rect_gradient(t_ctx *c, t_rect rect, int from_color, int to_color)
{
	int	x;
	int	y;
	int	color;

	y = rect.y;
	while (y < rect.y + rect.height)
	{
		color = linear_gradient(from_color, to_color,
				(float)(y - rect.y) / rect.height, false);
		x = rect.x;
		while (x < rect.x + rect.width)
		{
			pixel_put(c, x, y, color);
			x++;
		}
		++y;
	}
}
