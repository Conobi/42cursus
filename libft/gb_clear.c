/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gb_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:37:21 by conobi            #+#    #+#             */
/*   Updated: 2022/04/26 19:10:15 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	gb_clear(t_garbc **garbcl)
{
	t_garbc	*prev;
	t_garbc	*curr;

	if (!garbcl || !*garbcl)
		return ;
	curr = *garbcl;
	while (curr)
	{
		prev = curr->next;
		free(curr->content);
		free(curr);
		curr = prev;
	}
	*garbcl = NULL;
}
