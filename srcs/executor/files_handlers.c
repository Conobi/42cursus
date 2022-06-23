/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:55:51 by abastos           #+#    #+#             */
/*   Updated: 2022/06/17 17:00:27 by conobi           ###   ########lyon.fr   */
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

	c->cmds[curr_cmd].outfile = -1;
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

	c->cmds[curr_cmd].infile = -1;
	if (c->cmds[curr_cmd].redc == 0)
	{
		c->cmds[curr_cmd].infile = 0;
		return ;
	}
	i = 0;
	while (i < c->cmds[curr_cmd].redc)
	{
		if (c->cmds[curr_cmd].redirections[i].type == HRDC_TK)
			c->cmds[curr_cmd].infile = create_heredoc(c, c->cmds[curr_cmd].redirections[i].arg);
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
void	in_selector(t_ctx *c, int curr, int *in)
{
	if (EDEBUG)
	{
		printf("======in selection======\n");
		printf("%d in -> %d\n", curr, c->cmds[curr].infile);
	}
	if (c->cmds[curr].infile != -1)
	{
		if (EDEBUG)
			printf("enter in infile mode\n");
		*in = c->cmds[curr].infile;
	}
	else if (curr == 0)
	{
		if (EDEBUG)
			printf("enter in first cmd mode\n");
		*in = 0;
	}
	else
	{
		if (EDEBUG)
			printf("enter in last or middle cmd mode\n");
		*in = c->exec->pipe_fd[2 * curr - 2];
	}
	if (EDEBUG)
	{
		printf("%d in -> %d\n", curr, *in);
		printf("========================\n");
	}
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
	if (EDEBUG)
	{
		printf("======out selection======\n");
		printf("%d out -> %d\n", curr, c->cmds[curr].outfile);
	}
	if (c->cmds[curr].outfile != -1)
	{
		if (EDEBUG)
			printf("enter in outfile mode\n");
		*out = c->cmds[curr].outfile;
	}
	if (curr == piped_commands - 1)
	{
		if (EDEBUG)
			printf("enter in last cmd mode\n");
		*out = c->cmds[curr].outfile;
	}
	else if (curr == 0)
	{
		if (EDEBUG)
			printf("enter in first cmd mode\n");
		*out = c->exec->pipe_fd[1];
	}
	else
	{
		if (EDEBUG)
			printf("enter in middle cmd mode\n");
		*out = c->exec->pipe_fd[2 * curr + 1];
	}
	if (EDEBUG)
	{
		printf("%d out -> %d\n", curr, *out);
		printf("========================\n");
	}
}
