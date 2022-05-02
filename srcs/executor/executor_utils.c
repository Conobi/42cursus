/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:55:49 by abastos           #+#    #+#             */
/*   Updated: 2022/03/30 16:54:42 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_exec(char *exec_name)
{
	char	**path;
	char	*pre_exec;
	char	*exec_path;
	int		i;

	path = ft_split(getenv("PATH"), ':');
	i = 0;
	while (path[i])
	{
		pre_exec = ft_strjoin("/", exec_name);
		exec_path = ft_strjoin(path[i], pre_exec);
		free(path[i]);
		free(pre_exec);
		if (access(exec_path, X_OK) == 0)
			return (exec_path);
		free(exec_path);
		i++;
	}
	free(path);
	return (NULL);
}

void	close_pipes(t_table *table, int pipes)
{
	int	i;

	i = 0;
	while (i < pipes)
		close(table->pipe_fd[i++]);
}

void	switch_pipes(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
}

void	set_exec_path(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->commands_num)
	{
		table->command_table[i].exec_path = find_exec(
				table->command_table[i].args[0]);
		if (!table->command_table[i].exec_path)
		{
			printf("%s: %s\n", table->command_table[i].args[0],
				"command not found");
			return ;
		}
		i++;
	}
}
