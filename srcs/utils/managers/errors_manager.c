/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:13:21 by abastos           #+#    #+#             */
/*   Updated: 2022/06/30 19:15:26 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Just a function to print the error message in stderr
 *
 * @param err Error message
 */
void	err_print(const char *err)
{
	write(2, err, ft_strlen(err));
}

/**
 * @brief Create an error and exit if necessary
 *
 * @param c Minishell context struct
 * @param err Error struct
 */
void	create_error(t_ctx *c, t_error err)
{
	char	*message;

	g_return = err.code;
	message = gb_add(ft_aconcat(8, RED_FG, err.cmd, ": ",
				err.path, ": ", err.message, "\n", RESET),
			&c->gbc, CMD_GB);
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
	int			staterr;

	staterr = stat(err.path, &path_stat);
	if (!err.is_file && !S_ISDIR(path_stat.st_mode))
	{
		create_error(c, (t_error){WARNING, err.cmd,
			strerror(ENOTDIR), err.path, 1, err.is_file});
		return (true);
	}
	if (err.is_file && S_ISDIR(path_stat.st_mode))
	{
		create_error(c, (t_error){WARNING, err.cmd,
			strerror(EISDIR), err.path, 126, err.is_file});
		return (true);
	}
	if (staterr)
	{
		create_error(c, (t_error){WARNING, err.cmd,
			strerror(errno), err.path, 127, err.is_file});
		return (true);
	}
	if (!(path_stat.st_mode & S_IRUSR))
	{
		create_error(c, (t_error){WARNING, err.cmd,
			strerror(EACCES), err.path, 126, err.is_file});
		return (true);
	}
	return (false);
}

/**
 * @brief This function takes as parameter the context and an struct
 * that contains error informations. If err.type is define,
 * the error display function corresponding to the given type is triggered
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
