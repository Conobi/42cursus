/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 01:51:22 by abastos           #+#    #+#             */
/*   Updated: 2022/05/20 03:09:36 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	termios_init(t_ctx *c)
{
	struct termios	term;
	t_error			err;

	if (tcgetattr(STDIN_FILENO, &term) != 0)
	{
		err.cmd = "tcgetattr";
		err.code = 1;
		err.message = "Unable to initialize terminal";
		err.type = ERROR;
		create_error(c, err);
	}
	else {
		term.c_lflag &= ~(ICANON | ECHOCTL);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
  	}
}