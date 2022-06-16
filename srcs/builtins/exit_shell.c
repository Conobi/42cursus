/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:06:17 by abastos           #+#    #+#             */
/*   Updated: 2022/06/16 19:02:59 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function is a clone of exit command for builtins
 *
 * @param c Minishell context struct
 * @param code Exit code
 */
void	exit_shell(t_ctx *c, int code)
{
	if (EDEBUG)
		printf("exit with code %d\n", code % 256); //debug
	close(c->history_fd);
	gb_clear(&c->gbc);
	exit(code); // % 256 code
}
