/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:05:18 by abastos           #+#    #+#             */
/*   Updated: 2022/08/23 14:28:24 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	no_path_manager(t_ctx *c, char **new_path)
{
	t_env	*home_env;

	home_env = get_env_by_key(c->env, "HOME");
	if (!home_env || !home_env->value)
	{
		create_error(c, (t_error){WARNING, "cd",
			"HOME not set", NULL, 1, false});
		return (false);
	}
	*new_path = home_env->value;
	return (true);
}

static bool	minus_manager(t_ctx *c, char **new_path)
{
	t_env	*pwd_env;

	pwd_env = get_env_by_key(c->env, "OLDPWD");
	if (!pwd_env || !pwd_env->value)
	{
		create_error(c, (t_error){WARNING, SHELL_NAME,
			"OLDPWD not set", "cd", 1, false});
		return (false);
	}
	printf("%s\n", pwd_env->value);
	*new_path = pwd_env->value;
	return (true);
}

static void	path_changer(t_ctx *c, char *new_path)
{
	set_list_entry(c, "OLDPWD",
		sf_add(getcwd(NULL, 256), &c->gbc, CMD_GB), false);
	if (chdir(new_path) == -1)
		create_error(c, (t_error){WARNING, "cd",
			strerror(errno), new_path, errno, false});
	set_list_entry(c, "PWD",
		sf_add(getcwd(NULL, 256), &c->gbc, CMD_GB), false);
}

/**
 * @brief This function is a clone of cd command for builtins
 *
 * @param c Minishell context struct
 * @param path Destination
 */
int	b_cd(t_ctx *c, char *path)
{
	char	*new_path;

	new_path = NULL;
	if (c->ncmds > 1)
		return (0);
	if (!path)
	{
		if (!no_path_manager(c, &new_path))
			return (1);
	}
	else if (ft_strlen(path) == 0)
		new_path = get_path(c);
	else if (path && ft_eq(path, "-", 0))
	{
		if (!minus_manager(c, &new_path))
			return (1);
	}
	else
		new_path = path;
	if (file_errors(c, (t_error){FILE_ERR, "cd", NULL, new_path, 1, false}))
		return (1);
	path_changer(c, new_path);
	return (0);
}
