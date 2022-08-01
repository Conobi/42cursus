/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar_pass.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:11:20 by conobi            #+#    #+#             */
/*   Updated: 2022/08/01 15:32:27 by conobi           ###   ########lyon.fr   */
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

static short	is_envvar(const t_ctx *c, const char *token, const t_temp t)
{
	if (c->parser.squoted == true)
		return (0);
	if (token[t.start_kw] == '$'
		&& (ft_isalnum(token[t.start_kw + 1]) || token[t.start_kw + 1] == '_'))
		return (1);
	return (0);
}

static char	*envvar_builder(t_ctx *c, char *token, t_temp *t)
{
	token[t->start_kw] = 0;
	t->kw = gb_calloc(t->end_kw - t->start_kw + 1,
			sizeof(char), CMD3P_GB, &c->gbc);
	ft_strlcpy(t->kw, token + t->start_kw + 1, t->end_kw - t->start_kw);
	if (get_env_by_key(c->env, t->kw))
		t->var = gb_add(ft_strdup(
					get_env_by_key(c->env, t->kw)->value),
				&c->gbc, CMD3P_GB);
	else
		t->var = gb_calloc(1, sizeof(char), CMD3P_GB, &c->gbc);
	t->ret = gb_add(ft_aconcat(3, token, t->var, token + t->end_kw),
			&c->gbc, CMD3P_GB);
	return (t->ret);
}

static char	*str_envvar(t_ctx *c, char *token)
{
	t_temp	t;

	t = (t_temp){0, 0, 0, ft_strlen(token), -1, -1};
	reset_quote_bool(c);
	while (token[++t.start_kw] && !is_envvar(c, token, t))
		set_quote_bool(c, token[t.start_kw]);
	t.end_kw = t.start_kw;
	while (
		token[t.start_kw] && token[++t.end_kw]
		&& (ft_isalnum(token[t.end_kw]) || token[t.end_kw] == '_'))
		;
	if (PDEBUG)
		printf("@@@ %02d %02d %02d @@@\n", t.tk_len, t.start_kw, t.end_kw);
	if (t.start_kw < t.tk_len - 1)
		return (envvar_builder(c, token, &t));
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
			c->cmds[i].argv[j] = str_envvar(c, c->cmds[i].argv[j]);
		j = -1;
		while (++j < c->cmds[i].redc)
			c->cmds[i].redirections[j].arg = str_envvar(c,
					c->cmds[i].redirections[j].arg);
	}
	gb_delete(&c->gbc, CMD2P_GB);
}
