/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:56:56 by conobi            #+#    #+#             */
/*   Updated: 2022/10/12 15:39:56 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	set_map_values(t_ctx *c, const char ch, int y, int x)
{
	if (ch == '0')
		c->map[y][x] = 0;
	else if (ch == ' ' || ch == '1')
		c->map[y][x] = 1;
	else if ((ch == 'N' || ch == 'S' || ch == 'W' || ch == 'E')
		&& c->player.x == -1
		&& c->player.y == -1)
	{
		c->map[y][x] = 0;
		c->player.x = x * c->cell_size + c->cell_size / 2;
		c->player.y = y * c->cell_size + c->cell_size / 2;
	}
	else
		return (free_ascii_map(c));
	if (ch == 'N')
		c->player.angle = NORTH;
	else if (ch == 'S')
		c->player.angle = SOUTH;
	else if (ch == 'W')
		c->player.angle = WEST;
	else if (ch == 'E')
		c->player.angle = EAST;
	return (true);
}

static bool	is_valid_boundary(char **file, int line, int x, int y)
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

static bool	init_map_size(t_ctx *c, char **file, int line)
{
	int	x;

	c->map_size_x = 0;
	c->map_size_y = 0;
	line--;
	while (file[++line])
	{
		c->map_size_y++;
		if (!file[line][0] || file[line][0] == '\n')
			return (free_ascii_map(c));
		x = -1;
		while (file[line][++x] && file[line][x] != '\n')
		{
			if (type_of_char(file[line][x]) >= 0
				&& is_valid_boundary(file, line, c->map_size_x, x))
			{
				if (x >= c->map_size_x)
					c->map_size_x = x;
			}
			else
				return (free_ascii_map(c));
		}
	}
	c->map_size_x++;
	printf("SX: %d SY: %d\n", c->map_size_x, c->map_size_y);
	return (true);
}

static bool	free_failed_map_alloc(t_ctx *c, int x)
{
	c->map_size_x = -1;
	c->map_size_y = -1;
	c->player.x = -1;
	c->player.y = -1;
	while (--x || x >= 0)
		free(c->map[x]);
	return (true);
}

void	parse_ascii_map(t_ctx *c, char **file, int line)
{
	int	x;
	int	y;

	y = -1;
	init_map_size(c, file, line);
	if (c->map_size_x > 0 && c->map_size_y > 0)
	{
		c->map = ft_calloc(c->map_size_y + 1, sizeof(void *));
		if (!c->map)
			return ;
		line--;
		while (file[++line] && file[line][0] && file[line][0] != '\n')
		{
			c->map[++y] = ft_calloc(c->map_size_x + 1,
					sizeof(int));
			if (!c->map[y] && free_failed_map_alloc(c, y))
				return ;
			init_line(c, c->map[y]);
			x = -1;
			while (file[line][++x] && file[line][x] != '\n')
				if (!set_map_values(c, file[line][x], y, x))
					return ;
		}
	}
}
