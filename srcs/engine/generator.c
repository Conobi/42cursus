/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:48:12 by abastos           #+#    #+#             */
/*   Updated: 2022/10/13 15:35:08 by conobi           ###   ########lyon.fr   */
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
		// free(c->player.hitboxes);
		render(c, rays);
		free(rays);
		draw_map(c, (t_rmap){0, 0, NULL});
	}
	return (0);
}
