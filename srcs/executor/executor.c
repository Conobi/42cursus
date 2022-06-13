/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:56:06 by abastos           #+#    #+#             */
/*   Updated: 2022/06/13 20:08:13 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function executes the child process
 *
 * @param table Commands table struct
 * @param cmd Current fork
 * @param curr_cmd Current command to execute
 * @param piped_commands Number of piped commands
 */
void	exec_child(t_ctx *c, int curr_cmd, int piped_commands)
{
	int	in;
	int	out;

	printf("Executing command %d\n", curr_cmd);
	c->exec->process[curr_cmd] = fork();
	if (c->exec->process[curr_cmd] < 0)
		return (perror("fork"));
	if (c->exec->process[curr_cmd] == 0)
	{
		in_selector(c, curr_cmd, &in);
		out_selector(c, curr_cmd, piped_commands, &out);
		if (curr_cmd == piped_commands - 1)
			switch_pipes(in, out);
		else if (curr_cmd == 0)
			switch_pipes(in, out);
		else
			switch_pipes(in, out);
		close_pipes(c, 2 * piped_commands);
		if (exec_builtin(c, c->cmds[curr_cmd]))
			exit(0);
		exit(execve(c->cmds[curr_cmd].exec_path,
				c->cmds[curr_cmd].argv, c->env_list));
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
			return (perror("pipe"));
			free(c->exec->pipe_fd);
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
		waitpid(c->exec->process[i++], 0, 0);
	return (c->ncmds);
}

/**
 * @brief this function is called when the current command is not piped
 *
 * @param table Commands table struct
 * @param cmd Index of the command to execute
 */
void	exec_single(t_ctx *c, int cmd)
{
	pid_t	pid;
	int		in;
	int		out;

	pid = fork();
	if (pid < 0)
		return (perror("fork"));
	termios_set(c, 1);
	signal(SIGINT, fork_sig_handler);
	signal(SIGQUIT, fork_sig_handler);
	if (pid == 0)
	{
		if (!c->cmds[cmd].exec_path)
			return ;
		in_selector(c, cmd, &in);
		out_selector(c, cmd, c->ncmds, &out);
		switch_pipes(in, out);
		if (exec_builtin(c, c->cmds[cmd]))
			exit(0);
		execve(c->cmds[cmd].exec_path,
			c->cmds[cmd].argv, c->env_list);
		perror("execve");
		exit(0);
	}
	else
		waitpid(pid, &g_return, 0);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler); //todo: function to switch signals
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
	set_exec_path(c);
	if (c->ncmds == 1)
		return (exec_single(c, 0));
	exec_piped(c);
}
