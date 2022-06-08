/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 23:56:55 by abastos           #+#    #+#             */
/*   Updated: 2022/05/20 16:55:34 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function is used to load .minishell_hystory file and
 * add his content to readline history
 *
 * @param c Minishell context struct
 */
void	init_history(t_ctx *c)
{
	char	*entry;
	char	*new_entry;

	while (true)
	{
		entry = ft_gnl(c->history_fd);
		if (!entry)
			break ;
		free(c->last_entry);
		c->last_entry = ft_substr(entry, 0, ft_strlen(entry) - 1);
		new_entry = ft_substr(entry, 0, ft_strlen(entry) - 1);
		add_history(new_entry);
		free(new_entry);
		free(entry);
	}
}

/**
 * @brief This function is used to add a new entry to the history
 *
 * @param c Minishell context struct
 */
void	history(t_ctx *c)
{
	if (c->last_entry && ft_eq(c->last_entry, c->entry, 0))
		return ;
	add_history(c->entry);
	write(c->history_fd, c->entry, ft_strlen(c->entry));
	write(c->history_fd, "\n", 1);
	free(c->last_entry);
	c->last_entry = ft_strdup(c->entry);
}
