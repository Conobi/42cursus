/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 13:02:02 by conobi            #+#    #+#             */
/*   Updated: 2021/11/12 18:41:09 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*prev;
	t_list	*curr;

	if (!lst || !*lst)
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
