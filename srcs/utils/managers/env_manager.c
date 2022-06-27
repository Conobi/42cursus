/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:20:12 by abastos           #+#    #+#             */
/*   Updated: 2022/06/27 19:19:09 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	new_env = gb_calloc(1, sizeof(t_env), PERM_GB, &c->gbc);
	if (!new_env) // todo: if an error occurred exit shell with code 12 Cannot allocate memory
		return (NULL);
	while (entry[i] != '=')
		i++;
	new_env->key = gb_add(ft_substr(entry, 0, i), &c->gbc, PERM_GB);
	new_env->value = gb_add(ft_substr(entry, i + 1,
				ft_strlen(entry) - i - 1), &c->gbc, PERM_GB);
	if (!new_env->key || !new_env->value) // todo: if an error occurred exit shell with code 12 Cannot allocate memory
		return (NULL);
	new_entry = gb_add(ft_lstnew(new_env), &c->gbc, PERM_GB);
	if (!new_entry)
		return (NULL);
	return (new_entry);
}

/**
 * @brief This function is used to get the env object by key
 *
 * @param head Head of the environment variable list
 * @param key Key to search
 * @return t_env * Returns env struct for the given key, NULL if not found
 */
t_env	*get_env_by_key(t_list *head, char *key)
{
	t_list	*curr;
	t_env	*curr_env;

	curr = head;
	while (curr->next)
	{
		curr_env = (t_env *)curr->content;
		if (ft_eq(curr_env->key, key, 0))
			return (curr_env);
		curr = curr->next;
	}
	return (NULL);
}

/**
 * @brief This function is used to get the env object by key
 *
 * @param head Head of the environment variable list
 * @param key Key to search
 * @return t_env * Returns env struct for the given key, NULL if not found
 */
t_list	*get_env_list_by_key(t_list *head, char *key)
{
	t_list	*curr;
	t_env	*curr_env;

	curr = head;
	while (curr->next)
	{
		curr_env = (t_env *)curr->content;
		if (ft_eq(curr_env->key, key, 0))
			return (curr);
		curr = curr->next;
	}
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

	head = gb_calloc(1, sizeof(t_list), PERM_GB, &c->gbc);
	if (!head) // todo: if an error occurred exit shell with code 12 Cannot allocate memory
		return (NULL);
	head->content = NULL;
	head->next = NULL;
	i = -1;
	while (env[++i])
		ft_lstadd_front(&head, create_env_entry(c, env[i]));
	return (head);
}
