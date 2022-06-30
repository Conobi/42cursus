/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:38:05 by conobi            #+#    #+#             */
/*   Updated: 2022/06/30 17:29:49 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_tk_err(t_ctx *c, char *token)
{
	syntax_err(c, token);
	return (0);
}

// static bool	is_redirection(char *str)
// {
// 	if (
// 		ft_eq(str, ">", 0)
// 		|| ft_eq(str, "<", 0)
// 		|| ft_eq(str, ">>", 0)
// 		|| ft_eq(str, "<<", 0)
// 	)
// 		return (true);
// 	return (false);
// }

/*
	Permet de vérifier la syntaxe des redirections.
	Si une redirection n'a pas d'argument correct, elle se retrouve dans
	argc/argv. Du coup, si on trouve une redirection dans argc/argv,
	on regarde, si elle en a une voisine et si elle est dans un pipe.
*/
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
			if (token_type(c->cmds[i].argv[j]) > 0)
			{
				if (
					j < c->cmds[i].argc - 1
					&& token_type(c->cmds[i].argv[j + 1]) > 0
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
