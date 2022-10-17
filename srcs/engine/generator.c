/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:48:12 by abastos           #+#    #+#             */
/*   Updated: 2022/10/14 19:17:51 by conobi           ###   ########lyon.fr   */
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
		draw_map(c, (t_rmap){0, 0, NULL});
		if (c->player.hitboxes)
			free(c->player.hitboxes);
	}
	return (0);
}

// int	generate_frame(t_ctx *c)
// {
// 	int		x;
// 	int		y;

// 	y = -1;
// 	while (++y < c->window.height)
// 	{
// 		x = -1;
// 		while (++x < c->window.width)
// 		{
// 			// printf("%f\n", (float)((float)x / c->window.width));
// 			pixel_put(c, x, y,
// 				rgba2hex(
// 					linear_gradient((t_rgba){255, 242, 217, 255}, (t_rgba){123, 200, 151, 255}, (float)x / c->window.width)
// 				)
// 			);
// 		}
// 	}
// 	return (0);
// }
