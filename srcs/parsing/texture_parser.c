/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:55:49 by conobi            #+#    #+#             */
/*   Updated: 2022/10/06 22:38:25 by conobi           ###   ########lyon.fr   */
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

static t_texture	texture_from_file(char *str)
{
	void	*mlx;
	void	*img;
	int		height;
	int		width;

	mlx = mlx_init();
	img = mlx_xpm_file_to_image(mlx, str, &height, &width);
	free(mlx);
	return ((t_texture){img, height, width});
}

void	parse_texture(t_parser *parser_ctx, char *str)
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
			parser_ctx->no_texture = texture_from_file(str_split[1]);
		else if (ft_eq(str_split[0], "SO", 0))
			parser_ctx->so_texture = texture_from_file(str_split[1]);
		else if (ft_eq(str_split[0], "WE", 0))
			parser_ctx->we_texture = texture_from_file(str_split[1]);
		else if (ft_eq(str_split[0], "EA", 0))
			parser_ctx->ea_texture = texture_from_file(str_split[1]);
	}
	free_split(str_split);
}
