/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eq.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 17:02:20 by conobi            #+#    #+#             */
/*   Updated: 2022/05/17 17:02:23 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	rtn_value(const char *a, const char *b, size_t len)
{
	if (ft_strncmp(a, b, len) == 0)
		return (1);
	else
		return (0);
}

int	ft_eq(const char *a, const char *b, char action)
{
	size_t	len_a;
	size_t	len_b;
	size_t	i;

	len_a = ft_strlen(a);
	len_b = ft_strlen(b);
	if (action == 0)
	{
		if (len_a > len_b)
			return (rtn_value(a, b, len_a));
		return (rtn_value(a, b, len_b));
	}
	if (action == 1)
		return (rtn_value(a, b, len_b));
	if (action == 2)
	{
		i = -1;
		while (++i < len_a - len_b)
			a++;
		return (rtn_value(a, b, len_b));
	}
	return (-1);
}
