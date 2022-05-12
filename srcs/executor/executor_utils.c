/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:55:49 by abastos           #+#    #+#             */
/*   Updated: 2022/05/12 01:04:03 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function is used to find an executable in PATH env variable
 * for the given exec_name
 *
 * @param c Context struct
 * @param exec_name executable name to search
 * @return char* Returns the executable path
 */
static char	*find_exec(t_ctx *c, const char *exec_name)
{
	char	**path;
	char	*pre_exec;
	char	*exec_path;
	int		i;

	path = gb_add(ft_split(getenv("PATH"), ':'), &c->gbc, CMD_GB);
	i = 0;
	while (path[i])
	{
		pre_exec = gb_add(ft_strjoin("/", exec_name), &c->gbc, CMD_GB);
		exec_path = gb_add(ft_strjoin(path[i], pre_exec), &c->gbc, CMD_GB);
		if (access(exec_path, X_OK) == 0)
			return (exec_path);
		i++;
	}
	return (NULL);
}

/**
 * @brief This function is used to close all pipes after execution
 *
 * @param table Commands table struct
 * @param pipes	Number of pipes to close
 */
void	close_pipes(t_table *table, int pipes)
{
	int	i;

	i = 0;
	while (i < pipes)
		close(table->pipe_fd[i++]);
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
 * @brief This function set the exec path in all commands
 *
 * @param c Context struct
 * @param table Commands table struct
 */
void	set_exec_path(t_ctx *c, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->commands_num)
	{
		table->command_table[i].exec_path = find_exec(
				c,
				table->command_table[i].args[0]);
		if (!table->command_table[i].exec_path)
		{
			printf("%s: %s\n", table->command_table[i].args[0],
				"command not found");
			return ;
		}
		i++;
	}
}
