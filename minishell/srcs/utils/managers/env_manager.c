/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:20:12 by abastos           #+#    #+#             */
/*   Updated: 2022/08/12 15:14:13 by abastos          ###   ########lyon.fr   */
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
	new_env = sf_calloc(1, sizeof(t_env), PERM_GB, &c->gbc);
	if (!new_env)
		return (NULL);
	while (entry[i] != '=')
		i++;
	new_env->key = sf_add(ft_substr(entry, 0, i), &c->gbc, PERM_GB);
	new_env->value = sf_add(ft_substr(entry, i + 1,
				ft_strlen(entry) - i - 1), &c->gbc, PERM_GB);
	if (!new_env->key || !new_env->value)
		return (NULL);
	new_entry = sf_add(ft_lstnew(new_env), &c->gbc, PERM_GB);
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

char	**convert_env(t_ctx *c)
{
	t_list	*curr;
	t_env	*curr_env;
	char	**rtn;
	int		i;

	curr = c->env;
	i = 0;
	rtn = sf_calloc(ft_lstsize(c->env) + 1,
			sizeof(char *), CMD_GB, &c->gbc);
	while (curr && curr->next)
	{
		curr_env = (t_env *)curr->content;
		if (curr_env->key && curr_env->value && !curr_env->unset)
		{
			rtn[i] = sf_add(ft_aconcat(3, curr_env->key, "=", curr_env->value),
					&c->gbc, CMD_GB);
			i++;
		}
		curr = curr->next;
	}
	return (rtn);
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

	head = sf_calloc(1, sizeof(t_list), PERM_GB, &c->gbc);
	if (!head)
		return (NULL);
	head->content = NULL;
	head->next = NULL;
	i = -1;
	while (env[++i])
		ft_lstadd_front(&head, create_env_entry(c, env[i]));
	return (head);
}
