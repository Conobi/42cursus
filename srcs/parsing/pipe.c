/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:37:16 by conobi            #+#    #+#             */
/*   Updated: 2022/05/17 18:44:25 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Si action == 1, on compte le nombre de pipes,
// sinon on compte le nombre de caractères jusqu'au prochain pipe
static int	pipe_count(char *curr, int actioncnt)
{
	char	squoted;
	char	dquoted;
	char	*cur;

	cur = curr;
	squoted = -1;
	dquoted = -1;
	while (*cur)
	{
		if (!actioncnt)
			actioncnt++;
		if (*cur == '\'' && dquoted == -1)
			squoted *= -1;
		if (*cur == '"' && squoted == -1)
			dquoted *= -1;
		else if (squoted == -1 && dquoted == -1 && *cur == '|')
		{
			if (!actioncnt)
				break ;
			actioncnt++;
		}
		cur++;
	}
	return (actioncnt);
}

static void	cutter_init(t_ctx *c)
{
	c->parser.pipes_n = pipe_count(c->entry, 1);
	c->parser.pipes = gb_calloc(c->parser.pipes_n,
			sizeof(char **), PIPE_GB, &c->gbc);
	c->parser.pipes[0] = gb_calloc(pipe_count(c->entry, 0) + 1,
			sizeof(char *), PIPE_GB, &c->gbc);
}

static char	pipe_quote(t_ctx *c, char curr)
{
	return (c->parser.squoted == -1 && c->parser.dquoted == -1 && curr == '|');
}

// Tant qu'on a pas fini le string, on split à chaque pipe
void	pipe_cutter(t_ctx *c)
{
	char	*cur;
	int		i;
	int		j;

	cur = c->entry;
	printf("{ nb pipes: %d }\n", pipe_count(cur, 1));
	cutter_init(c);
	printf("%d\n", pipe_count(cur, 0));
	i = 0;
	j = -1;
	while (*cur)
	{
		set_quote_bool(c, *cur);
		if (pipe_quote(c, *cur))
		{
			cur++;
			c->parser.pipes[++i] = gb_calloc(pipe_count(cur, 0) + 1,
					sizeof(char *), PIPE_GB, &c->gbc);
			printf("[%d: %d]\n", i, pipe_count(cur, 0));
			j = -1;
		}
		c->parser.pipes[i][++j] = 0;
		if (!pipe_quote(c, *cur))
			c->parser.pipes[i][j] = *cur;
		if (*cur != '|')
			cur++;
	}
}
