/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameloop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:48:12 by abastos           #+#    #+#             */
/*   Updated: 2022/08/16 13:30:43 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	display_fps(t_window *window)
{
	static clock_t	last_loop = 0;
	clock_t			this_loop;
	double			fps;

	this_loop = clock();
	fps = 1000 / (double)(this_loop - last_loop) * 1000.0;
	last_loop = this_loop;
	printf("fps: %f\n", fps);
	mlx_string_put(window->mlx, window->id, 500, 10, 0xFF0000,
		ft_strjoin("fps: ", ft_itoa(fps)));
}

void	moove_player(t_ctx *c)
{
	double	new_x;
	double	new_y;

	new_x = c->player->x + (cos(c->player->angle) * c->player->speed);
	new_y = c->player->y + (sin(c->player->angle) * c->player->speed);
	// todo: calculate distance for collisions here
	if (out_of_bounds(c, floor(new_x / CELL_SIZE), floor(new_y / CELL_SIZE)))
		return ;
	c->player->x = new_x;
	c->player->y = new_y;
}

void	display_hud(t_ctx *c)
{
	display_fps(c->window);
	mlx_string_put(c->window->mlx, c->window->id, 500, 20, 0xFF0000,
		ft_strjoin("angle: ", ft_itoa(c->player->angle)));
	mlx_string_put(c->window->mlx, c->window->id, 500, 30, 0xFF0000,
		ft_strjoin("x: ", ft_itoa(c->player->x)));
	mlx_string_put(c->window->mlx, c->window->id, 500, 40, 0xFF0000,
		ft_strjoin("y: ", ft_itoa(c->player->y)));
}

int	request_animation_frame(t_ctx *c)
{
	mlx_clear_window(c->window->mlx, c->window->id);
	moove_player(c);
	draw_map(c, (t_rmap){0, 0, SCALE, create_rays(c)});
	display_hud(c);
	return (0);
}

int	key_press(int keycode, t_ctx *c)
{
	if (keycode == MVUP_KEY)
		c->player->speed = PLAYER_SPEED;
	else if (keycode == DVDW_KEY)
		c->player->speed = -PLAYER_SPEED;
	else if (keycode == MVR_KEY)
		c->player->angle -= to_radians(PLAYER_SPEED + 2);
	else if (keycode == MVL_KEY)
		c->player->angle += to_radians(PLAYER_SPEED + 2);
	else if (keycode == EXIT_KEY)
		exit (0);
	return (0);
}

int	key_release(int keycode, t_ctx *c)
{
	if (keycode == MVUP_KEY)
		c->player->speed = 0;
	else if (keycode == DVDW_KEY)
		c->player->speed = 0;
	return (0);
}

void	gameloop(t_ctx *c)
{
	// mlx_hook(c->window->id, 17, 0, kill_process, NULL);
	mlx_hook(c->window->id, 2, 0, key_press, c);
	mlx_hook(c->window->id, 3, 0, key_release, c);
	// mlx_hook(data->win->id, 3, 0, idle_render, data);
	mlx_loop_hook(c->window->mlx, request_animation_frame, c);
	mlx_loop(c->window->mlx);
}
