/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:43:12 by conobi            #+#    #+#             */
/*   Updated: 2022/06/24 20:09:54 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	multi_viewer(char **string, int cnt)
// {
// 	int	i;

// 	i = -1;
// 	printf("Liste des strings: \n");
// 	while (++i < cnt && string[i])
// 		printf("{%d: %s}\n", i, string[i]);
// }

static int	not_identifier(char *str)
{
	int	i;

	i = -1;
	if (!(str[0] == '_' || ft_isalpha(str[0])))
		return ((int)str[0]);
	while (str[++i] && str[i] != '=')
		if (!(str[i] == '_' || ft_isalnum(str[i])))
			return ((int)str[0]);
	return (-1);
}

static void	split_env_keyval(t_ctx *c, char *str)
{
	t_env	*env;
	t_list	*ret;
	int		i;
	int		j;

	env = gb_calloc(1, sizeof(t_env), PERM_GB, &c->gbc);
	env->key = gb_calloc(ft_strlen(str) + 1, sizeof(char), PERM_GB, &c->gbc);
	env->value = gb_calloc(ft_strlen(str) + 1, sizeof(char), PERM_GB, &c->gbc);
	i = -1;
	j = -1;
	while (str[++i] && str[i] != '=')
		env->key[++j] = str[i];
	j = -1;
	while (str[i] && str[++i])
		env->value[++j] = str[i];
	printf("\nkey:\n\t{%s}\nvalue:\n\t{%s}\n", env->key, env->value);
	ret = gb_add(ft_lstnew(&env), &c->gbc, PERM_GB);
	ft_lstadd_back(&c->env, ret);
}

typedef struct s_temp
{
	int		i;
	int		j;
}	t_temp;

int	b_export(t_ctx *c, int argc, char **argv)
{
	t_temp	t;

	t = (t_temp){0, -1};
	c += 0;
	if (argc == 1)
		export_print(c);
	while (++t.i < argc)
	{
		if (not_identifier(argv[t.i]) == -1)
			split_env_keyval(c, argv[t.i]);
		else
			printf("`%s` c'est pas un identifier valide\n", argv[t.i]);
	}
	// multi_viewer(argv + 1, argc - 1);
	return (0);
}
