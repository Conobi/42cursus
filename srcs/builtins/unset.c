/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:49:46 by conobi            #+#    #+#             */
/*   Updated: 2022/06/29 15:25:26 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	identifier_err(t_ctx *c, char *token)
{
	err_print(
		gb_add(
			ft_aconcat(
				4,
				SHELL_NAME,
				": unset: `",
				token,
				"': not a valid identifier\n"
				),
			&c->gbc,
			CMD_GB
			)
		);
	return (1);
}

static bool	not_identifier(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!(str[i] == '_' || ft_isalnum(str[i])))
			return (true);
	return (false);
}

static void	unset_env(t_ctx *c, char *key)
{
	t_list	*curr_list;
	t_list	*old_list;
	t_env	*curr_env;

	curr_list = c->env;
	while (curr_list->content)
	{
		curr_env = (t_env *)curr_list->content;
		if (ft_eq(curr_env->key, key, 0))
		{
			old_list->next = curr_list->next;
			free(curr_env->key);
			free(curr_env->value);
			curr_env->key = NULL;
			curr_env->value = NULL;
			curr_env->unset = NULL;
			free(curr_env);
			curr_env = NULL;
			curr_list = old_list;
		}
		old_list = curr_list;
		curr_list = curr_list->next;
	}
}

int	b_unset(t_ctx *c, int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (not_identifier(argv[i]))
			return (identifier_err(c, argv[i]));
		unset_env(c, argv[i]);
	}
	return (0);
}
