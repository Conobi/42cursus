/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 20:05:37 by abastos           #+#    #+#             */
/*   Updated: 2022/05/18 13:14:29 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_branch(t_ctx *c)
{
	int		fd;
	char	*branch;
	char	*new_branch;

	fd = open(".git/HEAD", O_RDWR);
	if (fd < 0)
		return (NULL);
	branch = gb_add(ft_gnl(fd),
			&c->gbc, CMD_GB);
	new_branch = gb_add(ft_substr(branch, 16, ft_strlen(branch) - 17),
			&c->gbc, CMD_GB);
	close(fd);
	return (new_branch);
}
