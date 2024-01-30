/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:48:12 by abastos           #+#    #+#             */
/*   Updated: 2022/10/20 17:00:10 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	generate_frame(t_ctx *c)
{
	t_ray		*rays;

	rays = create_rays(c, c->player.fov, c->rays_num);
	c->player.hitboxes = create_rays(c, 360, 12);
	if (rays)
	{
		move_player(c);
		render(c, rays);
		draw_map(c, 25, 25);
		free(rays);
		free(c->player.hitboxes);
	}
	return (0);
}
