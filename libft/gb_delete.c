/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gb_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:52:33 by conobi            #+#    #+#             */
/*   Updated: 2022/08/01 15:39:18 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	gb_free(t_garbc **curr, t_garbc **prev, t_garbc **head)
{
	if (!*prev)
		*head = (*curr)->next;
	else
		(*prev)->next = (*curr)->next;
	free((*curr)->content);
	free(*curr);
	*curr = NULL;
}

static int	gb_count(t_garbc **garbcl, const short type)
{
	t_garbc	*curr;
	int		i;

	curr = *garbcl;
	i = 0;
	while (curr->type != -1)
	{
		if (curr->type == type)
			i++;
		curr = curr->next;
	}
	return (i);
}

void	gb_delete(t_garbc **garbcl, const short type)
{
	t_garbc	*head;
	t_garbc	*curr;
	t_garbc	*prev;

	curr = *garbcl;
	prev = NULL;
	head = curr;
	while (curr->type != -1)
	{
		if (curr->type == type)
			gb_free(&curr, &prev, &head);
		if (curr)
			prev = curr;
		if (curr && curr->next)
			curr = curr->next;
		else
			curr = head;
		if (gb_count(&head, type) > 1 && curr->next->type == -1)
			curr = head;
	}
	*garbcl = head;
}
