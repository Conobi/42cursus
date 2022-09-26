/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:56:06 by abastos           #+#    #+#             */
/*   Updated: 2022/09/26 19:56:54 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_handler(t_ctx *c, int curr, int *in, int *out)
{
	if (c->cmds[curr].is_builtins)
	{
		dup2(*out, STDOUT_FILENO);
		g_return = exec_builtin(c, c->cmds[curr]);
		dup2(STDIN_FILENO, STDOUT_FILENO);
	}
	else
	{
		c->exec->process[c->exec->curr_process] = fork();
		if (c->exec->process[c->exec->curr_process] < 0)
			return (perror("fork"));
		if (c->exec->process[c->exec->curr_process] == 0)
			exec_fork(c, curr, in, out);
		c->exec->curr_process += 1;
	}
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
		fdgb_close(&c->fdgbc, CMD_GB);
		c->cmds[curr].errored = true;
		return ;
	}
	if (c->cmds[curr].argc >= 1)
		exec_handler(c, curr, &in, &out);
	fdgb_close(&c->fdgbc, CMD_GB);
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
	if (c->cmds[c->ncmds - 1].argc > 0 && !is_builtin(c->cmds[c->ncmds - 1]))
	{
		while (i < c->ncmds)
		{
			waitpid(c->exec->process[i], &status, 0);
			child_status(status);
			i++;
		}
	}
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
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
	c->exec->nprocess = 0;
	i = -1;
	while (++i < c->ncmds)
	{
		if (c->cmds[i].argc > 0 && !is_builtin(c->cmds[i]))
		{
			c->cmds[i].is_builtins = false;
			c->exec->nprocess++;
		}
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
	fdgb_close(&c->fdgbc, HEREDOCS_GB);
	wait_forks(c);
}
