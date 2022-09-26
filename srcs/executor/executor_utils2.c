/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 14:20:15 by abastos           #+#    #+#             */
/*   Updated: 2022/09/25 18:14:11 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function is used to find command bin file in PATH env variable
 *
 * @param c Minishell context struct
 * @param exec_name Executable name to search
 * @return char* Return the executable path
 */
static char	*find_by_path_env(t_ctx *c, const char *exec_name)
{
	t_env	*env_path;
	char	**path;
	char	*exec_path;
	int		i;

	env_path = get_env_by_key(c->env, "PATH");
	if (!env_path || !ft_strlen(env_path->value) || !env_path->value)
	{
		create_error(c, (t_error){WARNING, SHELL_NAME,
			"No such file or directory", (char *)exec_name, 127, true});
		return (NULL);
	}
	path = gb_split(env_path->value, ':', &c->gbc, CMD_GB);
	if (!path)
		enomem_error(&c->gbc);
	i = -1;
	while (path[++i])
	{
		exec_path = sf_add(
				ft_aconcat(3, path[i], "/", exec_name),
				&c->gbc, CMD_GB);
		if (access(exec_path, X_OK) == 0)
			return (exec_path);
	}
	return (NULL);
}

/**
 * @brief This function is used to find an executable in PATH env variable
 * or given path for the given exec_name
 *
 * @param c Minishell context struct
 * @param exec_name Executable name to search
 * @return char* Return the executable path
 */
char	*find_exec(t_ctx *c, const char *exec_name)
{
	char	*path;
	t_env	*path_env;

	if (ft_strchr(exec_name, '/')
		|| ft_eq(exec_name, ".", 0) || ft_eq(exec_name, "..", 0))
	{
		if (file_errors(c, (t_error){FILE_ERR, SHELL_NAME, NULL,
				(char *)exec_name, 1, true}))
			return (NULL);
		return ((char *)exec_name);
	}
	path = find_by_path_env(c, exec_name);
	if (path)
		return (path);
	path_env = get_env_by_key(c->env, "PATH");
	if (path_env && path_env->value && ft_strlen(path_env->value))
		create_error(c, (t_error){WARNING, SHELL_NAME,
			"command not found", (char *)exec_name, 127, true});
	return (NULL);
}

/**
 * @brief This function is used to close command fds (in, out and heredocs)
 *
 * @param c Minishell context struct
 * @param curr Index of current command
 * @param in Pointer to infile fd to close
 * @param out Pointer to output fd to close
 */
void	close_fds(t_ctx *c, int curr)
{
	fdgb_close(&c->fdgbc, CMD_GB);
	if (c->cmds[curr].heredoc > 0)
		close(c->cmds[curr].heredoc);
}

/**
 * @brief This function is used to determine and set
 * input and output redirection for a command
 *
 * @param c Minishell context struct
 * @param curr Index of current command
 * @param in Pointer to infile fd to modify for input
 * @param out Pointer to output fd to modify for output
 * @return Return true if no file errors, false if given file is errored
 */
bool	io_handler(t_ctx *c, int curr, int *in, int *out)
{
	if (!infile_handler(c, curr))
		return (false);
	if (!outfile_handler(c, curr))
		return (false);
	in_selector(c, curr, in);
	out_selector(c, curr, out);
	return (true);
}
