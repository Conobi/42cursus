/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar_pass.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:11:20 by conobi            #+#    #+#             */
/*   Updated: 2022/06/13 19:53:17 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_envvar {
	char	*ret;
	char	*var;
	char	*kw;
	int		tk_len;
	int		start_kw;
	int		end_kw;
}	t_envvar;

// static short	is_varword(char chr)
// {
// 	if (ft_isalnum(c) || c == '_')
// 		return (1);
// 	return (0);
// }

static short	is_envvar(const t_ctx *c, const char *token, const t_envvar e)
{
	if (c->parser.squoted == 1)
		return (0);
	if (token[e.start_kw] == '$'
		&& (ft_isalnum(token[e.start_kw + 1]) || token[e.start_kw + 1] == '_'))
		return (1);
	return (0);
}

// static short	contains_envvar(t_ctx *c, const char *token)
// {
// 	int	i;

// 	i = -1;
// 	reset_quote_bool(c);
// 	while (token[++i] && token[i + 1])
// 	{
// 		set_quote_bool(c, token[i]);
// 		if (c->parser.squoted == 1)
// 			continue ;
// 		if (token[i] == '$'
// 			&& (ft_isalnum(token[i + 1]) || token[i + 1] == '_'))
// 			return (1);
// 	}
// 	return (0);
// }

static char	*str_envvar(t_ctx *c, char *token)
{
	t_envvar	e;

	e = (t_envvar){0, 0, 0, ft_strlen(token), -1, -1};
	reset_quote_bool(c);
	while (token[++e.start_kw] && !is_envvar(c, token, e))
		set_quote_bool(c, token[e.start_kw]);
	e.end_kw = e.start_kw;
	while (
		token[e.start_kw] && token[++e.end_kw]
		&& (ft_isalnum(token[e.end_kw]) || token[e.end_kw] == '_'))
		;
	printf("@@@ %02d %02d %02d @@@\n", e.tk_len, e.start_kw, e.end_kw);
	if (e.start_kw < e.tk_len - 1)
	{
		token[e.start_kw] = 0;
		e.kw = gb_calloc(e.end_kw - e.start_kw + 1,
				sizeof(char), CMD3P_GB, &c->gbc);
		ft_strlcpy(e.kw, token + e.start_kw + 1, e.end_kw - e.start_kw);
		if (get_env_by_key(c->env, e.kw))
			e.var = gb_add(ft_strdup(
						get_env_by_key(c->env, e.kw)), &c->gbc, CMD3P_GB);
		else
			e.var = gb_calloc(1, sizeof(char), CMD3P_GB, &c->gbc);
		e.ret = gb_add(ft_aconcat(3, token, e.var, token + e.end_kw),
				&c->gbc, CMD2P_GB);
		return (e.ret);
	}
	return (gb_add(ft_strdup(token), &c->gbc, CMD3P_GB));
}

void	envvar_pass(t_ctx *c)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < c->ncmds)
	{
		j = -1;
		while (++j < c->cmds[i].argc)
			// while (contains_envvar(c, c->cmds[i].argv[j]))
			c->cmds[i].argv[j] = str_envvar(c, c->cmds[i].argv[j]);
		j = -1;
		while (++j < c->cmds[i].redc)
			// while (contains_envvar(c, c->cmds[i].redirections[j].arg))
			c->cmds[i].redirections[j].arg = str_envvar(c,
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
