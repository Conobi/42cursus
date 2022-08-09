/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:05:18 by abastos           #+#    #+#             */
/*   Updated: 2022/08/09 13:36:19 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * todo: check with symlink
*/

/**
 * @brief This function is a clone of cd command for builtins
 *
 * @param c Minishell context struct
 * @param path Destination
 */
int	b_cd(t_ctx *c, char *path)
{
	char	*new_path;
	t_env	*pwd_env;
	t_env	*home_env;

	if (c->ncmds > 1)
		return (0);
	pwd_env = get_env_by_key(c->env, "OLDPWD");
	if (!path)
	{
		home_env = get_env_by_key(c->env, "HOME");
		if (!home_env)
		{
			create_error(c, (t_error){WARNING, "cd",
				"HOME not set", NULL, 1, false});
			return (1);
		}
		new_path = home_env->value;
	}
	else if (ft_strlen(path) == 0)
		new_path = get_path(c);
	else if (ft_eq(path, "-", 0))
	{
		if (!pwd_env)
		{
			create_error(c, (t_error){WARNING, "cd",
				"OLDPWD not set", NULL, 1, false});
			return (1);
		}
		printf("%s\n", pwd_env->value);
		new_path = pwd_env->value;
	}
	else
		new_path = path;
	if (file_errors(c, (t_error){FILE_ERR, "cd", NULL, new_path, 1, false}))
		return (1);
	if (!pwd_env)
		ft_lstadd_front(&c->env, create_env_entry(c,
				gb_add(
					ft_aconcat(2, "OLDPWD=",
						getcwd(NULL, 256)), &c->gbc, CMD_GB)));
	else
		pwd_env->value = gb_add(getcwd(NULL, 256), &c->gbc, CMD_GB);
	if (chdir(new_path) == -1)
		create_error(c, (t_error){WARNING, "cd",
			strerror(errno), new_path, errno, false});
	return (0);
}
