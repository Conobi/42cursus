/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:26:16 by abastos           #+#    #+#             */
/*   Updated: 2022/10/17 14:28:33 by abastos          ###   ########lyon.fr   */
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

void	display_fps(t_ctx *c)
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
	draw_rect(c, (t_rect){
		100,
		100,
		30,
		30,
		0xFFF
	});
	mlx_string_put(c->window.mlx, c->window.id,
		c->window.width - 60, 15, c->f_color, join);
	free(join);
}

int	get_facing(double angle, bool is_vertical)
{
	if (is_vertical)
	{
		if (abs((int)floor((angle - M_PI * 0.5) / M_PI) % 2))
			return (EAST);
		return (WEST);
	}
	if (abs((int)floor(angle / M_PI) % 2))
		return (NORTH);
	return (SOUTH);
}

bool	out_of_bounds(t_ctx *c, int x, int y)
{
	return (x < 0 || x >= c->map_size_x || y < 0 || y >= c->map_size_y);
}

double	to_radians(int degrees)
{
	return ((degrees * M_PI) / 180);
}
