/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 23:12:26 by abastos           #+#    #+#             */
/*   Updated: 2022/08/03 21:23:32 by abastos          ###   ########lyon.fr   */
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
		if (cmd.argc < 3)
			return (0);
		while (ft_eq(cmd.argv[i], "-n", 0))
			i++;
		while (i < cmd.argc - 1)
			printf("%s ", cmd.argv[i++]);
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
