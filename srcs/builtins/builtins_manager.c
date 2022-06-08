/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:27:31 by abastos           #+#    #+#             */
/*   Updated: 2022/05/24 15:49:20 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function is used to handle and execute if entry is a builtins
 *
 * @param c Minishell context struct
 * @return true if entry is a builtins
 * @return false if entry isnt a builtins
 */
bool	exec_builtin(t_ctx *c)
{
	if (ft_eq(c->entry, "exit", 1))
	{
		if (ft_strlen(c->entry) > 4)
			exit_shell(c, ft_atoi(c->entry + 5));
		else
			exit_shell(c, 0);
		return (true);
	}
	else if (ft_eq(c->entry, "cd", 1))
	{
		b_cd(c, c->entry);
		return (true);
	}
	else if (ft_eq(c->entry, "pwd", 1))
	{
		b_pwd(c);
		return (true);
	}
	// else if (ft_strncmp(c->entry, "echo", 4) == 0)
	// 	b_echo(c->entry);
	return (false);
}
