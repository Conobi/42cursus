/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:26:25 by conobi            #+#    #+#             */
/*   Updated: 2022/08/11 17:29:45 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_temp {
	char	*ret;
	char	*var;
	char	*kw;
	int		tk_len;
	int		start_kw;
	int		end_kw;
}	t_temp;

static char	*envvar_builder(t_ctx *c, char *token, t_temp *t)
{
	token[t->start_kw] = 0;
	t->kw = sf_calloc(t->end_kw - t->start_kw + 1,
			sizeof(char), CMD3P_GB, &c->gbc);
	ft_strlcpy(t->kw, token + t->start_kw + 1, t->end_kw - t->start_kw);
	if (get_env_by_key(c->env, t->kw))
		t->var = sf_add(ft_strdup(
					get_env_by_key(c->env, t->kw)->value),
				&c->gbc, CMD3P_GB);
	else
		t->var = sf_calloc(1, sizeof(char), CMD_GB, &c->gbc);
	t->ret = sf_add(ft_aconcat(3, token, t->var, token + t->end_kw),
			&c->gbc, CMD3P_GB);
	return (t->ret);
}

static char	*str_envvar(t_ctx *c, char *token)
{
	t_temp	t;

	t = (t_temp){0, 0, 0, ft_strlen(token), -1, -1};
	reset_quote_bool(c);
	while (token[++t.start_kw] && !(token[t.start_kw] == '$'
			&& (ft_isalnum(token[t.start_kw + 1])
				|| token[t.start_kw + 1] == '_')))
		set_quote_bool(c, token[t.start_kw]);
	t.end_kw = t.start_kw;
	while (
		token[t.start_kw] && token[++t.end_kw]
		&& (ft_isalnum(token[t.end_kw]) || token[t.end_kw] == '_'))
		;
	if (t.start_kw < t.tk_len - 1)
		return (envvar_builder(c, token, &t));
	return (sf_add(ft_strdup(token), &c->gbc, CMD_GB));
}

static char	*str_enverr(t_ctx *c, char *token)
{
	t_temp	t;

	t = (t_temp){0, 0, 0, ft_strlen(token), -1, -1};
	reset_quote_bool(c);
	while (token[++t.start_kw] && (!ft_eq(&token[t.start_kw], "$?", 1)))
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
	return (sf_add(ft_strdup(token), &c->gbc, CMD_GB));
}

static short	contains_env(const char *token, short type)
{
	int	i;

	i = -1;
	if (type)
	{
		while (token[++i] && token[i + 1])
		{
			if (token[i] == '$'
				&& (ft_isalnum(token[i + 1]) || token[i + 1] == '_'))
				return (1);
		}
	}
	else
	{
		while (token[++i] && token[i + 1])
		{
			if (token[i] == '$'
				&& token[i + 1] == '?')
				return (1);
		}
	}
	return (0);
}

char	*heredoc_env_replace(t_ctx *c, const char *str)
{
	char	*ret;

	ret = sf_add(ft_strdup(str), &c->gbc, CMD_GB);
	while (contains_env(ret, 1))
		ret = str_envvar(c, ret);
	while (contains_env(ret, 0))
		ret = str_enverr(c, ret);
	return (ret);
}
