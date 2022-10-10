/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:55:49 by conobi            #+#    #+#             */
/*   Updated: 2022/10/08 22:59:53 by abastos          ###   ########lyon.fr   */
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
	printf("<%s> : %sTexture invalide.%s\n", str, RED_TXT, RESET_TXT);
	return (free_split(str_split));
}

static t_img	texture_from_file(t_ctx *c, char *str)
{
	t_img	ret;

	ret.img = mlx_xpm_file_to_image(c->window.mlx, str,
			&ret.height, &ret.width);
	// if (!texture->img)
	// 	// todo: throw error or import default texture
	ret.addr = mlx_get_data_addr(ret.img, &ret.bits_per_pixel,
			&ret.line_length, &ret.endian);
	return (ret);
}

void	parse_texture(t_ctx *c, char *str)
{
	char	**str_split;

	printf("<%s> : %sTexture valide !%s\n", str, GRN_TXT, RESET_TXT);
	str_split = ft_split(str, ' ');
	if (str_split
		&& str_split[0]
		&& str_split[1]
		&& !str_split[2]
	)
	{
		if (ft_eq(str_split[0], "NO", 0))
			c->no_texture = texture_from_file(c, str_split[1]);
		else if (ft_eq(str_split[0], "SO", 0))
			c->so_texture = texture_from_file(c, str_split[1]);
		else if (ft_eq(str_split[0], "WE", 0))
			c->we_texture = texture_from_file(c, str_split[1]);
		else if (ft_eq(str_split[0], "EA", 0))
			c->ea_texture = texture_from_file(c, str_split[1]);
	}
	free_split(str_split);
}
