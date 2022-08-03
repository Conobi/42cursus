/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:27:31 by abastos           #+#    #+#             */
/*   Updated: 2022/08/03 21:47:01 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(t_ncommand cmd)
{
	if (ft_eq(cmd.argv[0], "cd", 0))
		return (true);
	if (ft_eq(cmd.argv[0], "exit", 0))
		return (true);
	if (ft_eq(cmd.argv[0], "pwd", 0))
		return (true);
	if (ft_eq(cmd.argv[0], "echo", 0))
		return (true);
	if (ft_eq(cmd.argv[0], "export", 0))
		return (true);
	if (ft_eq(cmd.argv[0], "unset", 0))
		return (true);
	if (ft_eq(cmd.argv[0], "env", 0))
		return (true);
	return (false);
}

int	exec_builtin(t_ctx *c, t_ncommand cmd)
{
	if (ft_eq(cmd.argv[0], "cd", 0))
		return (b_cd(c, cmd.argv[1]));
	if (ft_eq(cmd.argv[0], "exit", 0))
		return (b_exit(c, cmd));
	if (ft_eq(cmd.argv[0], "pwd", 0))
		return (b_pwd(c));
	if (ft_eq(cmd.argv[0], "echo", 0))
		return (b_echo(cmd));
	if (ft_eq(cmd.argv[0], "export", 0))
		return (b_export(c, cmd.argc, cmd.argv));
	if (ft_eq(cmd.argv[0], "unset", 0))
		return (b_unset(c, cmd.argc, cmd.argv));
	if (ft_eq(cmd.argv[0], "env", 0))
		return (b_env(c, cmd.argc));
	return (1);
}
