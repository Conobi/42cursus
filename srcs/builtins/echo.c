/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 23:12:26 by abastos           #+#    #+#             */
/*   Updated: 2022/08/09 14:58:46 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (ft_eq(cmd.argv[1], "-n", 0))
	{
		i = 1;
		while (i != cmd.argc && ft_eq(cmd.argv[i], "-n", 0))
			i++;
		while (i < cmd.argc - 1)
			printf("%s ", cmd.argv[i++]);
		if (i != cmd.argc)
			printf("%s", cmd.argv[i]);
	}
	else
	{
		i = 0;
		while (++i < cmd.argc - 1)
			printf("%s ", cmd.argv[i]);
		printf("%s\n", cmd.argv[i]);
	}
	return (0);
}
