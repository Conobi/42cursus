/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:06:55 by abastos           #+#    #+#             */
/*   Updated: 2022/09/28 17:59:34 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	out_open_appd(t_ctx *c, int curr_cmd, int i)
{
	c->cmds[curr_cmd].outfile = fdgb_add(open(
				c->cmds[curr_cmd].redirections[i].arg,
				O_CREAT | O_RDWR | O_APPEND, 0000644),
			&c->fdgbc, CMD_GB);
	if (c->cmds[curr_cmd].outfile < 0)
	{
		file_errors(c, (t_error){FILE_ERR, SHELL_NAME,
			NULL, c->cmds[curr_cmd].redirections[i].arg, 1, true});
		return (false);
	}
	return (true);
}

static bool	out_open_out(t_ctx *c, int curr_cmd, int i)
{
	c->cmds[curr_cmd].outfile = fdgb_add(open(
				c->cmds[curr_cmd].redirections[i].arg,
				O_CREAT | O_RDWR | O_TRUNC, 0000644),
			&c->fdgbc, CMD_GB);
	if (c->cmds[curr_cmd].outfile < 0)
	{
		file_errors(c, (t_error){FILE_ERR, SHELL_NAME,
			NULL, c->cmds[curr_cmd].redirections[i].arg, 1, true});
		return (false);
	}
	return (true);
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
	if (c->cmds[curr_cmd].redc >= 0)
		c->cmds[curr_cmd].outfile = 1;
	i = 0;
	while (i < c->cmds[curr_cmd].redc)
	{
		if (c->cmds[curr_cmd].redirections[i].type == APPD_TK)
		{
			if (!out_open_appd(c, curr_cmd, i))
				break ;
		}
		else if (c->cmds[curr_cmd].redirections[i].type == OUT_TK)
			if (!out_open_out(c, curr_cmd, i))
				break ;
		i++;
	}
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
