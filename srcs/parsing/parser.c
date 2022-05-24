/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 18:11:57 by conobi            #+#    #+#             */
/*   Updated: 2022/05/24 18:27:47 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_print(t_ctx *c)
{
	c += 0;
	printf("Jacques a dit: [%s] (%d)\n", c->entry, (int)c->entry[0]);
}

static void	multi_viewer(char **pipes, int cnt)
{
	int	i;

	i = -1;
	printf("Liste des pipes: \n");
	while (++i < cnt && pipes[i])
		printf("{%d: %s}\n", i, pipes[i]);
}

void	parser(t_ctx *c)
{
	int	i;

	if (!c->entry
		|| !ft_strncmp(c->entry, "exit", 5)
		|| !ft_strncmp(c->entry, "bye", 3))
		exit_shell(c, 0);
	pipe_cutter(c);
	multi_viewer(c->parser.pipes, c->parser.pipes_n);
	printf("-----------------\n");
	i = -1;
	while (c->parser.pipes[++i])
		split_quote(c, c->parser.pipes[i]);
	printf("-----------------\n");
	parse_print(c);
}

// Tant que l'on atteint pas de pipe (et qu'on est hors quote):
//	- On cut
