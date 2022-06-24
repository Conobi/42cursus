/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:43:12 by conobi            #+#    #+#             */
/*   Updated: 2022/06/24 20:29:39 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_sort_int_tab(char **arr, int size)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 1;
		while (j < size - i - 1)
		{
			if (ft_strncmp(arr[j], arr[j + 1], ft_strlen(arr[j])) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

typedef struct s_temp {
	t_list	*curr;
	t_env	*curr_env;
	char	**print_list;
	int		i;
}	t_temp;

void	build_line(t_ctx *c, t_temp *t)
{
	t->curr_env = (t_env *)t->curr->content;
	if (t->curr_env->value)
		t->print_list[t->i] = gb_add(
				ft_aconcat(6, "declare -x ", t->curr_env->key, "=\"",
					t->curr_env->value, RESET, "\"\n"),
				&c->gbc, EXPT_PT_GB
				);
	else
		t->print_list[t->i] = gb_add(
				ft_aconcat(3, "declare -x ",
					t->curr_env->key, "=\"\"\n"), &c->gbc, EXPT_PT_GB);
	t->curr = t->curr->next;
	t->i++;
}

void	export_print(t_ctx *c)
{
	t_temp	t;

	t.curr = c->env;
	t.i = 0;
	t.print_list = gb_calloc(ft_lstsize(c->env) + 1,
			sizeof(char *), EXPT_PT_GB, &c->gbc);
	while (t.curr && t.curr->next)
		build_line(c, &t);
	ft_sort_int_tab(t.print_list, t.i);
	t.i = -1;
	while (t.print_list[++t.i])
		printf("%s", t.print_list[t.i]);
	gb_delete(&c->gbc, EXPT_PT_GB);
}
