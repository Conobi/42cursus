/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 23:56:55 by abastos           #+#    #+#             */
/*   Updated: 2022/08/09 14:17:17 by conobi           ###   ########lyon.fr   */
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
	char	*home;

	if (!get_env_by_key(c->env, "HOME"))
		return ;
	home = get_env_by_key(c->env, "HOME")->value;
	c->history_fd = open(
			gb_add(ft_aconcat(2, home, "/.minishell_history"), &c->gbc, CMD_GB),
			O_CREAT | O_RDWR | O_APPEND, 0000644);
	if (c->history_fd < 0)
		return ;
	while (true)
	{
		entry = ft_gnl(c->history_fd);
		if (!entry)
			break ;
		c->last_entry = gb_add(ft_substr(entry, 0,
					ft_strlen(entry) - 1), &c->gbc, PERM_GB);
		new_entry = ft_substr(entry, 0, ft_strlen(entry) - 1);
		add_history(new_entry);
		free(new_entry);
		free(entry);
	}
	close(c->history_fd);
}

static void	history_write(t_ctx *c)
{
	if (write(c->history_fd, c->entry, ft_strlen(c->entry)) == -1)
	{
		create_error(c, (t_error){WARNING, "write",
			strerror(errno), false, errno, false});
	}
	if (write(c->history_fd, "\n", 1) == -1)
	{
		create_error(c, (t_error){WARNING, "write",
			strerror(errno), false, errno, false});
	}
}

/**
 * @brief This function is used to add a new entry to the history
 *
 * @param c Minishell context struct
 */
void	history(t_ctx *c)
{
	char	*home;
	t_env	*home_env;

	if (c->last_entry && ft_eq(c->last_entry, c->entry, 0))
		return ;
	add_history(c->entry);
	home_env = get_env_by_key(c->env, "HOME");
	if (!home_env)
		return ;
	home = home_env->value;
	c->history_fd = open(
			gb_add(ft_aconcat(2, home, "/.minishell_history"), &c->gbc, CMD_GB),
			O_CREAT | O_RDWR | O_APPEND, 0000644);
	if (c->history_fd < 0)
	{
		create_error(c, (t_error){WARNING, "open",
			strerror(errno), false, errno, false});
	}
	history_write(c);
	gb_delete(&c->gbc, HISTR_GB);
	c->last_entry = gb_add(ft_strdup(c->entry), &c->gbc, HISTR_GB);
	close(c->history_fd);
}
