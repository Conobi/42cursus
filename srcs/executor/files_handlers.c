/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:55:51 by abastos           #+#    #+#             */
/*   Updated: 2022/08/12 14:38:08 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_file(t_ctx *c, int curr_cmd, int i)
{
	if (c->cmds[curr_cmd].redirections[i].type == APPD_TK)
	{
		c->cmds[curr_cmd].outfile = open(
				c->cmds[curr_cmd].redirections[i].arg,
				O_CREAT | O_RDWR | O_APPEND, 0000644);
		if (c->cmds[curr_cmd].outfile < 0)
			file_errors(c, (t_error){FILE_ERR, SHELL_NAME,
				NULL, c->cmds[curr_cmd].redirections[i].arg, 1, true});
	}
	else if (c->cmds[curr_cmd].redirections[i].type == OUT_TK)
	{
		c->cmds[curr_cmd].outfile = open(
				c->cmds[curr_cmd].redirections[i].arg,
				O_CREAT | O_RDWR | O_TRUNC, 0000644);
		if (c->cmds[curr_cmd].outfile < 0)
			file_errors(c, (t_error){FILE_ERR, SHELL_NAME,
				NULL, c->cmds[curr_cmd].redirections[i].arg, 1, true});
	}
}

/**
 * @brief This function is used to handle all outfile redirections
 *
 * @param c Minshell context struct
 * @param curr_cmd Index of current command
 */
void	outfile_handler(t_ctx *c, int curr_cmd)
{
	int	i;

	c->cmds[curr_cmd].outfile = -2;
	if (c->cmds[curr_cmd].redc == 0)
	{
		c->cmds[curr_cmd].outfile = 1;
		return ;
	}
	i = -1;
	while (++i < c->cmds[curr_cmd].redc)
		open_file(c, curr_cmd, i);
}

/**
 * @brief This function is used to handle all infile redirections
 *
 * @param c Minishell context struct
 * @param curr_cmd Index of current command
 */
void	infile_handler(t_ctx *c, int curr_cmd)
{
	int	i;

	c->cmds[curr_cmd].infile = -2;
	if (c->cmds[curr_cmd].redc == 0)
	{
		c->cmds[curr_cmd].infile = 0;
		return ;
	}
	i = 0;
	while (i < c->cmds[curr_cmd].redc)
	{
		if (c->cmds[curr_cmd].redirections[i].type == HRDC_TK)
			c->cmds[curr_cmd].infile = c->cmds[curr_cmd].heredoc;
		if (c->cmds[curr_cmd].redirections[i].type == IN_TK)
		{
			c->cmds[curr_cmd].infile = open(
					c->cmds[curr_cmd].redirections[i].arg, O_RDONLY);
			if (c->cmds[curr_cmd].infile < 0)
				file_errors(c, (t_error){FILE_ERR, SHELL_NAME,
					NULL, c->cmds[curr_cmd].redirections[i].arg, 1, true});
		}
		i++;
	}
}

/**
 * @brief This function is used to handle infile redirection
 *
 * @param curr Index of current command
 * @param in File descriptor to modify for input
 */
void	in_selector(t_ctx *c, int curr, int *in)
{
	if (c->cmds[curr].infile == -1)
		*in = -1;
	else if (c->cmds[curr].infile != -2 && c->cmds[curr].infile != 0)
		*in = c->cmds[curr].infile;
	else if (curr == 0)
		*in = 0;
	else
		*in = c->exec->pipe_fd[2 * curr - 2];
}

/**
 * @brief This function is used to handle outfile redirection
 *
 * @param c Minishell context struct
 * @param curr Index of current command
 * @param out File descriptor to modify for output
 */
void	out_selector(t_ctx *c, int curr, int *out)
{
	if (c->cmds[curr].outfile == -1)
		*out = -1;
	else if (c->cmds[curr].outfile != -2 && c->cmds[curr].outfile != 1)
		*out = c->cmds[curr].outfile;
	else if (curr == c->ncmds - 1)
		*out = c->cmds[curr].outfile;
	else if (curr == 0)
		*out = c->exec->pipe_fd[1];
	else
		*out = c->exec->pipe_fd[2 * curr + 1];
}
