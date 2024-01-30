/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 19:24:32 by conobi            #+#    #+#             */
/*   Updated: 2022/10/20 16:06:37 by abastos          ###   ########lyon.fr   */
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
		return (true);
	return (false);
}

bool	is_valid_ascii(t_ctx *c)
{
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
