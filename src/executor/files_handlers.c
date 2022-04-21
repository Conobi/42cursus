/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:55:51 by abastos           #+#    #+#             */
/*   Updated: 2022/03/30 16:41:37 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	outfile_handler(t_table *table, int curr_cmd)
{
	int	i;

	if (table->command_table[curr_cmd].outfiles[0])
	{
		i = 0;
		while (table->command_table[curr_cmd].outfiles[i])
		{
			table->command_table[curr_cmd].outfile = open(
					table->command_table[curr_cmd].outfiles[i],
					O_CREAT | O_RDWR | O_TRUNC, 0000644);
			i++;
		}
	}
	else
		table->command_table[curr_cmd].outfile = 1;
}

void	infile_handler(t_table *table, int curr_cmd)
{
	int	i;

	if (table->command_table[curr_cmd].infiles[0])
	{
		i = 0;
		while (table->command_table[curr_cmd].infiles[i])
		{
			table->command_table[curr_cmd].infile = open(
					table->command_table[curr_cmd].infiles[i],
					O_CREAT | O_RDWR | O_TRUNC, 0000644);
			i++;
		}
	}
}

void	in_selector(t_table *table, int curr, int *in)
{
	// if (table->command_table[curr].infile)
	// 	*in = table->command_table[curr].infile;
	if (curr == 0)
		*in = table->pipe_fd[0];
	else
		*in = table->pipe_fd[2 * curr - 2];
}

void	out_selector(t_table *table, int curr, int piped_commands, int *out)
{
	if (table->command_table[curr].outfile)
		*out = table->command_table[curr].outfile;
	else if (curr == 0)
		*out = table->pipe_fd[1];
	else if (curr == piped_commands - 1)
	{
		if (table->command_table[curr].outfile)
			*out = table->command_table[curr].outfile;
		else
			*out = 1;
	}
	else
		*out = table->pipe_fd[2 * curr + 1];
}
