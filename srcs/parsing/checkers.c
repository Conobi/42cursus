/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 19:24:32 by conobi            #+#    #+#             */
/*   Updated: 2022/10/05 16:43:54 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		&& parser_ctx->f_color >= 0
		&& parser_ctx->c_color >= 0
		&& parser_ctx->no_texture.img != NULL
		&& parser_ctx->so_texture.img != NULL
		&& parser_ctx->we_texture.img != NULL
		&& parser_ctx->ea_texture.img != NULL)
	{
		printf("- %sContexte valide%s -\n", GRN_TXT, RESET_TXT);
		return (true);
	}
	printf("- %sContexte invalide%s -\n", RED_TXT, RESET_TXT);
	printf("F: %04X\nC: %04X\n", parser_ctx->f_color, parser_ctx->c_color);
	printf("File err: %d\nF: %d\nC: %d\n", !parser_ctx->file_err,
		parser_ctx->f_color >= 0, parser_ctx->c_color >= 0);
	printf("NO: %d\nSO: %d\nWE: %d\nEA: %d\n",
		parser_ctx->no_texture.img != NULL, parser_ctx->so_texture.img != NULL,
		parser_ctx->we_texture.img != NULL, parser_ctx->ea_texture.img != NULL
		);
	return (false);
}

bool	is_valid_ascii(t_parser *parser_ctx)
{
	printf("MAP ASCII:\nSX: %d\nSY: %d\nPX: %d\nPY: %d\n", parser_ctx->map_size_x, parser_ctx->map_size_y, parser_ctx->player_pos_x, parser_ctx->player_pos_y);
	if (parser_ctx->map_size_x > 0 && parser_ctx->map_size_y > 0
		&& parser_ctx->player_pos_x > 0 && parser_ctx->player_pos_y > 0)
		return (true);
	return (false);
}
