/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:56:06 by abastos           #+#    #+#             */
/*   Updated: 2022/06/15 19:29:52 by abastos          ###   ########lyon.fr   */
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

	printf("Executing command %d\n", curr);
	signal(SIGINT, fork_sig_handler);
	termios_set(c, 1);
	if (exec_builtin(c, c->cmds[curr]))
		return ;
	c->exec->process[curr] = fork();
	if (c->exec->process[curr] < 0)
		return (perror("fork"));
	if (c->exec->process[curr] == 0)
	{
		in_selector(c, curr, &in);
		out_selector(c, curr, ncmd, &out);
		// if (c->cmds[curr_cmd].redirections[i].type == HRDC_TK)
		// 	c->cmds[curr_cmd].infile = create_heredoc(c, c->cmds[curr_cmd].redirections[i].arg);
		if (curr == ncmd - 1)
			switch_pipes(in, out);
		else if (curr == 0)
			switch_pipes(in, out);
		else
			switch_pipes(in, out);
		close_pipes(c, 2 * ncmd);
		execve(c->cmds[curr].exec_path,
			c->cmds[curr].argv, c->env_list);
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

	c->exec->pipe_fd = malloc(sizeof(int) * (cmds * 2));
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
 * @brief This function is called when a command is piped
 *
 * @param table Ccommands table struct
 * @param curr_command Current command to execute
 * @return int
 */
int	exec_piped(t_ctx *c)
{
	int		i;

	pipe_fd(c, c->ncmds);
	i = 0;
	while (i < c->ncmds)
		exec_child(c, i++, c->ncmds);
	close_pipes(c, 2 * c->ncmds);
	i = 0;
	while (i < c->ncmds)
		waitpid(c->exec->process[i++], &g_return, 0);
	signal(SIGINT, sig_handler);
	return (c->ncmds);
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

	// todo: rewrite all redirections functions
	i = -1;
	while (++i < c->ncmds)
	{
		infile_handler(c, i);
		outfile_handler(c, i);
	}
	c->exec = gb_calloc(1, sizeof(t_exec), CMD_GB, &c->gbc);
	c->exec->process = gb_calloc(c->ncmds, sizeof(pid_t), CMD_GB, &c->gbc);
	if (set_exec_path(c) == false)
		return ;
	exec_piped(c);
}
