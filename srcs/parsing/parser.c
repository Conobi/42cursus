/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:47:22 by conobi            #+#    #+#             */
/*   Updated: 2022/10/05 19:29:10 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	map_parser(t_parser *parser_ctx, int fd)
{
	char	*line;

	line = ft_gnl(fd);
	if (!line)
		return (false);
	while (line)
	{
		if (line == NULL
			&& parser_ctx->map_size_x <= 0 && parser_ctx->map_size_y <= 0)
			continue ;
		else if (is_valid_texture(line))
			parse_texture(parser_ctx, line);
		else if (is_valid_color(line))
			parse_color(parser_ctx, line);
		else if (is_valid_context(parser_ctx) && !is_valid_ascii(parser_ctx))
		{
			printf("Letzgong parsing\n");
			parse_ascii_map(parser_ctx, fd);
			break ;
		}
		else
			break ;
	}
	free(line);
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

int	main(int argc, char **argv)
{
	char		*map;
	char		**map_splited;
	t_parser	parser_ctx;

	init_parser(&parser_ctx);
	if (argc != 2 || !argv[1])
		return (print_err(22));
	if (ft_eq(argv[1], ".cub", 2) < 1)
		return (print_err(79));
	printf("------\nMap:\n");
	map = load_file(argv[1]);
	map_splited = ft_split(map, '\n');
	free(map);
	if (map_splited && map_parser(&parser_ctx, map_splited))
		printf("---\nMAP OK\n");
	else
		printf("---\nMAP MEH\n");
	free(map_splited);
}
