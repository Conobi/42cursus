/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:07:51 by abastos           #+#    #+#             */
/*   Updated: 2022/09/21 18:08:03 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	in_open(t_ctx *c, int curr_cmd, int i)
{
	if (c->cmds[curr_cmd].redirections[i].type == HRDC_TK)
		c->cmds[curr_cmd].infile = c->cmds[curr_cmd].heredoc;
	if (c->cmds[curr_cmd].redirections[i].type == IN_TK)
	{
		c->cmds[curr_cmd].infile = open(
				c->cmds[curr_cmd].redirections[i].arg, O_RDONLY);
		if (c->cmds[curr_cmd].infile < 0)
		{
			file_errors(c, (t_error){FILE_ERR, SHELL_NAME,
				NULL, c->cmds[curr_cmd].redirections[i].arg, 1, true});
			return (false);
		}
	}
	return (true);
}

/**
 * @brief This function is used to handle all infile redirections
 *
 * @param c Minishell context struct
 * @param curr_cmd Index of current command
 */
bool	infile_handler(t_ctx *c, int curr_cmd)
{
	int	i;

	c->cmds[curr_cmd].infile = -2;
	if (c->cmds[curr_cmd].redc == 0)
	{
		c->cmds[curr_cmd].infile = 0;
		return (true);
	}
	i = 0;
	while (i < c->cmds[curr_cmd].redc)
	{
		if (!in_open(c, curr_cmd, i))
			return (false);
		i++;
	}
	return (true);
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
