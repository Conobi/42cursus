/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 20:05:37 by abastos           #+#    #+#             */
/*   Updated: 2022/05/17 20:33:45 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_branch(t_ctx *c)
{
	int		fd;
	char	*branch;

	fd = open(".git/HEAD", O_RDWR);
	if (fd > 0)
	{
		branch = gb_add(ft_gnl(fd), &c->gbc, CMD_GB);
		return (branch + 16);
	}
	return (NULL);
}
