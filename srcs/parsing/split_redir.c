/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:16:53 by conobi            #+#    #+#             */
/*   Updated: 2022/06/03 13:44:24 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	split_viewer(char **arrstr)
{
	int	i;

	i = -1;
	printf("Liste des strings: \n");
	while (arrstr[++i])
		printf("{%d: %s}\n", i, arrstr[i]);
}

typedef struct s_split
{
	char	**new;
	int		i;
	int		j;
	int		k;
	int		l;
	int		tokens_nb;
}	t_split;

static int	is_redir(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

static void	redir_splitter(t_ctx *c, t_split *s, char **old)
{
	if (s->k)
		s->new[++s->j] = gb_calloc(3,
				sizeof(char), REDIR_GB, &c->gbc);
	s->new[s->j][0] = old[s->i][s->k];
	if (old[s->i][s->k + 1] == old[s->i][s->k])
		s->new[s->j][1] = old[s->i][++s->k];
	if (old[s->i][s->k + 1])
		s->new[++s->j] = gb_calloc(ft_strlen(old[s->i]) + 1,
				sizeof(char), REDIR_GB, &c->gbc);
	s->l = -1;
}

static char	**split_redir_2(t_ctx *c, char **old)
{
	t_split	s;

	s = (t_split){0, -1, -1, -1, -1, c->parser.len * 3};
	s.new = gb_calloc(s.tokens_nb, sizeof(void *), REDIR_GB, &c->gbc);
	while (old[++s.i])
	{
		s.k = -1;
		s.l = -1;
		reset_quote_bool(c);
		s.new[++s.j] = gb_calloc(ft_strlen(old[s.i]) + 1,
				sizeof(char), REDIR_GB, &c->gbc);
		while (old[s.i][++s.k] && ++s.l >= 0)
		{
			set_quote_bool(c, old[s.i][s.k]);
			if (is_redir(old[s.i][s.k]) && !is_curr_quoted(c))
				redir_splitter(c, &s, old);
			else
				s.new[s.j][s.l] = old[s.i][s.k];
		}
	}
	return (s.new);
}

char	**split_redir(t_ctx *c, char **split)
{
	char	**tamerelapute;

	reset_quote_bool(c);
	tamerelapute = split_redir_2(c, split);
	split_viewer(tamerelapute);
	return (tamerelapute);
}
