/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:34:52 by abastos           #+#    #+#             */
/*   Updated: 2022/07/01 19:11:55 by conobi           ###   ########lyon.fr   */
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
	char	*home_path;
	int		home_path_len;

	pwd = get_path(c);
	if (!get_env_by_key(c->env, "HOME")
		|| !*get_env_by_key(c->env, "HOME")->value)
		return (pwd);
	home_path = get_env_by_key(c->env, "HOME")->value;
	home_path_len = ft_strlen(home_path);
	if (
		home_path_len > 1
		&& home_path[ft_strlen(home_path) - 1] == '/'
	)
		home_path_len -= 1;
	else if (home_path[ft_strlen(home_path) - 1] == '/')
		home_path_len = 0;
	if (ft_eq(pwd, home_path, 1))
		return (
			gb_add(
				ft_aconcat(2, "~/", pwd + home_path_len + 1)
				, &c->gbc, CMD_GB)
		);
	return (pwd);
}
