/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gb_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:44:30 by conobi            #+#    #+#             */
/*   Updated: 2022/04/26 19:07:57 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_garbc	*gb_init(void)
{
	t_garbc	*ret;

	ret = ft_calloc(1, sizeof(t_garbc));
	if (!ret)
		return (NULL);
	ret->content = NULL;
	ret->next = NULL;
	ret->type = -1;
	return (ret);
}
