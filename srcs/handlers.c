/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:31:13 by conobi            #+#    #+#             */
/*   Updated: 2022/08/19 20:01:40 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	display_fps(t_window *window)
// {
// 	static clock_t	last_loop = 0;
// 	clock_t			this_loop;
// 	double			fps;

// 	this_loop = clock();
// 	fps = 1000 / (double)(this_loop - last_loop);
// 	fps *= 1000;
// 	last_loop = this_loop;
// 	printf("fps: %f\n", fps);
// 	mlx_string_put(window->mlx, window->id, 500, 10, 0xFF0000,
// 		ft_strjoin("fps: ", ft_itoa(fps)));
// }

static void	display_hud(t_ctx *c)
{
	// display_fps(&(c->window));
	mlx_string_put(c->window.mlx, c->window.id, 500, 20, 0xFF0000,
		ft_strjoin("angle: ", ft_itoa(c->player.angle)));
	mlx_string_put(c->window.mlx, c->window.id, 500, 30, 0xFF0000,
		ft_strjoin("x: ", ft_itoa(c->player.x)));
	mlx_string_put(c->window.mlx, c->window.id, 500, 40, 0xFF0000,
		ft_strjoin("y: ", ft_itoa(c->player.y)));
}

t_img	image_handler(t_ctx *c)
{
	c->img.img = mlx_new_image(c->window.mlx,
			c->window.width, c->window.height);
	c->img.addr = mlx_get_data_addr(c->img.img, &c->img.bits_per_pixel,
			&c->img.line_length, &c->img.endian);
	generate_frame(c);
	display_hud(c);
	return (c->img);
}

void	refresh_handler(t_ctx *c)
{
	mlx_destroy_image(c->window.mlx, c->img.img);
	c->img = image_handler(c);
	mlx_put_image_to_window(c->window.mlx, c->window.id, c->img.img, 0, 0);
}
