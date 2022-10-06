/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:22:03 by conobi            #+#    #+#             */
/*   Updated: 2022/10/06 21:34:57 by conobi           ###   ########lyon.fr   */
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
	printf("<%s> : %sCouleur invalide.%s\n", str, RED_TXT, RESET_TXT);
	return (free_split(str_split));
}

void	parse_color(t_parser *parser_ctx, char *str)
{
	char	*unspaced_str;
	char	**str_split;

	str_split = NULL;
	printf("<%s> : %sCouleur valide !%s\n", str, GRN_TXT, RESET_TXT);
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
				parser_ctx->f_color = rgba2hex(
						ft_atoi(str_split[0]), ft_atoi(str_split[1]),
						ft_atoi(str_split[2]), 255);
			else if (str[0] == 'C')
				parser_ctx->c_color = rgba2hex(
						ft_atoi(str_split[0]), ft_atoi(str_split[1]),
						ft_atoi(str_split[2]), 255);
		}
		free_split(str_split);
	}
}
