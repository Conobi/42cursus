/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:56:06 by abastos           #+#    #+#             */
/*   Updated: 2022/05/19 18:16:34 by abastos          ###   ########lyon.fr   */
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
void	exec_child(t_table *table, int cmd,
	int curr_cmd, int piped_commands)
{
	int	in;
	int	out;

	table->process[curr_cmd] = fork();
	if (table->process[curr_cmd] < 0)
		return (perror("fork"));
	if (table->process[curr_cmd] == 0)
	{
		// todo: check utility of these functions
		in_selector(table, curr_cmd, &in);
		out_selector(table, curr_cmd, piped_commands, &out);
		// todo end
		if (curr_cmd == 0)
			switch_pipes(table->pipe_fd[0], table->pipe_fd[1]);
		else if (curr_cmd == piped_commands - 1)
			switch_pipes(table->pipe_fd[2 * curr_cmd - 2],
				table->command_table[cmd].outfile);
		else
			switch_pipes(table->pipe_fd[2 * curr_cmd - 2],
				table->pipe_fd[2 * curr_cmd + 1]);
		close_pipes(table, 2 * piped_commands);
		execve(table->command_table[cmd].exec_path,
			table->command_table[cmd].args, NULL);
	}
}

/**
 * @brief This function is used to create a pipe array with pipe()
 * in table->pipe_fd
 *
 * @param table Commands table struct
 * @param piped_commands Number of piped commands
 */
void	pipe_fd(t_table *table, int piped_commands)
{
	int	i;

	table->pipe_fd = malloc(sizeof(int) * (piped_commands * 2));
	i = 0;
	while (i < piped_commands)
	{
		if (pipe(table->pipe_fd + 2 * i++) < 0)
		{
			return (perror("pipe"));
			free(table->pipe_fd);
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
int	exec_piped(t_table *table, int curr_command)
{
	int		i;
	int		piped_commands;

	i = 0;
	piped_commands = curr_command;
	while (table->command_table[piped_commands++].piped)
		i++;
	piped_commands = i;
	pipe_fd(table, piped_commands);
	i = 0;
	while (i < piped_commands)
		exec_child(table, curr_command++, i++, piped_commands);
	close_pipes(table, 2 * piped_commands);
	i = 0;
	while (i < piped_commands)
		waitpid(table->process[i++], 0, 0);
	return (piped_commands);
}

/**
 * @brief this function is called when the current command is not piped
 *
 * @param table Commands table struct
 * @param cmd Index of the command to execute
 */
void	exec_single(t_ctx *c, t_table *table, int cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror("fork"));
	if (pid == 0)
	{
		if (!table->command_table[cmd].exec_path)
			return ;
		execve(table->command_table[cmd].exec_path,
			table->command_table[cmd].args, c->env_list);
		perror("execve");
		exit(0);
	}
	else
		waitpid(pid, &c->return_code, 0);
}

/**
 * @brief This function is the main function of execution
 *
 * @param c CMinishell context struct
 * @param table Commands table struct
 */
void	exec(t_ctx *c, t_table *table)
{
	int		i;

	i = 0;
	while (i < table->commands_num)
		outfile_handler(table, i++);
	set_exec_path(c, table);
	i = 0;
	while (i < table->commands_num)
	{
		if (!table->command_table[i].exec_path)
			return ;
		if (table->command_table[i].piped)
			i = exec_piped(table, i);
		if (i < 0)
			return ;
		if (ft_eq(table->command_table[i].exec_path, "/bin/ls", 0)
			&& !table->command_table[i].args[1])
			return (b_ls(c, table, i));
		exec_single(c, table, i);
		i++;
	}
}
