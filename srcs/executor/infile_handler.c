/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:07:51 by abastos           #+#    #+#             */
/*   Updated: 2022/09/27 13:46:10 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	in_open(t_ctx *c, int curr_cmd, int i)
{
	if (c->cmds[curr_cmd].redirections[i].type == HRDC_TK)
		c->cmds[curr_cmd].infile = c->cmds[curr_cmd].heredoc;
	if (c->cmds[curr_cmd].redirections[i].type == IN_TK)
	{
		c->cmds[curr_cmd].infile = fdgb_add(open(
					c->cmds[curr_cmd].redirections[i].arg, O_RDONLY),
				&c->fdgbc, CMD_GB);
		if (c->cmds[curr_cmd].infile < 0)
		{
			file_errors(c, (t_error){FILE_ERR, SHELL_NAME,
				NULL, c->cmds[curr_cmd].redirections[i].arg, 1, true});
		}
	}
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
		in_open(c, curr_cmd, i);
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
