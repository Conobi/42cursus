/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_gb_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:59:50 by abastos           #+#    #+#             */
/*   Updated: 2022/09/25 18:16:10 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fdgb_free(t_fdgbc **curr, t_fdgbc **prev, t_fdgbc **head)
{
	if (!*prev)
		*head = (*curr)->next;
	else
		(*prev)->next = (*curr)->next;
	close((*curr)->fd);
	free(*curr);
	*curr = NULL;
}

static int	fdgb_count(t_fdgbc **fdgbcl, const short type)
{
	t_fdgbc	*curr;
	int		i;

	curr = *fdgbcl;
	i = 0;
	while (curr->type != -1)
	{
		if (curr->type == type)
			i++;
		curr = curr->next;
	}
	return (i);
}

void	fdgb_close(t_fdgbc **fdgbcl, const short type)
{
	t_fdgbc	*head;
	t_fdgbc	*curr;
	t_fdgbc	*prev;

	curr = *fdgbcl;
	prev = NULL;
	head = curr;
	while (curr->type != -1)
	{
		if (curr->type == type)
			fdgb_free(&curr, &prev, &head);
		if (curr)
			prev = curr;
		if (curr && curr->next)
			curr = curr->next;
		else
			curr = head;
		if (fdgb_count(&head, type) > 1 && curr->next->type == -1)
			curr = head;
	}
	*fdgbcl = head;
}
