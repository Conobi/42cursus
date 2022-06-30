/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:05:18 by abastos           #+#    #+#             */
/*   Updated: 2022/06/30 19:56:41 by abastos          ###   ########lyon.fr   */
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

	if (c->ncmds > 1)
		return (0);
	if (!path || ft_strlen(path) == 0) // todo: check if err after parsing
		new_path = getenv("HOME");
	else if (path[0] == '~')
	{
		if (path[1] == '/')
			new_path = gb_add(ft_aconcat(2, getenv("HOME"), path + 1),
					&c->gbc, CMD_GB);
		else
			new_path = getenv("HOME");
	}
	// todo: make a function to change value of env list values
	// else if (ft_strncmp(path, "-", ft_strlen(path)) == 0)
	// {
	// 	lenv = get_env_list_by_key(c->env, "OLDPDW");
	// 	printf("%s\n", (t_env *)(lenv->content)->value);
	// 	// printf("%s\n", new_path);
	// }
	else
		new_path = path;
	if (error_handler(c, (t_error){FILE_ERR, "cd", NULL, new_path, 1, false}))
	{
		if (c->better_prompt)
			gen_prompt(c, format_path(c), get_branch(c));
		return (1);
	}
	chdir(new_path);
	if (c->better_prompt)
		gen_prompt(c, format_path(c), get_branch(c));
	return (0);
}
