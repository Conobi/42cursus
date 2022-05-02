/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:56:06 by abastos           #+#    #+#             */
/*   Updated: 2022/03/30 16:39:34 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		in_selector(table, curr_cmd, &in);
		out_selector(table, curr_cmd, piped_commands, &out);
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

void	exec_single(t_table *table, int cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror("fork"));
	if (pid == 0)
	{
		execve(table->command_table[cmd].exec_path,
			table->command_table[cmd].args, NULL);
		perror("execve");
		exit(0);
	}
	else
		waitpid(pid, 0, 0);
}

void	exec(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->commands_num)
		outfile_handler(table, i++);
	set_exec_path(table);
	i = 0;
	while (i < table->commands_num)
	{
		if (table->command_table[i].piped)
			i = exec_piped(table, i);
		if (i < 0)
			return ;
		exec_single(table, i);
		free(table->command_table[i].exec_path);
		i++;
	}
}
