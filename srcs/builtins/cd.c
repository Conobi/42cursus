/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:05:18 by abastos           #+#    #+#             */
/*   Updated: 2022/05/14 16:25:28 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function is a clone of cd command for builtins
 *
 * @param c Context struct
 * @param path Destination
 */
void	b_cd(t_ctx *c, char *path)
{
	t_error	err;
	char	*new_path;

	path += 3;
	if (path[0] == '~')
	{
		if (path[1] == '/')
			new_path = gb_add(ft_aconcat(2, getenv("HOME"), path + 1),
					&c->gbc, CMD_GB);
		else
			new_path = getenv("HOME");
	}
	else if (ft_strncmp(path, "-", ft_strlen(path)) == 0)
	{
		printf("last path before -> %s\n", c->last_path);
		new_path = c->last_path;
		printf("new path -> %s\n", new_path);
	}
	else if (ft_strlen(path) == 0)
		new_path = getenv("HOME");
	else
		new_path = path;
	printf("new path end -> %s\n", new_path);
	err.path = new_path;
	err.cmd = "cd";
	err.type = FILE_ERR;
	// if (!error_handler(c, err))
	// {
	// 	free(c->last_path);
	// 	c->last_path = getcwd(NULL, sizeof(char) * 128);
	// 	printf("last path after -> %s\n", c->last_path);
	// 	printf("new path after -> %s\n", new_path);
	// 	chdir(new_path);
	// 	free(c->prompt);
	// 	gen_prompt(c, get_path(c));
	// }
}
