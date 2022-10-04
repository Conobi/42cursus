/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:56:56 by conobi            #+#    #+#             */
/*   Updated: 2022/10/04 23:35:25 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	free_ascii_map(t_parser *parser_ctx)
{
	int	i;

	i = -1;
	parser_ctx->map_size_x = -1;
	parser_ctx->map_size_y = -1;
	parser_ctx->player_pos_x = -1;
	parser_ctx->player_pos_y = -1;
	parser_ctx->player_facing = -1;
	if (parser_ctx->map_size_x > 0 || parser_ctx->map_size_y > 0)
	{
		while (parser_ctx->map[++i])
			free(parser_ctx->map[i]);
		free(parser_ctx->map);
	}
	return (false);
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

	// Tests anti crashs
	len_plus = -1;
	if (file[line + 1] != NULL)
		len_plus = ft_strlen(file[line + 1]);
	len_minus = -1;
	if (line > 0 && file[line - 1] != NULL)
		len_minus = ft_strlen(file[line - 1]);
	// Tous les cas où on est sur une bordure
	if (y == 0 || x == 0 || file[line + 1] == NULL || !file[line][y + 1])
	{
		// Cas de la première ligne
		if (x == 0 && !(file[line][y] == ' ' || file[line][y] == '1')
			&& file[line + 1] != NULL && y + 1 <= len_plus
			&& !(file[line + 1][y] == ' ' || file[line + 1][y] == '1'))
			return (false);
		// Cas de la dernière ligne
		if ((file[line + 1] == NULL || !file[line + 1][0])
			&& (!(file[line][y] == ' ' || file[line][y] == '1')
			|| (y + 1 <= len_minus
				&& !(file[line - 1][y] == ' ' || file[line - 1][y] == '1'))))
			return (false);
		// Cas du premier caractère
		if (y == 0 && !(file[line][y] == ' ' || file[line][y] == '1'))
			return (false);
		// Cas du dernier caractère
		if (!file[line][y + 1]
			&& !(file[line][y] == ' ' || file[line][y] == '1'))
			return (false);
		// TODO: checker qu'un SPACE ne puisse pas toucher un caractère qui ne soit pas un 1 || SPACE
	}
	return (true);
}

void	init_map_size(t_parser *parser_ctx, char **file, int line)
{
	int	y;

	parser_ctx->map_size_x = -1;
	parser_ctx->map_size_y = -1;
	line--;
	while (file[++line])
	{
		parser_ctx->map_size_x++;
		y = -1;
		while (file[line][y])
		{
			if ((file[line][y] == '0' || file[line][y] == ' '
				|| file[line][y] == '1' || file[line][y] == 'N'
				|| file[line][y] == 'S' || file[line][y] == 'W'
				|| file[line][y] == 'E')
				&& is_valid_boundary(file, line, parser_ctx->map_size_x, y))
			{
				if (y > parser_ctx->map_size_y)
					parser_ctx->map_size_y = y;
			}
			else
			{
				free_ascii_map(parser_ctx);
				return ;
			}
		}
	}
}

void	parse_ascii_map(t_parser *parser_ctx, char **file, int line)
{
	int	x;
	int	y;

	x = -1;
	init_map_size(parser_ctx, file, line);
	line--;
	if (parser_ctx->map_size_x > 0 && parser_ctx->map_size_y > 0)
	{
		parser_ctx->map = ft_calloc(parser_ctx->map_size_y + 1, sizeof(void *));
		if (!parser_ctx->map)
			return ;
		while (file[++line])
		{
			parser_ctx->map[++x] = ft_calloc(parser_ctx->map_size_x + 1,
					sizeof(int));
			// TODO : free_failed_map_alloc
			ft_memset(parser_ctx->map[x], 1, parser_ctx->map_size_x);
			y = -1;
			while (file[line][++y])
				if (!set_map_values(parser_ctx, file[line][x], x, y))
					return ;
		}
	}
}
