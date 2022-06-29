/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 20:14:38 by conobi            #+#    #+#             */
/*   Updated: 2022/06/29 14:48:30 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	toomany_err(t_ctx *c)
{
	err_print(
		gb_add(
			ft_aconcat(
				4,
				SHELL_NAME,
				": env: ",
				strerror(7),
				"\n"
				),
			&c->gbc,
			CMD_GB
			)
		);
	return (7);
}

typedef struct s_temp {
	t_list	*curr;
	t_env	*curr_env;
	char	**print_list;
	int		i;
}	t_temp;

static void	build_line(t_ctx *c, t_temp *t)
{
	t->curr_env = (t_env *)t->curr->content;
	if (t->curr_env->key && t->curr_env->value && !t->curr_env->unset)
	{
		t->print_list[t->i] = gb_add(
				ft_aconcat(5, t->curr_env->key, "=\"",
					t->curr_env->value, RESET, "\"\n"),
				&c->gbc, EXPT_PT_GB
				);
		t->i++;
	}
	t->curr = t->curr->next;
}

int	b_env(t_ctx *c, int argc, char **argv)
{
	t_temp	t;

	argv += 0;
	if (argc != 1)
		return (toomany_err(c));
	t.curr = c->env;
	t.i = 0;
	t.print_list = gb_calloc(ft_lstsize(c->env) + 1,
			sizeof(char *), EXPT_PT_GB, &c->gbc);
	while (t.curr->content && t.curr->next->content)
		build_line(c, &t);
	t.i = -1;
	while (t.print_list[++t.i])
		printf("%s", t.print_list[t.i]);
	gb_delete(&c->gbc, EXPT_PT_GB);
	return (0);
}
