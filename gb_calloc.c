/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gb_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:33:33 by conobi            #+#    #+#             */
/*   Updated: 2022/04/29 18:22:26 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*gb_calloc(size_t count, size_t size, const char type, t_garbc **last)
{
	t_garbc	*new;

	new = ft_calloc(1, sizeof(t_garbc));
	if (!new)
		return (NULL);
	new->content = ft_calloc(count, size);
	if (!new->content)
		return (NULL);
	new->type = type;
	new->next = *last;
	*last = new;
	return (new->content);
}
