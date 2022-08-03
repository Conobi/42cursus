/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:06:17 by abastos           #+#    #+#             */
/*   Updated: 2022/08/03 22:40:51 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	valid_param(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}

int	b_exit(t_ctx *c, t_ncommand cmd)
{
	if (cmd.argc > 1)
	{
		if (!valid_param(cmd.argv[1]))
		{
			printf("exit\n");
			create_error(c, (t_error){WARNING, "exit",
				"numeric argument required", cmd.argv[1], 255, false});
			exit_shell(c, 255, true);
			return (255);
		}
		if (cmd.argc > 2)
		{
			printf("exit\n");
			create_error(c, (t_error){WARNING, "exit",
				"too many arguments", NULL, 1, false});
			return (1);
		}
		exit_shell(c, ft_atoi(cmd.argv[1]) % 256, true); // todo: check value, fix negative numbers and max int
	}
	else
		exit_shell(c, g_return, false);
	return (0);
}

/**
 * @brief This function is a clone of exit command for builtins
 *
 * @param c Minishell context struct
 * @param code Exit code
 * @param no_print Disable print statement
 */
void	exit_shell(t_ctx *c, int code, int no_print)
{
	if (!no_print)
		printf("exit\n");
	close(c->history_fd);
	gb_clear(&c->gbc);
	exit(code);
}
