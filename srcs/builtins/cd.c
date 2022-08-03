/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:05:18 by abastos           #+#    #+#             */
/*   Updated: 2022/08/03 21:07:35 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * todo: fix bug when cd / and cd -
 * Mem error l:56 new_path not defined
 * (final path not change)
 * check with symlink
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

	if (c->ncmds > 1)
		return (0);
	if (!path || ft_strlen(path) == 0) // todo: check if err after parsing
		new_path = get_env_by_key(c->env, "HOME")->value;
	// todo: make a function to change value of env list values
	else if (ft_eq(path, "-", 0))
	{
		pwd_env = get_env_by_key(c->env, "OLDPWD");
		if (!pwd_env)
		{
			create_error(c, (t_error){WARNING, "cd",
				"OLDPWD not set", NULL, 1, false});
			return (1);
		}
		printf("%s\n", pwd_env->value);
		new_path = pwd_env->value;
		pwd_env->value = get_path(c);
	}
	else
		new_path = path;
	if (file_errors(c, (t_error){FILE_ERR, "cd", NULL, new_path, 1, false}))
		return (1);
	if (chdir(new_path) == -1)
		create_error(c, (t_error){WARNING, "cd",
			strerror(errno), new_path, errno, false});
	return (0);
}
