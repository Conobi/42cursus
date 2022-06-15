/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remquote_pass.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:13:05 by conobi            #+#    #+#             */
/*   Updated: 2022/06/15 17:15:39 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_remquote {
	char	*ret;
	char	*var;
	int		tk_len;
	int		i;
	int		j;
}	t_remquote;

static char	*remquote(t_ctx *c, char *token)
{
	t_remquote	r;

	r = (t_remquote){0, 0, ft_strlen(token), -1, -1};
	reset_quote_bool(c);
	r.ret = gb_calloc(r.tk_len + 1, sizeof(char), CMD4P_GB, &c->gbc);
	while (token[++r.i])
	{
		set_quote_bool(c, token[r.i]);
		if (
			!((c->parser.dquoted != 1 && token[r.i] == '\'')
				|| (c->parser.squoted != 1 && token[r.i] == '"'))
		)
			r.ret[++r.j] = token[r.i];
	}
	return (r.ret);
}

void	remquote_pass(t_ctx *c)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < c->ncmds)
	{
		j = -1;
		while (++j < c->cmds[i].argc)
			c->cmds[i].argv[j] = remquote(c, c->cmds[i].argv[j]);
		j = -1;
		while (++j < c->cmds[i].redc)
			c->cmds[i].redirections[j].arg = remquote(c,
					c->cmds[i].redirections[j].arg);
	}
	gb_delete(&c->gbc, CMD3P_GB);
}
