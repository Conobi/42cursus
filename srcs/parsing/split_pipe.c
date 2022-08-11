/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:37:16 by conobi            #+#    #+#             */
/*   Updated: 2022/08/11 17:29:45 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Si action == 0 on compte le nombre de caractères jusqu'au prochain pipe,
	Si action == 1, on compte le nombre de pipes.
*/
static int	pipe_count(char *cur, const int action)
{
	bool	squoted;
	bool	dquoted;
	int		cnt;

	squoted = false;
	dquoted = false;
	cnt = action;
	while (*cur)
	{
		if (*cur == '\'' && dquoted == false)
			squoted = !squoted;
		if (*cur == '"' && squoted == false)
			dquoted = !dquoted;
		if (squoted == false && dquoted == false && *cur == '|')
		{
			if (!action)
				break ;
			cnt++;
		}
		if (!action)
			cnt++;
		cur++;
	}
	return (cnt);
}

static void	cutter_init(t_ctx *c)
{
	c->parser.pipes_n = pipe_count(c->entry, 1);
	c->parser.pipes = sf_calloc(c->parser.pipes_n + 1,
			sizeof(char *), PIPE_GB, &c->gbc);
	c->parser.pipes[0] = sf_calloc(pipe_count(c->entry, 0) + 1,
			sizeof(char), PIPE_GB, &c->gbc);
	if (PDEBUG == 1)
		printf("[0: %d]\n", pipe_count(c->entry, 0));
}

/*
	Coupe la string renvoyée par readline en tableau de strings,
	correspondant à chaque pipe.
	Si on trouve un pipe non quoté, on créé une nouvelle string
	de la taille donnée par pipe_count(0). Sinon, on continue d'ajouter
	des caractères au string du pipe courant.
*/
void	split_pipe(t_ctx *c)
{
	char	*cur;
	int		i;
	int		j;

	cur = c->entry;
	if (PDEBUG == 1)
		printf("{ nb pipes: %d }\n%d\n", pipe_count(cur, 1), pipe_count(cur, 0));
	cutter_init(c);
	i = 0;
	j = 0;
	while (*cur)
	{
		set_quote_bool(c, *cur);
		if (!is_curr_quoted(c) && *cur == '|')
		{
			cur++;
			c->parser.pipes[++i] = sf_calloc(pipe_count(cur, 0) + 1,
					sizeof(char *), PIPE_GB, &c->gbc);
			if (PDEBUG == 1)
				printf("[%d: %d]\n", i, pipe_count(cur, 0));
			j = 0;
		}
		if (*cur && !(!is_curr_quoted(c) && *cur == '|'))
			c->parser.pipes[i][j++] = *(cur++);
	}
}
