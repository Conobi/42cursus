/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:34:52 by abastos           #+#    #+#             */
/*   Updated: 2022/05/12 01:04:51 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_len(const char *home_path, const char *pwd)
{
	if (ft_strlen(home_path) > ft_strlen(pwd))
		return(ft_strlen(home_path));
	else
		return(ft_strlen(pwd));
}

/**
 * @brief This function is used to get the current path location
 *
 * @param c Context struct
 * @return char* Path of current location
 */
char	*get_path(t_ctx *c)
{
	char	*pwd;
	char	*new_path;
	char	*home_path;

	pwd = NULL;
	pwd = gb_add(getcwd(pwd, sizeof(pwd)), &c->gbc, CMD_GB);
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
