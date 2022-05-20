/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 01:51:22 by abastos           #+#    #+#             */
/*   Updated: 2022/05/20 16:58:55 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	termios_set(t_ctx *c, short mode)
{
	if (mode == 0)
	{
		c->term.c_lflag &= ~(ICANON | ECHOCTL);
		tcsetattr(STDIN_FILENO, TCSANOW, &c->term);
		return ;
	}
	if (mode == 1)
	{
		c->base = c->term;
		c->base.c_lflag |= (ICANON | ECHOCTL);
		tcsetattr(STDIN_FILENO, TCSANOW, &c->base);
	}
}

void	termios_init(t_ctx *c)
{
	t_error			err;

	if (tcgetattr(STDIN_FILENO, &c->base) != 0)
	{
		err.cmd = "tcgetattr";
		err.code = 1;
		err.message = "Unable to initialize terminal";
		err.type = ERROR;
		create_error(c, err);
		return ;
	}
	c->term = c->base;
}
