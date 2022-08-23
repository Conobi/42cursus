/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_pass.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:02:29 by conobi            #+#    #+#             */
/*   Updated: 2022/08/23 18:10:41 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_temp {
	char	*ret;
	char	*var;
}	t_temp;

static char	*str_tilde(t_ctx *c, char *token)
{
	t_temp	t;
	t_env	*home;

	t = (t_temp){0, 0};
	reset_quote_bool(c);
	if (
		token[0] == '~'
		&& (!token[1] || token[1] == '/')
	)
	{
		home = get_env_by_key(c->env, "HOME");
		t.var = "/";
		if (home)
			t.var = home->value;
		t.ret = sf_add(ft_aconcat(2, t.var, token + 1),
				&c->gbc, CMD3P_GB);
		return (t.ret);
	}
	return (sf_add(ft_strdup(token), &c->gbc, CMD3P_GB));
}

void	tilde_pass(t_ctx *c)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < c->ncmds)
	{
		j = -1;
		while (++j < c->cmds[i].argc)
			c->cmds[i].argv[j] = str_tilde(c, c->cmds[i].argv[j]);
		j = -1;
		while (++j < c->cmds[i].redc)
			c->cmds[i].redirections[j].arg = str_tilde(c,
					c->cmds[i].redirections[j].arg);
	}
	gb_delete(&c->gbc, CMD2P_GB);
}
