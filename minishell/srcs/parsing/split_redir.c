/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:16:53 by conobi            #+#    #+#             */
/*   Updated: 2022/08/11 17:29:45 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* --- DEBUG PART --- */
static void	split_viewer(char **arrstr)
{
	int	i;

	i = -1;
	if (PDEBUG != 1)
		return ;
	printf("Liste des strings: \n");
	while (arrstr[++i])
		printf("{%d: %s}\n", i, arrstr[i]);
}

/* --- END DEBUG PART --- */

typedef struct s_temp
{
	char	**new;
	int		i;
	int		j;
	int		k;
	int		l;
	int		tokens_nb;
}	t_temp;

static int	is_redir(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

static void	redir_splitter(t_ctx *c, t_temp *t, char **old)
{
	if (t->k)
		t->new[++t->j] = sf_calloc(3,
				sizeof(char), REDIR_GB, &c->gbc);
	t->new[t->j][0] = old[t->i][t->k];
	if (old[t->i][t->k + 1] == old[t->i][t->k])
		t->new[t->j][1] = old[t->i][++t->k];
	if (old[t->i][t->k + 1])
		t->new[++t->j] = sf_calloc(ft_strlen(old[t->i]) + 1,
				sizeof(char), REDIR_GB, &c->gbc);
	t->l = -1;
}

char	**split_redir(t_ctx *c, char **old)
{
	t_temp	t;

	t = (t_temp){0, -1, -1, -1, -1, c->parser.len * 3};
	t.new = sf_calloc(t.tokens_nb + 1, sizeof(char *), REDIR_GB, &c->gbc);
	while (old[++t.i])
	{
		t.k = -1;
		t.l = -1;
		reset_quote_bool(c);
		t.new[++t.j] = sf_calloc(ft_strlen(old[t.i]) + 1,
				sizeof(char), REDIR_GB, &c->gbc);
		while (old[t.i][++t.k] && ++t.l >= 0)
		{
			set_quote_bool(c, old[t.i][t.k]);
			if (is_redir(old[t.i][t.k]) && !is_curr_quoted(c))
				redir_splitter(c, &t, old);
			else
				t.new[t.j][t.l] = old[t.i][t.k];
		}
	}
	split_viewer(t.new);
	gb_delete(&c->gbc, QUOTE_GB);
	return (t.new);
}
