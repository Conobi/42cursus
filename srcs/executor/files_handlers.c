/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:55:51 by abastos           #+#    #+#             */
/*   Updated: 2022/06/08 22:34:17 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function is used to handle all outfile redirections
 *
 * @param table Commands table struct
 * @param curr_cmd Index of current command
 */
void	outfile_handler(t_ctx *c, int curr_cmd)
{
	(void)c;
	(void)curr_cmd;
	// int	i;

	// if (table->command_table[curr_cmd].outfiles[0])
	// {
	// 	i = 0;
	// 	while (table->command_table[curr_cmd].outfiles[i])
	// 	{
	// 		table->command_table[curr_cmd].outfile = open(
	// 				table->command_table[curr_cmd].outfiles[i],
	// 				O_CREAT | O_RDWR | O_TRUNC, 0000644);
	// 		i++;
	// 	}
	// }
	// else
	// 	table->command_table[curr_cmd].outfile = 1;
}

/**
 * @brief This function is used to handle all infile redirections
 *
 * @param table Commands table struct
 * @param curr_cmd Index of current command
 */
void	infile_handler(t_ctx *c, int curr_cmd)
{
	(void)c;
	(void)curr_cmd;
	// int	i;

	// if (table->command_table[curr_cmd].infiles[0])
	// {
	// 	i = 0;
	// 	while (table->command_table[curr_cmd].infiles[i])
	// 	{
	// 		table->command_table[curr_cmd].infile = open(
	// 				table->command_table[curr_cmd].infiles[i],
	// 				O_CREAT | O_RDWR | O_TRUNC, 0000644);
	// 		i++;
	// 	}
	// }
}

// Deprecated functions
/**
 * @brief This function is used to handle infile redirection
 *
 * @param table Commands table struct
 * @param curr Index of current command
 * @param in File descriptor to modify for input
 */
void	in_selector(t_ctx *c, int curr, int *in)
{
	(void)c;
	(void)curr;
	(void)in;
	// if (table->command_table[curr].infile)
	// 	*in = table->command_table[curr].infile;
	// if (curr == 0)
	// 	*in = table->pipe_fd[0];
	// else
	// 	*in = table->pipe_fd[2 * curr - 2];
}

/**
 * @brief This function is used to handle outfile redirection
 *
 * @param table Commands table struct
 * @param curr Index of current command
 * @param piped_commands Number of piped commands
 * @param out File descriptor to modify for output
 */
void	out_selector(t_ctx *c, int curr, int piped_commands, int *out)
{
	(void)c;
	(void)curr;
	(void)piped_commands;
	(void)out;
	// if (table->command_table[curr].outfile)
	// 	*out = table->command_table[curr].outfile;
	// else if (curr == 0)
	// 	*out = table->pipe_fd[1];
	// else if (curr == piped_commands - 1)
	// {
	// 	if (table->command_table[curr].outfile)
	// 		*out = table->command_table[curr].outfile;
	// 	else
	// 		*out = 1;
	// }
	// else
	// 	*out = table->pipe_fd[2 * curr + 1];
}
