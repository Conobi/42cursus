/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:06:17 by abastos           #+#    #+#             */
/*   Updated: 2022/05/18 13:10:04 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_ctx *c, int code)
{
	close(c->history_fd);
	gb_clear(&c->gbc);
	exit(code);
}
