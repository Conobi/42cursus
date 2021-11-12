/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 13:02:02 by conobi            #+#    #+#             */
/*   Updated: 2021/11/11 19:23:10 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*prev;
	t_list	*curr;

	if (!*lst)
		return ;
	curr = *lst;
	while (curr)
	{
		prev = curr->next;
		(*del)(curr->content);
		free(curr);
		curr = prev;
	}
	*lst = NULL;
}
