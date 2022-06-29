/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enverr_pass.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:19:06 by conobi            #+#    #+#             */
/*   Updated: 2022/06/29 19:59:16 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_enverr {
	char	*ret;
	char	*var;
	int		tk_len;
	int		start_kw;
	int		end_kw;
}	t_enverr;

static char	*str_enverr(t_ctx *c, char *token)
{
	t_enverr	e;

	e = (t_enverr){0, 0, ft_strlen(token), -1, -1};
	reset_quote_bool(c);
	while (token[++e.start_kw] && (!ft_eq(&token[e.start_kw], "$?", 1)
			|| c->parser.squoted == 1))
		set_quote_bool(c, token[e.start_kw]);
	if (e.start_kw < e.tk_len)
	{
		e.end_kw = e.start_kw + 1;
		token[e.start_kw] = 0;
		e.var = gb_add(ft_itoa(WEXITSTATUS(g_return)),
				&c->gbc, CMD2P_GB);
		e.ret = gb_add(ft_aconcat(3, token, e.var, token + e.end_kw + 1),
				&c->gbc, CMD2P_GB);
		return (e.ret);
	}
	return (gb_add(ft_strdup(token), &c->gbc, CMD2P_GB));
}

static short	contains_enverr(t_ctx *c, const char *token)
{
	int	i;

	i = -1;
	reset_quote_bool(c);
	while (token[++i] && token[i + 1])
	{
		set_quote_bool(c, token[i]);
		if (c->parser.squoted == 1)
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
				c->cmds[i].redirections[j].arg = str_enverr(c,
						c->cmds[i].redirections[j].arg);
	}
}

// Dans la phrase qui contient un mot clé, on :
// tk_len = ft_strlen(token);
// - Tant que chr[start_kw] != \0
// - et que chr[start_kw] n'est pas un $ non quoté, ou un $ double quoté
// 	et que chr[start_kw + 1] est "a-Z 0-9 _", on continue
// - end_kw = start_kw - 1
// - Tant qu'on est "a-Z 0-9 _" on avance dans chr[++end_kw]
// - Si start_kw != end_kw :
//		kw = gb_calloc(end_kw - start_kw, sizeof(char), CMD3P_GB,&c->gbc);
//		ft_strlcpy(kw, token[start_kw + 1], end_kw - start_kw);
//		token[start_kw] = 0;
// 		ft_aconcat()
