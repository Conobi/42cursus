/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:48:12 by abastos           #+#    #+#             */
/*   Updated: 2022/08/16 19:24:15 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	display_fps(t_window *window)
{
	static clock_t	last_loop = 0;
	clock_t			this_loop;
	double			fps;

	this_loop = clock();
	fps = 1000 / (double)(this_loop - last_loop);
	fps *= 1000;
	last_loop = this_loop;
	printf("fps: %f\n", fps);
	mlx_string_put(window->mlx, window->id, 500, 10, 0xFF0000,
		ft_strjoin("fps: ", ft_itoa(fps)));
}

static void	move_player(t_ctx *c)
{
	double	new_x;
	double	new_y;

	new_x = c->player.x + (cos(c->player.angle) * c->player.speed);
	new_y = c->player.y + (sin(c->player.angle) * c->player.speed);
	// todo: calculate distance for collisions here
	if (out_of_bounds(c, floor(new_x / CELL_SIZE), floor(new_y / CELL_SIZE)))
		return ;
	c->player.x = new_x;
	c->player.y = new_y;
}

static void	display_hud(t_ctx *c)
{
	display_fps(&(c->window));
	mlx_string_put(c->window.mlx, c->window.id, 500, 20, 0xFF0000,
		ft_strjoin("angle: ", ft_itoa(c->player.angle)));
	mlx_string_put(c->window.mlx, c->window.id, 500, 30, 0xFF0000,
		ft_strjoin("x: ", ft_itoa(c->player.x)));
	mlx_string_put(c->window.mlx, c->window.id, 500, 40, 0xFF0000,
		ft_strjoin("y: ", ft_itoa(c->player.y)));
}

int	generate_frame(t_ctx *c)
{
	move_player(c);
	draw_map(c, (t_rmap){0, 0, SCALE, create_rays(c)});
	display_hud(c);
	return (0);
}
