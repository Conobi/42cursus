/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 13:53:23 by conobi            #+#    #+#             */
/*   Updated: 2021/11/12 14:56:28 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	nlen;

	i = -1;
	nlen = ft_strlen(needle);
	if (!needle[0])
		return ((char *)haystack);
	while (++i <= len && haystack[i])
		if (haystack[i] == needle[0]
			&& ft_strncmp(haystack + i, needle, nlen) == 0
			&& i + nlen <= len)
			return ((char *)haystack + i);
	return (NULL);
}
