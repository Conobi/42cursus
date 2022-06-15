/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:27:31 by abastos           #+#    #+#             */
/*   Updated: 2022/06/15 17:54:10 by abastos          ###   ########lyon.fr   */
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
bool	exec_builtin(t_ctx *c, t_ncommand cmd)
{
	if (ft_eq(cmd.argv[0], "exit", 1))
	{
		if (cmd.argc > 0)
			exit_shell(c, ft_atoi(cmd.argv[1]));
		else
			exit_shell(c, 0);
		return (true);
	}
	if (ft_eq(cmd.argv[0], "cd", 1))
	{
		b_cd(c, cmd.argv[1]);
		return (true);
	}
	if (ft_eq(cmd.argv[0], "pwd", 1))
	{
		b_pwd(c);
		return (true);
	}
	if (ft_strncmp(cmd.argv[0], "echo", 4) == 0)
	{
		b_echo(cmd);
		return (true);
	}
	return (false);
}
