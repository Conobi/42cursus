/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:37:16 by conobi            #+#    #+#             */
/*   Updated: 2022/05/11 15:33:36 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Si action == 1, on compte le nombre de pipes,
// sinon on compte le nombre de caractères jusqu'au prochain pipe
static int pipe_count(char *curr, char action)
{
	int		cnt;
	char	squoted;
	char	dquoted;
	char	*cur;

	cur = curr;
	cnt = action;
	squoted = -1;
	dquoted = -1;
	while (*cur)
	{
		if (!action)
			cnt++;
		if (*cur == '\'' && dquoted == -1)
			squoted *= -1;
		if (*cur == '"' && squoted == -1)
			dquoted *= -1;
		else if (squoted == -1 && dquoted == -1 && *cur == '|')
		{
			if (!action)
				break ;
			cnt++;
		}
		cur++;
		// Gestion d'erreur des quotes (non obligatoire)
	}
	return (cnt);
}

static void	pipe_viewer(char **pipes, int cnt)
{
	int	i;

	i = -1;
	printf("Liste des pipes: \n");
	while (++i < cnt && pipes[i])
		printf("{%d: \"%s\"}\n", i, pipes[i]);
}

// Tant qu'on a pas fini le string, on split à chaque pipe
void pipe_cutter(t_ctx *c)
{
	char	*cur;
	char	**pipes;
	int		i;
	int		j;
	int		nb_pipes;

	cur = c->entry;
	printf("{ nb pipes: %d }\n", pipe_count(cur, 1));
	nb_pipes = pipe_count(cur, 1);
	pipes = gb_calloc(nb_pipes, sizeof(char **), PIPE_GB, &c->gbc);
	pipes[0] = gb_calloc(pipe_count(cur, 0), sizeof(char *), PIPE_GB, &c->gbc);
 	printf("%d\n", pipe_count(cur, 0));
	i = 0;
	j = -1;
	while (*cur)
	{
		if (*cur == '\'' && c->parser.dquoted == -1)
			c->parser.squoted *= -1;
		if (*cur == '"' && c->parser.squoted == -1)
			c->parser.dquoted *= -1;
		else if (c->parser.squoted == -1 && c->parser.dquoted == -1 && *cur == '|')
		{
			cur++;
			pipes[++i] = gb_calloc(pipe_count(cur, 0) + 1, sizeof(char *), PIPE_GB, &c->gbc);
			printf("[%d: %d]\n", i, pipe_count(cur, 0));
			j = -1;
		}
		if (!(c->parser.squoted == -1 && c->parser.dquoted == -1 && *cur == '|'))
			pipes[i][++j] = *cur;
		else
			pipes[i][++j] = *cur * 0;
		if (*cur != '|')
			cur++;
		// Gestion d'erreur des quotes (non obligatoire)
	}
	pipe_viewer(pipes, nb_pipes);
}

