/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:38:05 by conobi            #+#    #+#             */
/*   Updated: 2022/06/17 15:31:51 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_tk_err(t_ctx *c, char *token)
{
	syntax_err(c, token);
	return (0);
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
			if (
				ft_eq(c->cmds[i].argv[j], ">", 0)
				|| ft_eq(c->cmds[i].argv[j], "<", 0)
				|| ft_eq(c->cmds[i].argv[j], ">>", 0)
				|| ft_eq(c->cmds[i].argv[j], "<<", 0)
			)
			{
				if (j == c->cmds[i].argc - 1)
					return (print_tk_err(c, c->cmds[i].argv[j]));
				return (print_tk_err(c, c->cmds[i].argv[j + 1]));
			}
		}
	}
	return (1);
}
