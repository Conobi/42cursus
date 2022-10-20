/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:35:07 by conobi            #+#    #+#             */
/*   Updated: 2022/10/20 16:07:12 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	free_ascii_map(t_ctx *c, bool is_err)
{
	int	i;

	i = -1;
	c->map_size_x = -1;
	c->map_size_y = -1;
	c->player.x = -1;
	c->player.y = -1;
	if (c->map_size_x > 0 || c->map_size_y > 0)
	{
		while (c->map[++i])
			free(c->map[i]);
		free(c->map);
	}
	if (is_err)
		print_err(NULL,
			"The ASCII map contains an incorrect line or character", 22);
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

void	init_line(t_ctx *c, int *line)
{
	int	i;

	i = -1;
	while (++i < c->map_size_x)
		line[i] = 1;
}
