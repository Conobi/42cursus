/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:44:39 by abastos           #+#    #+#             */
/*   Updated: 2022/08/26 18:29:22 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	normalize_coord(t_ctx *c, int i, bool is_x)
{
	if (i < 0)
		return (0);
	if (is_x && i >= c->window.width)
		return (c->window.width - 1);
	if (!is_x && i >= c->window.height)
		return (c->window.height - 1);
	return (i);
}

void	draw_line(t_ctx *c, t_line line)
{
	double	delta_x;
	double	delta_y;
	double	pixel_x;
	double	pixel_y;
	int		pixels;

	line = (t_line){
		normalize_coord(c, line.x, true), normalize_coord(c, line.y, false),
		normalize_coord(c, line.to_x, true),
		normalize_coord(c, line.to_y, false), line.color};
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

void	draw_rect(t_ctx *c, t_rect rect)
{
	int	i;
	int	j;

	rect = (t_rect){
		normalize_coord(c, rect.x, true),
		normalize_coord(c, rect.y, false),
		normalize_coord(c, rect.width, true),
		normalize_coord(c, rect.height, false),
		rect.color
	};
	i = rect.y;
	while (i < rect.y + rect.height && i < c->window.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width && j < c->window.width)
			pixel_put(c, j++, i, rect.color);
		++i;
	}
}

// printf("Win x max: %d\tWin y max: %d\tFrom: [%d,%d]\tTo: [%d, %d]\n", c->window.width, c->window.height, line.x, line.y, line.to_x, line.to_y);
