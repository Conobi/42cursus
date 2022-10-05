/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:44:39 by abastos           #+#    #+#             */
/*   Updated: 2022/10/05 16:44:38 by abastos          ###   ########lyon.fr   */
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
