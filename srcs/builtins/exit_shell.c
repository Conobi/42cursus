/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:06:17 by abastos           #+#    #+#             */
/*   Updated: 2022/06/27 15:15:00 by abastos          ###   ########lyon.fr   */
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
	printf("exit\n");
	close(c->history_fd);
	gb_clear(&c->gbc);
	exit(code);
}
