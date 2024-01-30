/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_gb.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:59:50 by abastos           #+#    #+#             */
/*   Updated: 2022/09/26 19:25:27 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fdgbc	*fdgb_init(void)
{
	t_fdgbc	*new;

	new = ft_calloc(1, sizeof(t_fdgbc));
	if (!new)
		return (NULL);
	new->fd = -1;
	new->type = -1;
	new->next = NULL;
	return (new);
}

int	fdgb_add(int fd, t_fdgbc **fdgbcl, const short type)
{
	t_fdgbc	*new;

	if (fd < 0)
		return (fd);
	new = ft_calloc(1, sizeof(t_fdgbc));
	if (!new)
		return (-1);
	new->fd = fd;
	new->type = type;
	new->next = *fdgbcl;
	*fdgbcl = new;
	return (new->fd);
}

void	fdgb_close_all(t_fdgbc **fdgbcl)
{
	t_fdgbc	*prev;
	t_fdgbc	*curr;

	if (!fdgbcl || !*fdgbcl)
		return ;
	curr = *fdgbcl;
	while (curr)
	{
		prev = curr->next;
		if (curr->fd > 1)
			close(curr->fd);
		free(curr);
		curr = prev;
	}
	*fdgbcl = NULL;
}
