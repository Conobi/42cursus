/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:31:13 by conobi            #+#    #+#             */
/*   Updated: 2022/10/05 19:34:54 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	image_handler(t_ctx *c)
{
	c->img.img = mlx_new_image(c->window.mlx,
			c->window.width, c->window.height);
	c->img.addr = mlx_get_data_addr(c->img.img, &c->img.bits_per_pixel,
			&c->img.line_length, &c->img.endian);
	generate_frame(c);
	return (c->img);
}

void	refresh_handler(t_ctx *c)
{
	mlx_destroy_image(c->window.mlx, c->img.img);
	c->img = image_handler(c);
	mlx_put_image_to_window(c->window.mlx, c->window.id, c->img.img, 0, 0);
	display_fps(c->window);
}
