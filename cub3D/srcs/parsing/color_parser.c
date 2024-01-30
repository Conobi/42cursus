/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:22:03 by conobi            #+#    #+#             */
/*   Updated: 2022/10/20 16:06:47 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*space_remover(char *str)
{
	char	*ret;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] == ' ')
			j++;
	ret = ft_calloc(ft_strlen(str) - j + 1, sizeof(char));
	if (!ret)
		return (NULL);
	i = -1;
	j = -1;
	while (str[++i])
		if (str[i] != ' ')
			ret[++j] = str[i];
	return (ret);
}

static bool	check_color_values(char **str_split)
{
	int	i;
	int	j;
	int	value;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (str_split[i] && str_split[i][++j])
			if (!ft_isdigit(str_split[i][j]))
				return (false);
		value = ft_atoi(str_split[i]);
		if (value < 0 || value > 255)
			return (false);
	}
	return (true);
}

bool	is_valid_color(char *str)
{
	char	*unspaced_str;
	char	**str_split;

	str_split = NULL;
	if (str[0] && str[1] && (str[0] == 'F' || str[0] == 'C') && str[1] == ' ')
	{
		unspaced_str = space_remover(str + 1);
		if (!unspaced_str)
			return (false);
		str_split = ft_split(unspaced_str, ',');
		if (!str_split)
		{
			free(unspaced_str);
			return (false);
		}
		free(unspaced_str);
		if (str_split[0] && str_split[1] && str_split[2]
			&& !str_split[3] && check_color_values(str_split))
		{
			free_split(str_split);
			return (true);
		}
	}
	return (free_split(str_split));
}

void	parse_color(t_ctx *c, char *str)
{
	char	*unspaced_str;
	char	**str_split;

	str_split = NULL;
	if (str[0] && str[1] && (str[0] == 'F' || str[0] == 'C') && str[1] == ' ')
	{
		unspaced_str = space_remover(str + 1);
		if (!unspaced_str)
			return ;
		str_split = ft_split(unspaced_str, ',');
		free(unspaced_str);
		if (str_split && check_color_values(str_split))
		{
			if (str[0] == 'F')
				c->f_color = (0 << 24 | ft_atoi(str_split[0]) << 16
						| ft_atoi(str_split[1]) << 8 | ft_atoi(str_split[2]));
			else if (str[0] == 'C')
				c->c_color = (0 << 24 | ft_atoi(str_split[0]) << 16
						| ft_atoi(str_split[1]) << 8 | ft_atoi(str_split[2]));
		}
		free_split(str_split);
	}
}
