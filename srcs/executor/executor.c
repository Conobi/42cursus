/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:56:06 by abastos           #+#    #+#             */
/*   Updated: 2022/09/28 18:11:55 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_handler(t_ctx *c, int curr, int *in, int *out)
{
	printf("%s in %d out %d\n", c->cmds[curr].argv[0], *in, *out);
	if (c->cmds[curr].is_builtins)
	{
		if (*in < 0 || *out < 0)
		{
			fdgb_close(&c->fdgbc, CMD_GB);
			close_pipes(c, c->ncmds * 2);
			g_return = 1;
			return ;
		}
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
	io_handler(c, curr, &in, &out);
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
	int	j;
	int	status;

	i = 0;
	if (c->cmds[c->ncmds - 1].argc > 0)
	{
		j = 0;
		while (i < c->ncmds)
		{
			if (!c->cmds[i].is_builtins)
			{
				waitpid(c->exec->process[j++], &status, 0);
				if (!c->cmds[c->ncmds - 1].is_builtins)
					child_status(status);
			}
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
