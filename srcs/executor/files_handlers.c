/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:55:51 by abastos           #+#    #+#             */
/*   Updated: 2022/06/09 19:51:09 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function is used to handle all outfile redirections
 *
 * @param c Commands table struct
 * @param curr_cmd Index of current command
 */
void	outfile_handler(t_ctx *c, int curr_cmd)
{
	int	i;

	if (c->cmds[curr_cmd].redc == 0)
	{
		c->cmds[curr_cmd].outfile = 1;
		return ;
	}
	i = 0;
	while (i < c->cmds[curr_cmd].redc)
	{
		if (c->cmds[curr_cmd].redirections[i].type == APPD_TK)
		{
			c->cmds[curr_cmd].outfile = open(
					c->cmds[curr_cmd].redirections[i].arg,
					O_CREAT | O_RDWR | O_APPEND, 0000644);
		}
		if (c->cmds[curr_cmd].redirections[i].type == OUT_TK)
		{
			c->cmds[curr_cmd].outfile = open(
					c->cmds[curr_cmd].redirections[i].arg,
					O_CREAT | O_RDWR | O_TRUNC, 0000644);
		}
		i++;
	}
}

/**
 * @brief This function is used to handle all infile redirections
 *
 * @param table Commands table struct
 * @param curr_cmd Index of current command
 */
void	infile_handler(t_ctx *c, int curr_cmd)
{
	int	i;

	if (c->cmds[curr_cmd].redc == 0)
	{
		c->cmds[curr_cmd].infile = 0;
		return ;
	}
	i = 0;
	while (i < c->cmds[curr_cmd].redc)
	{
		if (c->cmds[curr_cmd].redirections[i].type == HRDC_TK)
			create_heredoc(c, c->cmds[curr_cmd].redirections[i].arg);
		if (c->cmds[curr_cmd].redirections[i].type == IN_TK)
		{
			c->cmds[curr_cmd].infile = open(
					c->cmds[curr_cmd].redirections[i].arg, O_RDONLY);
		}
		i++;
	}
}

// Deprecated functions
/**
 * @brief This function is used to handle infile redirection
 *
 * @param table Commands table struct
 * @param curr Index of current command
 * @param in File descriptor to modify for input
 */
void	in_selector(t_ctx *c, int curr, int piped_commands, int *in)
{
	if (c->cmds[curr].infile)
		*in = c->cmds[curr].infile;
	else if (curr == piped_commands)
		*in = c->cmds[curr].outfile;
	else if (curr == 0)
		*in = 0;
	else if (c->ncmds > 1)
		*in = c->exec->pipe_fd[2 * curr - 2];
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
	if (c->cmds[curr].outfile)
		*out = c->cmds[curr].outfile;
	else if (curr == 0)
		*out = c->exec->pipe_fd[1];
	else if (curr == piped_commands - 1)
		*out = c->cmds[curr].outfile;
	else
		*out = c->exec->pipe_fd[2 * curr + 1];
}
