/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:47:50 by conobi            #+#    #+#             */
/*   Updated: 2022/10/20 17:39:27 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ctx(t_ctx *c)
{
	c->window.height = 1080 * 0.5;
	c->window.width = 1920 * 0.5;
	c->window.res = 2;
	c->player.speed = 0;
	c->player.angle = 0;
	c->player.fov = 60;
	c->cell_size = 0;
	c->cell_map_size = 12;
	c->player.size = c->cell_map_size * 0.5;
	c->rays_num = c->window.width;
	c->target_speed = 1;
	c->turn_speed = 2;
	c->fog_color = 0x2f2d18;
}

void	init_parser(t_ctx *c)
{
	c->map_size_x = -1;
	c->map_size_y = -1;
	c->player.x = -1;
	c->player.y = -1;
	c->f_color = -1;
	c->c_color = -1;
	c->no_texture = (t_img){NULL, NULL, 0, 0, 0, 0, 0};
	c->so_texture = (t_img){NULL, NULL, 0, 0, 0, 0, 0};
	c->we_texture = (t_img){NULL, NULL, 0, 0, 0, 0, 0};
	c->ea_texture = (t_img){NULL, NULL, 0, 0, 0, 0, 0};
}
