/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:38:05 by conobi            #+#    #+#             */
/*   Updated: 2022/07/01 19:48:11 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_tk_err(t_ctx *c, char *token)
{
	syntax_err(c, token);
	return (0);
}

// static void	throw_heredoc_error(t_ctx *c, int i, int j)
// {
// 	if (
// 		j < c->cmds[i].argc - 1
// 		&& token_type(c->cmds[i].argv[j + 1]) > OTHR_TK
// 	)
// 			c->heredoc_errored = gb_add(
// 				ft_strdup(c->cmds[i].argv[j + 1]), &c->gbc, CMD_GB);
// 	else if (i < c->ncmds - 1)
// 		c->heredoc_errored = gb_add(
// 				ft_strdup("|"), &c->gbc, CMD_GB);
// 	else
// 		c->heredoc_errored = gb_add(
// 				ft_strdup("newline"), &c->gbc, CMD_GB);
// }

static short	throw_redirection_error(t_ctx *c, int i, int j)
{
	if (
		j < c->cmds[i].argc - 1
		&& token_type(c->cmds[i].argv[j + 1]) > OTHR_TK
	)
		return (print_tk_err(c, c->cmds[i].argv[j + 1]));
	else if (i < c->ncmds - 1)
		return (print_tk_err(c, "|"));
	else
		return (print_tk_err(c, "newline"));
}

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
			// if (token_type(c->cmds[i].argv[j]) == HRDC_TK)
			// 	throw_heredoc_error(c, i, j);
			if (token_type(c->cmds[i].argv[j]) > OTHR_TK)
				return (throw_redirection_error(c, i, j));
		}
	}
	return (1);
}
