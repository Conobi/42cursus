/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:56:06 by abastos           #+#    #+#             */
/*   Updated: 2022/09/21 19:54:58 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_fork(t_ctx *c, int curr, int *in, int *out)
{
	if (set_exec_path(c, &c->cmds[curr]))
	{
		close_fds(c, curr, in, out);
		close_pipes(c, c->ncmds * 2);
		exit(g_return);
	}
	if (*in == -1 || *out == -1)
	{
		close_fds(c, curr, in, out);
		close_pipes(c, c->ncmds * 2);
		exit(1);
	}
	switch_pipes(*in, *out);
	close_pipes(c, 2 * c->ncmds);
	exit(execve(c->cmds[curr].exec_path,
			c->cmds[curr].argv, convert_env(c)));
}

/**
 * @brief This function executes the child process
 *
 * @param cmd Current fork
 * @param curr Index of current command to execute
 */
static void	exec_child(t_ctx *c, int curr)
{
	int		in;
	int		out;

	signal(SIGINT, fork_sig_handler);
	signal(SIGQUIT, fork_sig_handler);
	termios_set(c, 1);
	if (!io_handler(c, curr, &in, &out))
	{
		close_fds(c, curr, &in, &out);
		return ;
	}
	if (c->cmds[curr].argc >= 1)
	{
		if (c->cmds[curr].is_builtins)
		{
			dup2(out, STDOUT_FILENO);
			g_return = exec_builtin(c, c->cmds[curr]);
			dup2(STDIN_FILENO, STDOUT_FILENO);
		}
		else
		{
			c->exec->process[c->exec->curr_process] = fork();
			if (c->exec->process[c->exec->curr_process] < 0)
				return (perror("fork"));
			if (c->exec->process[c->exec->curr_process] == 0)
				exec_fork(c, curr, &in, &out);
			c->exec->curr_process += 1;
		}
	}
	close_fds(c, curr, &in, &out);
}

/**
 * @brief This function is used to create a pipe array with pipe()
 * in table->pipe_fd
 * @param c Minishell context struct
 */
static void	pipe_fd(t_ctx *c)
{
	int	i;

	c->exec->pipe_fd = sf_calloc(c->ncmds * 2, sizeof(int), CMD_GB, &c->gbc);
	i = 0;
	while (i < c->ncmds)
	{
		if (pipe(c->exec->pipe_fd + 2 * i) < 0)
		{
			perror("pipe");
			close_pipes(c, c->ncmds * 2);
			exit_shell(c, 1, false);
		}
		i++;
	}
}

static void	wait_forks(t_ctx *c)
{
	int	i;
	int	status;

	i = 0;
	while (i < c->ncmds)
	{
		if (i < c->exec->nprocess)
		{
			waitpid(c->exec->process[i], &status, 0);
			child_status(status);
		}
		i++;
	}
}

/**
 * @brief This function is the main function of execution
 *
 * @param c Minishell context struct
 */
void	exec(t_ctx *c)
{
	int		i;

	c->exec = sf_calloc(1, sizeof(t_exec), CMD_GB, &c->gbc);
	c->exec->nprocess = c->ncmds;
	i = 0;
	while (i < c->ncmds)
	{
		if (c->cmds[i].argc > 0 && is_builtin(c->cmds[i]))
		{
			c->cmds[i].is_builtins = true;
			c->exec->nprocess -= 1;
		}
		i++;
	}
	c->exec->curr_process = 0;
	c->exec->process = sf_calloc(c->exec->nprocess,
			sizeof(pid_t), CMD_GB, &c->gbc);
	if (!open_heredocs(c))
		return ;
	pipe_fd(c);
	i = 0;
	while (i < c->ncmds)
		exec_child(c, i++);
	close_pipes(c, 2 * c->ncmds);
	wait_forks(c);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}
