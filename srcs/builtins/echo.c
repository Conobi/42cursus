/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 23:12:26 by abastos           #+#    #+#             */
/*   Updated: 2022/06/13 19:32:35 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function is a clone of echo command for builtins
 *
 * @param args Text to print, first args can be -n
 */
void	b_echo(const char *args)
{
	args += 5;
	if (ft_strncmp(args, "-n", 2) == 0)
	{
		args += 3;
		printf("%s", args);
	}
	else
		printf("%s\n", args);
}
