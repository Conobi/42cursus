/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:34:52 by abastos           #+#    #+#             */
/*   Updated: 2022/05/18 18:25:12 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function is used to get the current path
 *
 * @param c Minishell context struct
 * @return char* Path of current location (in garbage collector)
 */
char	*get_path(t_ctx *c)
{
	return (gb_add(getcwd(NULL, 256), &c->gbc, CMD_GB));
}

static size_t	get_len(const char *home_path, const char *pwd)
{
	if (ft_strlen(home_path) > ft_strlen(pwd))
		return (ft_strlen(home_path));
	else
		return (ft_strlen(pwd));
}

/**
 * @brief This function is used to format the current path location
 * (ex: /User/<user>/Documents -> ~/Documents)
 *
 * @param c Minishell context struct
 * @return char* Path of current location formated (in garbage collector)
 */
char	*format_path(t_ctx *c)
{
	char	*pwd;
	char	*new_path;
	char	*home_path;

	pwd = get_path(c);
	home_path = getenv("HOME");
	if (ft_strncmp(home_path, pwd, get_len(home_path, pwd)) == 0)
	{
		gb_calloc(2, sizeof(char), CMD_GB, &c->gbc);
		new_path = "~/";
	}
	else if (ft_strnstr(pwd, home_path, ft_strlen(pwd)))
	{
		new_path = pwd + (ft_strlen(home_path) - 1);
		new_path[0] = '~';
		new_path[1] = '/';
	}
	else
		new_path = pwd;
	return (new_path);
}
