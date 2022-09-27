/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:55:49 by abastos           #+#    #+#             */
/*   Updated: 2022/09/27 12:30:46 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (WTERMSIG(status) == 3)
			if (write(1, "Quit: 3\n", 9) == -1)
				return ;
		if (WTERMSIG(status) == 2)
			if (write(1, "\n", 1) == -1)
				return ;
		g_return = WTERMSIG(status);
		if (g_return != 131)
			g_return += 128;
	}
}
