/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:23:55 by conobi            #+#    #+#             */
/*   Updated: 2021/11/03 19:34:57 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	long int	i;
	size_t		len;

	len = ft_strlen(s);
	i = len;
	while (s[--i] && i >= 0)
		if (c == s[i])
			return ((char *)s + i);
	if (c == 0)
		return ((char *)s + len);
	return (NULL);
}

/*
	while (*s++ != c && *s)
		if (c != 0 && *s == 0)
			return (NULL);
	return (*s);
*/
