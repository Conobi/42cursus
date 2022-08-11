/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:13:21 by abastos           #+#    #+#             */
/*   Updated: 2022/08/11 17:29:30 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Print an error and exit if necessary
 *
 * @param c Minishell context struct
 * @param err Error struct
 */
void	create_error(t_ctx *c, t_error err)
{
	char	*message;

	if (err.type < FILE_ERR || err.type > WARNING)
	{
		create_error(c, (t_error){ERROR, SHELL_NAME,
			"Error code provided is not supported", NULL, 1, false});
		return ;
	}
	g_return = err.code;
	if (err.path)
		message = sf_add(ft_aconcat(8, RED_FG, err.cmd, ": ",
					err.path, ": ", err.message, "\n", RESET),
				&c->gbc, CMD_GB);
	else
		message = sf_add(ft_aconcat(6, RED_FG, err.cmd, ": ",
					err.message, "\n", RESET),
				&c->gbc, CMD_GB);
	if (write(2, message, ft_strlen(message)) == -1)
	{
		create_error(c, (t_error){WARNING, "write",
			strerror(errno), false, errno, false});
	}
	if (err.type == ERROR)
		exit_shell(c, err.code, true);
}

/**
 * @brief This function check files errors and print an error message
 *
 * @param c Minishell context struct
 * @param err Error struct must contains err.path and err.command
 * @return true if an error occurred
 * @return false if no error
 */
bool	file_errors(t_ctx *c, t_error err)
{
	struct stat	path_stat;
	int			staterr;

	staterr = stat(err.path, &path_stat);
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
	return (false);
}
