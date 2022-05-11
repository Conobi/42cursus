/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 18:11:57 by conobi            #+#    #+#             */
/*   Updated: 2022/05/11 18:49:59 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_print(t_ctx *c)
{
	c += 0;
	printf("Jacques a dit: [%s] (%d)\n", c->entry, (int)c->entry[0]);
}

void	parser(t_ctx *c)
{
	if (!c->entry
		|| !ft_strncmp(c->entry, "exit", 5)
		|| !ft_strncmp(c->entry, "bye", 3))
		exit_shell(c, 0);
	// pipe_cutter(c);
	parse_print(c);
}

// Tant que l'on atteint pas de pipe (et qu'on est hors quote):
//	- On cut
