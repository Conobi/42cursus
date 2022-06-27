/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:27:31 by abastos           #+#    #+#             */
/*   Updated: 2022/06/27 20:32:21 by conobi           ###   ########lyon.fr   */
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
	if (cmd.argc < 1)
		return (false);
	if (ft_eq(cmd.argv[0], "exit", 0))
	{
		if (cmd.argc > 0)
			exit_shell(c, ft_atoi(cmd.argv[1]));
		else
			exit_shell(c, 0);
		return (true);
	}
	if (ft_eq(cmd.argv[0], "cd", 0))
	{
		b_cd(c, cmd.argv[1]);
		return (true);
	}
	if (ft_eq(cmd.argv[0], "pwd", 0))
	{
		b_pwd(c);
		return (true);
	}
	if (ft_eq(cmd.argv[0], "echo", 0))
	{
		b_echo(cmd);
		return (true);
	}
	if (ft_eq(cmd.argv[0], "export", 0))
	{
		b_export(c, cmd.argc, cmd.argv);
		return (true);
	}
	if (ft_eq(cmd.argv[0], "env", 0))
	{
		b_env(c, cmd.argc, cmd.argv);
		return (true);
	}
	return (false);
}
