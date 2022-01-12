/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:46:21 by conobi            #+#    #+#             */
/*   Updated: 2022/01/12 00:05:09 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	err_printer(int err)
{
	ft_putstr_fd("\e[91m\e[1m\e[4mError:\e[0m ", 2);
	ft_putstr_fd(strerror(err), 2);
	ft_putchar_fd('\n', 2);
}

void	err_ender(int err)
{
	err_printer(err);
	exit(1);
}

int	ender(void)
{
	printf("Exiting...\n");
	exit(0);
	return (0);
}
