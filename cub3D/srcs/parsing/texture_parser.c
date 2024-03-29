/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:55:49 by conobi            #+#    #+#             */
/*   Updated: 2022/10/20 16:07:28 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_valid_texture(char *str)
{
	char	**str_split;

	str_split = ft_split(str, ' ');
	if (str_split
		&& str_split[0]
		&& str_split[1]
		&& !str_split[2]
		&& (
			ft_eq(str_split[0], "NO", 0)
			|| ft_eq(str_split[0], "SO", 0)
			|| ft_eq(str_split[0], "WE", 0)
			|| ft_eq(str_split[0], "EA", 0)
		)
	)
	{
		free_split(str_split);
		return (true);
	}
	return (free_split(str_split));
}

static t_img	texture_from_file(t_ctx *c, char *str)
{
	t_img	ret;

	ret.addr = NULL;
	ret.endian = 0;
	ret.line_length = 0;
	ret.bits_per_pixel = 0;
	ret.height = 0;
	ret.width = 0;
	ret.img = mlx_xpm_file_to_image(c->window.mlx, str,
			&ret.height, &ret.width);
	if (ret.img && ret.height == ret.width)
		ret.addr = mlx_get_data_addr(ret.img, &ret.bits_per_pixel,
				&ret.line_length, &ret.endian);
	else
		print_err(str, "Is not a working texture file", 5);
	return (ret);
}

void	parse_texture(t_ctx *c, char *str)
{
	char	**str_split;

	str_split = ft_split(str, ' ');
	if (str_split
		&& str_split[0]
		&& str_split[1]
		&& !str_split[2]
	)
	{
		if (ft_eq(str_split[0], "NO", 0))
		{
			c->no_texture = texture_from_file(c, str_split[1]);
			if (c->no_texture.height == c->no_texture.width)
				c->cell_size = c->no_texture.width;
		}
		else if (ft_eq(str_split[0], "SO", 0))
			c->so_texture = texture_from_file(c, str_split[1]);
		else if (ft_eq(str_split[0], "WE", 0))
			c->we_texture = texture_from_file(c, str_split[1]);
		else if (ft_eq(str_split[0], "EA", 0))
			c->ea_texture = texture_from_file(c, str_split[1]);
	}
	free_split(str_split);
}
