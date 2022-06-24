/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:56:06 by abastos           #+#    #+#             */
/*   Updated: 2022/06/24 17:56:06 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function executes the child process
 *
 * @param table Commands table struct
 * @param cmd Current fork
 * @param curr Current command to execute
 * @param ncmd Number of piped commands
 */
static void	exec_child(t_ctx *c, int curr, int ncmd)
{
	int	in;
	int	out;

	if (EDEBUG)
		printf("Executing command %d\n", curr);
	signal(SIGINT, fork_sig_handler);
	termios_set(c, 1);
	if (exec_builtin(c, c->cmds[curr])) // function to execute builtins with redirections
		return ;
	c->exec->process[curr] = fork();
	if (c->exec->process[curr] < 0)
		return (perror("fork"));
	if (c->exec->process[curr] == 0)
	{
		infile_handler(c, curr);
		outfile_handler(c, curr);
		in_selector(c, curr, &in);
		out_selector(c, curr, ncmd, &out);
		if (curr == ncmd - 1)
			switch_pipes(in, out);
		else if (curr == 0)
			switch_pipes(in, out);
		else
			switch_pipes(in, out);
		close_pipes(c, 2 * ncmd);
		// if (WEXITSTATUS(g_return) == 0)
		if (set_exec_path(c) == false)
			return ;
		execve(c->cmds[curr].exec_path,
			c->cmds[curr].argv, c->env_list);
		// else
		// 	exit(1);
	}
	else
	{
		waitpid(c->exec->process[curr], &g_return, 0);
	}
}

/**
 * @brief This function is used to create a pipe array with pipe()
 * in table->pipe_fd
 *
 * @param table Commands table struct
 * @param piped_commands Number of piped commands
 */
void	pipe_fd(t_ctx *c, int cmds)
{
	int	i;

	c->exec->pipe_fd = gb_calloc(cmds * 2, sizeof(int), CMD_GB, &c->gbc);
	i = 0;
	while (i < cmds)
	{
		if (pipe(c->exec->pipe_fd + 2 * i++) < 0)
		{
			perror("pipe");
			free(c->exec->pipe_fd);
			return ;
		}
	}
}

/**
 * @brief This function is the main function of execution
 *
 * @param c CMinishell context struct
 * @param table Commands table struct
 */
void	exec(t_ctx *c)
{
	int		i;

	c->exec = gb_calloc(1, sizeof(t_exec), CMD_GB, &c->gbc);
	c->exec->process = gb_calloc(c->ncmds, sizeof(pid_t), CMD_GB, &c->gbc);
	pipe_fd(c, c->ncmds);
	i = 0;
	while (i < c->ncmds)
		exec_child(c, i++, c->ncmds);
	close_pipes(c, 2 * c->ncmds);
	i = 0;
	while (i < c->ncmds)
		waitpid(c->exec->process[i++], &g_return, 0);
	signal(SIGINT, sig_handler);
}
