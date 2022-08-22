/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 01:51:22 by abastos           #+#    #+#             */
/*   Updated: 2022/08/22 16:07:49 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function is used to set termios mode for execution
 *
 * @param c Minishell context struct
 * @param mode 0 is to set main execution termios,
 * 1 is to set termios for fork execution
 */
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

/**
 * @brief This function is used to initialize the termios
 *
 * @param c Minishell context struct
 */
void	termios_init(t_ctx *c)
{
	if (tcgetattr(STDIN_FILENO, &c->base) < 0)
	{
		create_error(c, (t_error){ERROR, "tcgetattr",
			"Unable to initialize terminal", NULL, 1, false});
		return ;
	}
	c->term = c->base;
}
