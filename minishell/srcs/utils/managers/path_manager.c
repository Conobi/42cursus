/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:34:52 by abastos           #+#    #+#             */
/*   Updated: 2022/08/11 19:19:02 by conobi           ###   ########lyon.fr   */
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
	return (sf_add(getcwd(NULL, 256), &c->gbc, CMD_GB));
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
	t_env	*home_env;
	int		home_path_len;

	pwd = get_path(c);
	home_env = get_env_by_key(c->env, "HOME");
	if (!home_env || !home_env->value)
		return (pwd);
	home_path = home_env->value;
	home_path_len = ft_strlen(home_path);
	if (home_path_len > 1 && home_path[ft_strlen(home_path) - 1] == '/')
		home_path_len -= 1;
	else if (home_path[ft_strlen(home_path) - 1] == '/')
		home_path_len = 0;
	if ((int)ft_strlen(pwd) == home_path_len)
		return ("~/");
	if (ft_eq(pwd, home_path, 1))
		return (
			sf_add(
				ft_aconcat(2, "~/", pwd + home_path_len + 1)
				, &c->gbc, CMD_GB)
		);
	return (pwd);
}
