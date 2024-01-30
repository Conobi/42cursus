/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:43:12 by conobi            #+#    #+#             */
/*   Updated: 2022/08/11 19:39:44 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	identifier_err(t_ctx *c, char *token)
{
	char	*err;

	err = sf_add(
			ft_aconcat(
				3,
				"`",
				token,
				"': not a valid identifier"
				),
			&c->gbc,
			CMD_GB
			);
	create_error(c,
		(t_error){WARNING, SHELL_NAME, err, "export", 258, 0}
		);
	return (1);
}

static bool	not_identifier(char *str)
{
	int	i;

	i = -1;
	if (!(str[0] == '_' || ft_isalpha(str[0])))
		return (true);
	while (str[++i] && str[i] != '=')
		if (!(str[i] == '_' || ft_isalnum(str[i])))
			return (true);
	return (false);
}

void	set_list_entry(t_ctx *c, char *key,
		char *value, bool unset)
{
	t_env	*new;
	t_list	*new_list;

	new = get_env_by_key(c->env, key);
	new_list = get_env_list_by_key(c->env, key);
	if (!new)
		new = sf_calloc(1, sizeof(t_env), PERM_GB, &c->gbc);
	new->key = sf_add(ft_strdup(key), &c->gbc, PERM_GB);
	new->value = sf_add(ft_strdup(value), &c->gbc, PERM_GB);
	new->unset = unset;
	if (!new_list)
	{
		new_list = sf_add(ft_lstnew(new), &c->gbc, PERM_GB);
		ft_lstadd_front(&c->env, new_list);
	}
}

static void	split_env_keyval(t_ctx *c, char *str)
{
	char	*key;
	char	*value;
	int		i;
	int		j;

	key = sf_calloc(ft_strlen(str) + 1, sizeof(char), CMD_GB, &c->gbc);
	value = sf_calloc(ft_strlen(str) + 1, sizeof(char), CMD_GB, &c->gbc);
	i = -1;
	j = -1;
	while (str[++i] && str[i] != '=')
		key[++j] = str[i];
	j = -1;
	while (str[i] && str[++i])
		value[++j] = str[i];
	if (ft_strnstr(str, "=", ft_strlen(str)))
		i = 0;
	else
		i = 1;
	set_list_entry(c, key, value, i);
}

int	b_export(t_ctx *c, int argc, char **argv)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (argc == 1)
		export_print(c);
	while (++i < argc)
	{
		if (not_identifier(argv[i]))
			ret = identifier_err(c, argv[i]);
		if (c->ncmds == 1)
			split_env_keyval(c, argv[i]);
	}
	return (ret);
}
