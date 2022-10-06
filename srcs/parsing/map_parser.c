/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:56:56 by conobi            #+#    #+#             */
/*   Updated: 2022/10/06 22:38:52 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	free_ascii_map(t_parser *parser_ctx)
{
	int	i;

	i = -1;
	printf("On reset la map !\n");
	parser_ctx->map_size_x = -1;
	parser_ctx->map_size_y = -1;
	parser_ctx->player_pos_x = -1;
	parser_ctx->player_pos_y = -1;
	parser_ctx->player_facing = -1;
	if (parser_ctx->map_size_x > 0 || parser_ctx->map_size_y > 0)
	{
		printf("On free la map !\n");
		while (parser_ctx->map[++i])
			free(parser_ctx->map[i]);
		free(parser_ctx->map);
	}
	return (false);
}

short	type_of_char(char c)
{
	if (c == '1' || c == ' ')
		return (0);
	else if (c == '0')
		return (1);
	else if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (2);
	return (-1);
}

bool	set_map_values(t_parser *parser_ctx, const char c, int x, int y)
{
	if (c == '0')
		parser_ctx->map[x][y] = 0;
	else if (c == ' ' || c == '1')
		parser_ctx->map[x][y] = 1;
	else if ((c == 'N' || c == 'S' || c == 'W' || c == 'E')
		&& parser_ctx->player_pos_x == -1
		&& parser_ctx->player_pos_y == -1)
	{
		parser_ctx->map[x][y] = 0;
		parser_ctx->player_pos_x = x;
		parser_ctx->player_pos_y = y;
	}
	else
		return (free_ascii_map(parser_ctx));
	if (c == 'N')
		parser_ctx->player_facing = NORTH;
	else if (c == 'S')
		parser_ctx->player_facing = SOUTH;
	else if (c == 'W')
		parser_ctx->player_facing = WEST;
	else if (c == 'E')
		parser_ctx->player_facing = EAST;
	return (true);
}

bool	is_valid_boundary(char **file, int line, int x, int y)
{
	int	len_plus;
	int	len_minus;

	len_plus = 0;
	if (file[line + 1] != NULL)
		len_plus = ft_strlen(file[line + 1]);
	len_minus = 0;
	if (line > 0 && file[line - 1] != NULL)
		len_minus = ft_strlen(file[line - 1]);
	if (type_of_char(file[line][y]) > 0)
	{
		if (x == 0 || y == 0
			|| y + 1 >= len_plus
			|| y + 1 >= len_minus
			|| !file[line][y + 1] || !file[line + 1][y])
			return (false);
	}
	return (true);
}

static bool	init_map_size(t_parser *parser_ctx, char **file, int line)
{
	int	y;

	parser_ctx->map_size_x = 0;
	parser_ctx->map_size_y = 0;
	line--;
	while (file[++line])
	{
		parser_ctx->map_size_x++;
		y = -1;
		if (!file[line][0] || file[line][0] == '\n')
			return (free_ascii_map(parser_ctx));
		while (file[line][++y] && file[line][y] != '\n')
		{
			if (type_of_char(file[line][y]) >= 0
				&& is_valid_boundary(file, line, parser_ctx->map_size_x, y))
			{
				printf("%c", file[line][y]);
				if (y > parser_ctx->map_size_y)
					parser_ctx->map_size_y = y + 1;
			}
			else
			{
				return (free_ascii_map(parser_ctx));
			}
		}
		printf(" (%d)\n", parser_ctx->map_size_y);
	}
	return (true);
}

bool	free_failed_map_alloc(t_parser *parser_ctx, int x)
{
	parser_ctx->map_size_x = -1;
	parser_ctx->map_size_y = -1;
	parser_ctx->player_pos_x = -1;
	parser_ctx->player_pos_y = -1;
	parser_ctx->player_facing = -1;
	while (--x || x >= 0)
		free(parser_ctx->map[x]);
	return (true);
}

void	parse_ascii_map(t_parser *parser_ctx, char **file, int line)
{
	int	x;
	int	y;

	x = -1;
	init_map_size(parser_ctx, file, line);
	if (parser_ctx->map_size_x > 0 && parser_ctx->map_size_y > 0)
	{
		parser_ctx->map = ft_calloc(parser_ctx->map_size_x + 1, sizeof(void *));
		if (!parser_ctx->map)
			return ;
		line--;
		while (file[++line] && file[line][0] && file[line][0] != '\n')
		{
			parser_ctx->map[++x] = ft_calloc(parser_ctx->map_size_y + 1,
					sizeof(int));
			if (!parser_ctx->map[x] && free_failed_map_alloc(parser_ctx, x))
				return ;
			ft_memset(parser_ctx->map[x], 1, parser_ctx->map_size_x);
			y = -1;
			while (file[line][++y] && file[line][y] != '\n')
				if (!set_map_values(parser_ctx, file[line][y], x, y))
					return ;
		}
	}
}
