/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:21:18 by conobi            #+#    #+#             */
/*   Updated: 2022/06/30 17:12:25 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Cette fonction teste si il existe des pipes ne contenant
	ni argument, ni redirections. Si c'est le cas, on throw une erreur.
*/
short	test_pipe(t_ctx *c)
{
	int	i;

	i = -1;
	if (c->ncmds > 1)
	{
		while (++i < c->ncmds)
		{
			if (c->cmds[i].argc == 0 && c->cmds[i].redc == 0)
			{
				syntax_err(c, "|");
				return (0);
			}
		}
	}
	return (1);
}
