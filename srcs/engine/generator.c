/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:48:12 by abastos           #+#    #+#             */
/*   Updated: 2022/10/14 15:11:14 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	generate_frame(t_ctx *c)
{
	t_ray	*rays;

	printf("%f %f\n", c->player.x, c->player.y);
	rays = create_rays(c, c->player.fov, c->rays_num);
	c->player.hitboxes = create_rays(c, 360, 12);
	if (rays)
	{
		move_player(c);
		// free(c->player.hitboxes);
		render(c, rays);
		free(rays);
		draw_map(c, 0, 0);
	}
	return (0);
}
