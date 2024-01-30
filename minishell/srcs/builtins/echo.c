/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 23:12:26 by abastos           #+#    #+#             */
/*   Updated: 2022/09/28 18:30:02 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_param(char *param)
{
	int	i;

	i = 1;
	if (ft_eq(param, "-n", 1))
	{
		while (param[i])
		{
			if (param[i] != 'n')
				return (false);
			i++;
		}
	}
	else
		return (false);
	return (true);
}

static void	param_handler(t_ncommand cmd)
{
	int	i;

	i = 1;
	while (i != cmd.argc && is_param(cmd.argv[i]))
		i++;
	if (i != cmd.argc)
	{
		while (i < cmd.argc - 1)
		{
			ft_putstr_fd(cmd.argv[i++], 1);
			ft_putchar_fd(' ', 1);
		}
		ft_putstr_fd(cmd.argv[i], 1);
	}
}

/**
 * @brief This function is a clone of echo command for builtins
 *
 * @param cmd Command struct
 */
int	b_echo(t_ncommand cmd)
{
	int	i;

	if (cmd.argc < 2)
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	if (is_param(cmd.argv[1]))
		param_handler(cmd);
	else
	{
		i = 0;
		while (++i < cmd.argc - 1)
		{
			ft_putstr_fd(cmd.argv[i], 1);
			ft_putchar_fd(' ', 1);
		}
		ft_putstr_fd(cmd.argv[i], 1);
		ft_putchar_fd('\n', 1);
	}
	return (0);
}
