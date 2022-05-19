/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:13:21 by abastos           #+#    #+#             */
/*   Updated: 2022/05/19 18:22:17 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	err_print(char *err)
{
	write(2, err, ft_strlen(err));
}

/**
 * @brief This function prints the error message corresponding
 * to the given error
 *
 * @param c Minishell context struct
 * @param err Error struct must contains err.path and err.command
 * @return true if an error occurred
 * @return false if no error
 */
static bool	file_errors(t_ctx *c, t_error err)
{
	struct stat	path_stat;

	if (stat(err.path, &path_stat))
	{
		err_print(gb_add(ft_aconcat(6, err.cmd, ": ", err.path,
					": ", strerror(errno), "\n"), &c->gbc, CMD_GB));
		return (true);
	}
	if (!(path_stat.st_mode & S_IRUSR))
	{
		err_print(gb_add(ft_aconcat(6, err.cmd, ": ", err.path,
					": ", strerror(EACCES), "\n"), &c->gbc, CMD_GB));
		return (true);
	}
	if (!err.is_file && !S_ISDIR(path_stat.st_mode))
	{
		err_print(gb_add(ft_aconcat(6, err.cmd, ": ", err.path,
					": ", strerror(ENOTDIR), "\n"), &c->gbc, CMD_GB));
		return (true);
	}
	if (err.is_file && S_ISDIR(path_stat.st_mode))
	{
		err_print(gb_add(ft_aconcat(6, err.cmd, ": ", err.path,
					": ", strerror(EISDIR), "\n"), &c->gbc, CMD_GB));
		return (true);
	}
	return (false);
}

/**
 * @brief This function takes as parameter the context and an struct that contains
 * error informations. If err.type is define, the error display function
 * corresponding to the given type is triggered
 *
 * @param c Minishell context struct
 * @param err Error struct
 * @return true if an error occurred
 * @return false if no error
 */
bool	error_handler(t_ctx *c, t_error err)
{
	if (!err.type)
	{
		// todo: Display error
		return (true);
	}
	if (err.type == FILE_ERR)
		return (file_errors(c, err));
	return (false);
}
