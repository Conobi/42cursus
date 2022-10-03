/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 19:24:32 by conobi            #+#    #+#             */
/*   Updated: 2022/10/03 15:40:32 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	free_split(char **str_split)
{
	int	i;

	i = -1;
	if (!str_split)
		return (false);
	while (str_split[++i])
		free(str_split[i]);
	free(str_split);
	return (false);
}

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

// static void	debug_split(char **split)
// {
// 	int	i;

// 	i = -1;
// 	while (split[++i])
// 		printf("%s|", split[i]);
// 	printf("\n");
// }

bool	is_valid_context(t_parser *parser_ctx)
{
	if (!parser_ctx->file_err
		&& parser_ctx->map_size_x
		&& parser_ctx->map_size_y
		&& parser_ctx->f_color >= 0
		&& parser_ctx->c_color >= 0
		&& parser_ctx->no_texture
		&& parser_ctx->so_texture
		&& parser_ctx->we_texture
		&& parser_ctx->ea_texture)
		return (true);
	return (false);
}

bool	is_valid_ascii(t_parser *parser_ctx)
{
	parser_ctx->debug += 0;
	return (true);
}
