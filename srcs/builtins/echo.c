/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 23:12:26 by abastos           #+#    #+#             */
/*   Updated: 2022/06/22 17:59:10 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function is a clone of echo command for builtins
 *
 * @param args Text to print, first args can be -n
 */
void	b_echo(t_ncommand cmd)
{
	int	i;

	printf("exec echo cmd\n");
	if (ft_strncmp(cmd.argv[1], "-n", 2) == 0)
	{
		i = 1;
		while (++i < cmd.argc - 1)
			printf("%s ", cmd.argv[i]);
		printf("%s", cmd.argv[i]);
	}
	else
	{
		i = 0;
		while (++i < cmd.argc - 1)
			printf("%s ", cmd.argv[i]);
		printf("%s\n", cmd.argv[i]);
	}
	g_return = 0;
	exit(0);
}
