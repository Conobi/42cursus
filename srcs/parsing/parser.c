/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:47:22 by conobi            #+#    #+#             */
/*   Updated: 2022/10/06 22:37:18 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	map_parser(t_parser *parser_ctx, char **file)
{
	int		line;

	line = -1;
	while (file[++line])
	{
		if (file[line] && file[line][0] == '\n'
			&& parser_ctx->map_size_x <= 0 && parser_ctx->map_size_y <= 0)
			continue ;
		else if (is_valid_texture(nl_remove(file[line])))
			parse_texture(parser_ctx, nl_remove(file[line]));
		else if (is_valid_color(nl_remove(file[line])))
			parse_color(parser_ctx, nl_remove(file[line]));
		else if (is_valid_context(parser_ctx))
		{
			printf("Letzgong parsing\n");
			parse_ascii_map(parser_ctx, file, line);
			break ;
		}
		else
			return (false);
	}
	if (is_valid_context(parser_ctx) && is_valid_ascii(parser_ctx))
		return (true);
	return (false);
}

static void	init_parser(t_parser *parser_ctx)
{
	parser_ctx->file_err = false;
	parser_ctx->map_size_x = -1;
	parser_ctx->map_size_y = -1;
	parser_ctx->player_pos_x = -1;
	parser_ctx->player_pos_y = -1;
	parser_ctx->player_facing = -1;
	parser_ctx->f_color = -1;
	parser_ctx->c_color = -1;
	parser_ctx->debug = 0;
	parser_ctx->no_texture = (t_texture){NULL, 0, 0};
	parser_ctx->so_texture = (t_texture){NULL, 0, 0};
	parser_ctx->we_texture = (t_texture){NULL, 0, 0};
	parser_ctx->ea_texture = (t_texture){NULL, 0, 0};
}

void	free_ctx(t_parser *parser_ctx)
{
	int	i;

	if (parser_ctx->map_size_x > 0 || parser_ctx->map_size_y > 0)
	{
		i = -1;
		while (parser_ctx->map[++i])
			free(parser_ctx->map[i]);
		free(parser_ctx->map);
		parser_ctx->map = NULL;
		parser_ctx->map_size_x = -1;
		parser_ctx->map_size_y = -1;
	}
	if (parser_ctx->no_texture.img)
		free(parser_ctx->no_texture.img);
	if (parser_ctx->so_texture.img)
		free(parser_ctx->so_texture.img);
	if (parser_ctx->we_texture.img)
		free(parser_ctx->we_texture.img);
	if (parser_ctx->ea_texture.img)
		free(parser_ctx->ea_texture.img);
}

int	main(int argc, char **argv)
{
	char		**file_arr;
	t_parser	parser_ctx;

	init_parser(&parser_ctx);
	if (argc != 2 || !argv[1])
		return (print_err(22));
	if (ft_eq(argv[1], ".cub", 2) < 1)
		return (print_err(79));
	printf("------\nMap:\n");
	file_arr = unsplitable_file(argv[1]);
	if (file_arr && map_parser(&parser_ctx, file_arr))
		printf("---\nMAP OK\n");
	else
		printf("---\nMAP MEH\n");
	free_split(file_arr);
	free_ctx(&parser_ctx);
}
