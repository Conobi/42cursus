/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 23:12:26 by abastos           #+#    #+#             */
/*   Updated: 2022/09/26 19:36:30 by conobi           ###   ########lyon.fr   */
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
			printf("%s ", cmd.argv[i++]);
		printf("%s", cmd.argv[i]);
	}
}

/**
 * @brief This function is a clone of echo command for builtins
 *
 * @param args Text to print, first args can be -n
 */
int	b_echo(t_ncommand cmd)
{
	int	i;

	if (cmd.argc < 2)
	{
		printf("\n");
		return (0);
	}
	if (is_param(cmd.argv[1]))
		param_handler(cmd);
	else
	{
		i = 0;
		while (++i < cmd.argc - 1)
			printf("%s ", cmd.argv[i]);
		printf("%s\n", cmd.argv[i]);
	}
	return (0);
}
