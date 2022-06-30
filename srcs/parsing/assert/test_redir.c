/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:38:05 by conobi            #+#    #+#             */
/*   Updated: 2022/06/30 15:45:02 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_tk_err(t_ctx *c, char *token)
{
	syntax_err(c, token);
	return (0);
}

static bool	is_redirection(char *str)
{
	if (
		ft_eq(str, ">", 0)
		|| ft_eq(str, "<", 0)
		|| ft_eq(str, ">>", 0)
		|| ft_eq(str, "<<", 0)
	)
		return (true);
	return (false);
}

short	test_redir(t_ctx *c)
{
	int	i;
	int	j;

	i = -1;
	while (++i < c->ncmds)
	{
		j = -1;
		while (++j < c->cmds[i].argc)
		{
			if (is_redirection(c->cmds[i].argv[j]))
			{
				if (
					j < c->cmds[i].argc - 1
					&& is_redirection(c->cmds[i].argv[j + 1])
				)
					return (print_tk_err(c, c->cmds[i].argv[j + 1]));
				else if (i < c->ncmds - 1)
					return (print_tk_err(c, "|"));
				else
					return (print_tk_err(c, "newline"));
			}
		}
	}
	return (1);
}
