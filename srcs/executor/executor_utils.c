/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:55:49 by abastos           #+#    #+#             */
/*   Updated: 2022/08/03 22:41:26 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function is used to find an executable in PATH env variable
 * for the given exec_name
 *
 * @param c Minishell context struct
 * @param exec_name executable name to search
 * @return char* Returns the executable path
 */
char	*find_exec(t_ctx *c, const char *exec_name)
{
	t_env	*env_path;
	char	**path;
	char	*exec_path;
	int		i;

	if (ft_strchr(exec_name, '/'))
	{
		if (file_errors(c, (t_error){FILE_ERR, SHELL_NAME, NULL,
				(char *)exec_name, 1, true}))
			return (NULL);
		return ((char *)exec_name);
	}
	env_path = get_env_by_key(c->env, "PATH");
	if (!env_path)
	{
		create_error(c, (t_error){WARNING, SHELL_NAME,
			"No such file or directory", (char *)exec_name, 127, true});
		return (NULL);
	}
	path = gb_split(env_path->value, ':', &c->gbc, CMD_GB);
	i = 0;
	while (path[i])
	{
		exec_path = gb_add(
				ft_aconcat(3, path[i], "/", exec_name),
				&c->gbc, CMD_GB);
		if (access(exec_path, X_OK) == 0)
			return (exec_path);
		i++;
	}
	create_error(c, (t_error){WARNING, SHELL_NAME,
		"No such file or directory", (char *)exec_name, 127, true});
	return (NULL);
}

/**
 * @brief This function is used to close all pipes after execution
 *
 * @param table Commands table struct
 * @param pipes	Number of pipes to close
 */
void	close_pipes(t_ctx *c, int pipes)
{
	int	i;

	i = 0;
	while (i < pipes)
		close(c->exec->pipe_fd[i++]);
}

/**
 * @brief This function is used to switch in to stdin and out to stdout
 *
 * @param in in fd to switch
 * @param out out fd to switch
 */
void	switch_pipes(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
}

/**
 * @brief This function set the exec path in current command
 *
 * @param c Minishell context struct
 * @param cmd Current command to set exec path
 * @return 1 if an executable was not found, 0 if it was found
 */
int	set_exec_path(t_ctx *c, t_ncommand *cmd)
{
	cmd->exec_path = find_exec(c, cmd->argv[0]);
	if (!cmd->exec_path && !is_builtin(*cmd))
		return (1);
	return (0);
}

void	child_status(int status)
{
	if (WIFEXITED(status))
		g_return = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		g_return = WTERMSIG(status);
		if (g_return != 131)
			g_return += 128;
	}
	if (EDEBUG)
		printf("status = %d\n", g_return);
}
