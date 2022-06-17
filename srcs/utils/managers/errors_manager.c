/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:13:21 by abastos           #+#    #+#             */
/*   Updated: 2022/06/16 19:31:06 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_print(const char *err)
{
	write(2, err, ft_strlen(err));
}

void	create_error(t_ctx *c, t_error err)
{
	char	*message;

	message = ft_aconcat(6, err.cmd, ": ", err.message, ": ",
			gb_add(ft_itoa(err.code), &c->gbc, PERM_GB), "\n");
	write(2, message, ft_strlen(message));
	if (err.type == FATAL)
		exit_shell(c, err.code);
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
