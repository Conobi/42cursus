/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 19:24:32 by conobi            #+#    #+#             */
/*   Updated: 2022/10/14 14:42:47 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_valid_context(t_ctx *c)
{
	if (c->f_color >= 0
		&& c->c_color >= 0
		&& c->no_texture.img != NULL
		&& c->so_texture.img != NULL
		&& c->we_texture.img != NULL
		&& c->ea_texture.img != NULL)
	{
		// printf("- %sContexte valide%s -\n", GRN_TXT, RESET_TXT);
		return (true);
	}
	// printf("- %sContexte invalide%s -\n", RED_TXT, RESET_TXT);
	// printf("F: %04X\nC: %04X\n", c->f_color, c->c_color);
	// printf("F: %d\nC: %d\n",
	// 	c->f_color >= 0, c->c_color >= 0);
	// printf("NO: %d\nSO: %d\nWE: %d\nEA: %d\n",
	// 	c->no_texture.img != NULL, c->so_texture.img != NULL,
	// 	c->we_texture.img != NULL, c->ea_texture.img != NULL
	// 	);
	return (false);
}

bool	is_valid_ascii(t_ctx *c)
{
	// printf("MAP ASCII:\nSX: %d\nSY: %d\nPX: %f\nPY: %f\n", c->map_size_x,
		// c->map_size_y, c->player.x,
		// c->player.y);
	if (c->map_size_x > 0 && c->map_size_y > 0
		&& c->player.x > 0 && c->player.y > 0)
		return (true);
	return (false);
}

bool	are_texture_normalized(t_ctx *c)
{
	if (
		c->no_texture.width == c->so_texture.width
		&& c->so_texture.width == c->we_texture.width
		&& c->we_texture.width == c->ea_texture.width
	)
		return (true);
	print_err(NULL, "The textures must have the same size.", 5);
	return (false);
}
