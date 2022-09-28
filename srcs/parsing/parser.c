/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:47:22 by conobi            #+#    #+#             */
/*   Updated: 2022/09/28 20:04:25 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_texture(t_parser *parser_ctx, char *str)
{
	return ;
}

void	parse_color(t_parser *parser_ctx, char *str)
{
	return ;
}

void	parse_ascii_map(t_parser *parser_ctx, char **file, int line)
{
	return ;
}

static bool	map_parser(t_parser *parser_ctx, char **file)
{
	int		line;

	line = -1;
	while (file[++line])
	{
		if (is_valid_texture(file[line]))
			parse_texture(parser_ctx, file[line]);
		else if (is_valid_color(file[line]))
			parse_color(parser_ctx, file[line]);
		else if (file[line] != NULL && is_valid_context(parser_ctx))
		{
			parse_ascii_map(parser_ctx, file, line);
			break ;
		}
		else if (file[line] == NULL)
			continue ;
		else
			return (false);
	}
	return (false);
	if (is_valid_context(parser_ctx) && is_valid_ascii(parser_ctx))
		return (true);
}

int	main(int argc, char **argv)
{
	char		*map;
	char		**map_splited;
	t_parser	parser_ctx;

	if (argc != 2)
		return (print_err(22));
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
