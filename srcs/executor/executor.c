/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:56:06 by abastos           #+#    #+#             */
/*   Updated: 2022/06/08 22:52:40 by abastos          ###   ########lyon.fr   */
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
	// int	in;
	// int	out;

	c->exec.process[curr_cmd] = fork();
	if (c->exec.process[curr_cmd] < 0)
		return (perror("fork"));
	if (c->exec.process[curr_cmd] == 0)
	{
		// todo: check utility of these functions
		// in_selector(c, curr_cmd, &in);
		// out_selector(c, curr_cmd, piped_commands, &out);
		// todo end
		if (curr_cmd == 0)
			switch_pipes(c->exec.pipe_fd[0], c->exec.pipe_fd[1]);
		else if (curr_cmd == piped_commands - 1)
			switch_pipes(c->exec.pipe_fd[2 * curr_cmd - 2],
				c->cmds[curr_cmd].outfile);
		else
			switch_pipes(c->exec.pipe_fd[2 * curr_cmd - 2],
				c->exec.pipe_fd[2 * curr_cmd + 1]);
		close_pipes(c, 2 * piped_commands);
		execve(c->cmds[curr_cmd].exec_path,
			c->cmds[curr_cmd].argv, NULL);
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

	c->exec.pipe_fd = malloc(sizeof(int) * (cmds * 2));
	i = 0;
	while (i < cmds)
	{
		if (pipe(c->exec.pipe_fd + 2 * i++) < 0)
		{
			return (perror("pipe"));
			free(c->exec.pipe_fd);
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
	int		piped_commands;

	piped_commands = 0;
	while (&c->cmds[piped_commands])
		piped_commands++;
	pipe_fd(c, piped_commands);
	i = 0;
	while (&c->cmds[i])
		exec_child(c, i++, piped_commands);
	close_pipes(c, 2 * piped_commands);
	i = 0;
	while (i < piped_commands)
		waitpid(c->exec.process[i++], 0, 0);
	return (piped_commands);
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
		execve(c->cmds[cmd].exec_path,
			c->cmds[cmd].argv, c->env_list);
		perror("execve");
		exit(0);
	}
	else
		waitpid(pid, &c->return_code, 0);
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
	// int		i;

	// todo: rewrite all redirections functions
	// i = 0;
	// while (c->command_table[i])
	// 	outfile_handler(c, i++);
	set_exec_path(c);
	exec_piped(c);
}
