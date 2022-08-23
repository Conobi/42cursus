/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enverr_pass.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:19:06 by conobi            #+#    #+#             */
/*   Updated: 2022/08/23 18:15:42 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_temp {
	char	*ret;
	char	*var;
	int		tk_len;
	int		start_kw;
	int		end_kw;
}	t_temp;

static char	*str_enverr(t_ctx *c, char *token)
{
	t_temp	t;

	t = (t_temp){0, 0, ft_strlen(token), -1, -1};
	reset_quote_bool(c);
	while (token[++t.start_kw] && (!ft_eq(&token[t.start_kw], "$?", 1)
			|| c->parser.squoted == true))
		set_quote_bool(c, token[t.start_kw]);
	if (t.start_kw < t.tk_len)
	{
		t.end_kw = t.start_kw + 1;
		token[t.start_kw] = 0;
		t.var = sf_add(ft_itoa(g_return),
				&c->gbc, CMD2P_GB);
		t.ret = sf_add(ft_aconcat(3, token, t.var, token + t.end_kw + 1),
				&c->gbc, CMD2P_GB);
		return (t.ret);
	}
	return (sf_add(ft_strdup(token), &c->gbc, CMD2P_GB));
}

static short	contains_enverr(t_ctx *c, const char *token)
{
	int	i;

	i = -1;
	reset_quote_bool(c);
	while (token[++i] && token[i + 1])
	{
		set_quote_bool(c, token[i]);
		if (c->parser.squoted == true)
			continue ;
		if (token[i] == '$'
			&& token[i + 1] == '?')
			return (1);
	}
	return (0);
}

void	enverr_pass(t_ctx *c)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < c->ncmds)
	{
		j = -1;
		while (++j < c->cmds[i].argc)
			while (contains_enverr(c, c->cmds[i].argv[j]))
				c->cmds[i].argv[j] = str_enverr(c, c->cmds[i].argv[j]);
		j = -1;
		while (++j < c->cmds[i].redc)
			while (contains_enverr(c, c->cmds[i].redirections[j].arg))
				if (c->cmds[i].redirections[j].type != HRDC_TK)
					c->cmds[i].redirections[j].arg = str_enverr(c,
							c->cmds[i].redirections[j].arg);
	}
}
