/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:47:54 by abastos           #+#    #+#             */
/*   Updated: 2022/08/16 19:16:37 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	graph_manager(t_ctx *c)
{
	c->window.id = mlx_new_window(c->window.mlx,
			c->window.width, c->window.height, "minimap");
	c->img = image_handler(c);
	mlx_put_image_to_window(c->window.mlx, c->window.id, c->img.img, 0, 0);
	event_listener(c);
	mlx_loop(c->window.mlx);
}

int	main(void)
{
	t_ctx	c;

	init_ctx(&c);
	graph_manager(&c);
}
