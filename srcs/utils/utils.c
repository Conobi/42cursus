/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:26:16 by abastos           #+#    #+#             */
/*   Updated: 2022/10/07 15:26:30 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_pixel_color_from_texture(t_img texture, int x, int y)
{
	if (x >= 0 && x < texture.width
		&& y >= 0 && y < texture.height)
		return (*(int *)(texture.addr
			+ (4 * texture.width * (int)y) + (4 * (int)x)));
	return (0xFFE436);
}

void	display_fps(t_window window)
{
	static clock_t	last_loop = 0;
	clock_t			this_loop;
	double			fps;
	char			*tmp;
	char			*join;

	this_loop = clock();
	fps = (1000 / (double)(this_loop - last_loop)) * 1000.0;
	last_loop = this_loop;
	tmp = ft_itoa(fps);
	join = ft_strjoin("fps: ", tmp);
	free(tmp);
	mlx_string_put(window.mlx, window.id, window.width - 60, 15, 0xFF0000, join);
	free(join);
}

int	rgba2hex(t_rgba color)
{
	return ((255 - color.alpha) << 24 | color.red << 16
		| color.green << 8 | color.blue);
}

t_rgba	hex2rgba(int color)
{
	t_rgba	ret;

	ret.alpha = ((color >> 24) & 0xff) + 255;
	ret.red = (color >> 16) & 0xff;
	ret.green = (color >> 8) & 0xff;
	ret.blue = color & 0xff;
	return (ret);
}

int	view_distance(int color, float correction)
{
	t_rgba	s;

	s = hex2rgba(color);
	if (correction < 0)
	{
		correction += 1;
		s.red *= correction;
		s.green *= correction;
		s.blue *= correction;
	}
	else
	{
		s.red = (255 - s.red) * correction + s.red;
		s.green = (255 - s.green) * correction + s.green;
		s.blue = (255 - s.blue) * correction + s.blue;
	}
	return (rgba2hex(s)); // todo: fix color overflow
}

int	get_facing(double angle, bool is_vertical)
{
	if (is_vertical)
	{
		if (abs((int)floor((angle - M_PI / 2) / M_PI) % 2))
			return (EAST);
		return (WEST);
	}
	if (abs((int)floor(angle / M_PI) % 2))
		return (NORTH);
	return (SOUTH);
}

bool	out_of_bounds(t_ctx *c, int x, int y)
{
	return (x < 0 || x >= c->map_size_y || y < 0 || y >= c->map_size_x);
}

double	to_radians(int degrees)
{
	return ((degrees * M_PI) / 180);
}
