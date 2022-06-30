/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remquote_pass.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:13:05 by conobi            #+#    #+#             */
/*   Updated: 2022/06/30 17:50:22 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_temp {
	char	*ret;
	char	*var;
	int		tk_len;
	int		i;
	int		j;
}	t_temp;

static char	*remquote(t_ctx *c, char *token)
{
	t_temp	t;

	t = (t_temp){0, 0, ft_strlen(token), -1, -1};
	reset_quote_bool(c);
	t.ret = gb_calloc(t.tk_len + 1, sizeof(char), CMD4P_GB, &c->gbc);
	while (token[++t.i])
	{
		set_quote_bool(c, token[t.i]);
		if (
			!((c->parser.dquoted != 1 && token[t.i] == '\'')
				|| (c->parser.squoted != 1 && token[t.i] == '"'))
		)
			t.ret[++t.j] = token[t.i];
	}
	return (t.ret);
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
