/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:29:07 by conobi            #+#    #+#             */
/*   Updated: 2021/11/05 13:49:31 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (((unsigned char *)s1)[i] == ((unsigned char *)s2)[i]
			&& ((unsigned char *)s1)[i] != '\0'
			&& ((unsigned char *)s2)[i] != '\0' && i < n - 1
			)
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
