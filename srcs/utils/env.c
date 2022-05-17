/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:20:12 by abastos           #+#    #+#             */
/*   Updated: 2022/05/18 01:31:28 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Check memory leaks here
 */

/**
 * @brief This function create a env object
 *
 * @param c Minishell context struct
 * @param entry Env variable to be initialized
 * @return t_list* return an new node contains an
 * env struct for env chained list
 */
t_list	*create_env_entry(t_ctx *c, char *entry)
{
	t_env	*new_env;
	t_list	*new_entry;
	int		i;

	i = 0;
	new_env = ft_calloc(1, sizeof(t_env));
	if (!new_env) // todo: if an error occurred exit shell with code 12 Cannot allocate memory
		return (NULL);
	while (entry[i] != '=')
		i++;
	new_env->key = gb_add(ft_substr(entry, 0, i), &c->gbc, PERM_GB);
	new_env->value = gb_add(ft_substr(entry, i + 1,
				ft_strlen(entry) - i - 1), &c->gbc, PERM_GB);
	if (!new_env->key || !new_env->value) // todo: if an error occurred exit shell with code 12 Cannot allocate memory
		return (NULL);
	new_entry = ft_lstnew(new_env);
	if (!new_entry)
		return (NULL);
	printf("new entry -> %s=%s\n", new_env->key, new_env->value);
	return (new_entry);
}

// todo: error with last env key fix
t_env	*get_env_by_key(t_list *head, char *key)
{
	t_list	*curr;
	t_env	*curr_env;

	curr = head;
	while (curr)
	{
		curr_env = (t_env *)curr->content;
		printf("-> %s\n", curr_env->key);
		if (ft_eq(curr_env->key, key, 0))
			return (curr_env);
		if (!curr->next)
			break;
		curr = curr->next;
	}
	printf("Not found: %s\n", key);
	return (NULL);
}

/**
 * @brief This function is used to initialize the
 * environment chained list for execution
 *
 * @param c Minishell context struct
 * @param env All env variables from parent process
 * @return t_list* This function returns the head of the list
 */
t_list	*create_env(t_ctx *c, char **env)
{
	t_list	*head;
	int		i;

	(void)c;
	head = gb_add(ft_lstnew(
		gb_add(create_env_entry(c, env[0]),
		&c->gbc, PERM_GB)),
		&c->gbc, PERM_GB);
	i = 0;
	while (env[++i])
		ft_lstadd_front(&head, gb_add(create_env_entry(c, env[i]), &c->gbc, PERM_GB));
	printf("%s\n", get_env_by_key(head, "fwefwefwfew")->value);
	return (NULL);
}