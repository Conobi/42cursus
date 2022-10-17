/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:48:12 by abastos           #+#    #+#             */
/*   Updated: 2022/10/17 14:25:03 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	generate_frame(t_ctx *c)
{
	t_ray	*rays;

	rays = create_rays(c, c->player.fov, c->rays_num);
	c->player.hitboxes = create_rays(c, 360, 12);
	if (rays)
	{
		move_player(c);
		render(c, rays);
		free(rays);
		draw_map(c, 25, 25);
	}
	return (0);
}
