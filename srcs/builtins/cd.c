/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:05:18 by abastos           #+#    #+#             */
/*   Updated: 2022/05/18 19:18:01 by abastos          ###   ########lyon.fr   */
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

	path += 3;
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
	if (!error_handler(c, err))
	{
		c->last_path = get_path(c);
		chdir(new_path);
		free(c->prompt);
	}
}
