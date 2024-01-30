/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:46:21 by conobi            #+#    #+#             */
/*   Updated: 2022/04/06 17:11:08 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	err_printer(int err)
{
	ft_putstr_fd("\e[91m\e[1m\e[4mError:\e[0m ", 2);
	ft_putstr_fd(strerror(err), 2);
	ft_putchar_fd('\n', 2);
}

void	info_printer(char *note)
{
	ft_putstr_fd("\e[96m\e[1m\e[4mInfo:\e[0m ", 2);
	ft_putstr_fd(note, 2);
	ft_putchar_fd('\n', 2);
}

void	err_ender(int err)
{
	err_printer(err);
	exit(1);
}

void	cli_parser(int argc, char **argv, t_context *con)
{
	if (argc == 4)
	{
		con->cox = ft_atof(argv[2]);
		con->coy = ft_atof(argv[3]);
	}
}

int	ender(void)
{
	info_printer("Exiting...\n");
	exit(0);
	return (0);
}
