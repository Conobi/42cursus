/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:56:06 by abastos           #+#    #+#             */
/*   Updated: 2022/07/02 14:07:11 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_fork(t_ctx *c, int curr, int *in, int *out)
{
	if (set_exec_path(c, &c->cmds[curr]))
		exit(g_return);
	io_handler(c, curr, in, out);
	if (*in == -1 || *out == -1)
		exit(1);
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
	termios_set(c, 1);
	if (is_builtin(c->cmds[curr]))
	{
		io_handler(c, curr, &in, &out);
		switch_pipes(in, out);
		g_return = exec_builtin(c, c->cmds[curr]);
		dup2(STDIN_FILENO, STDOUT_FILENO);
		return ;
	}
	c->exec->process[curr] = fork();
	if (c->exec->process[curr] < 0)
		return (perror("fork"));
	if (c->exec->process[curr] == 0)
		exec_fork(c, curr, &in, &out);
}

/**
 * @brief This function is used to create a pipe array with pipe()
 * in table->pipe_fd
 * @param c Minishell context struct
 */
static void	pipe_fd(t_ctx *c)
{
	int	i;

	c->exec->pipe_fd = gb_calloc(c->ncmds * 2, sizeof(int), CMD_GB, &c->gbc);
	i = 0;
	while (i < c->ncmds)
	{
		if (pipe(c->exec->pipe_fd + 2 * i) < 0)
		{
			perror("pipe");
			free(c->exec->pipe_fd);
			return ;
		}
		i++;
	}
}

static void	wait_forks(t_ctx *c)
{
	int	i;
	int	status;

	i = -1;
	while (++i < c->ncmds)
	{
		if (!is_builtin(c->cmds[i]))
		{
			waitpid(c->exec->process[i], &status, 0);
			child_status(status);
		}
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

	c->exec = gb_calloc(1, sizeof(t_exec), CMD_GB, &c->gbc);
	c->exec->process = gb_calloc(c->ncmds, sizeof(pid_t), CMD_GB, &c->gbc);
	pipe_fd(c);
	open_heredocs(c);
	i = 0;
	while (i < c->ncmds)
	{
		if (c->cmds[i].argc < 1)
			return ;
		exec_child(c, i++);
	}
	close_pipes(c, 2 * c->ncmds);
	wait_forks(c);
	signal(SIGINT, sig_handler);
}
