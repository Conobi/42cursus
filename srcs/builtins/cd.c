/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:05:18 by abastos           #+#    #+#             */
/*   Updated: 2022/06/15 17:24:38 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * todo: fix bug when cd / and cd -
 * Mem error l:56 new_path not defined
 * (final path not change)
*/

/**
 * @brief This function is a clone of cd command for builtins
 *
 * @param c Minishell context struct
 * @param path Destination
 */
void	b_cd(t_ctx *c, char *path)
{
	t_error	err;
	char	*new_path;

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
	else if (ft_strncmp(path, "-", ft_strlen(path)) == 0)
	{
		new_path = c->last_path;
		printf("%s\n", new_path);
	}
	else
		new_path = path;
	err.path = new_path;
	err.cmd = "cd";
	err.type = FILE_ERR;
	err.is_file = false;
	if (error_handler(c, err))
	{
		g_return = 256;
		gen_prompt(c, format_path(c), get_branch(c));
		return ;
	}
	c->last_path = get_path(c);
	chdir(new_path);
	g_return = 0;
	gen_prompt(c, format_path(c), get_branch(c));
}
