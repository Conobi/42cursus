/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gb_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:33:33 by conobi            #+#    #+#             */
/*   Updated: 2022/08/01 15:38:38 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*gb_add(void *ptr, t_garbc **garbcl, const short type)
{
	t_garbc	*new;

	new = ft_calloc(1, sizeof(t_garbc));
	if (!new)
		return (NULL);
	new->content = ptr;
	new->type = type;
	new->next = *garbcl;
	*garbcl = new;
	return (new->content);
}
