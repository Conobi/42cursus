/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:49:48 by conobi            #+#    #+#             */
/*   Updated: 2021/11/07 12:39:56 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_charset(char a, char const *set)
{
	int	i;

	i = -1;
	while (set[++i])
		if (a == set[i])
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	size_t	len;
	size_t	start;

	len = ft_strlen(s1) - 1;
	start = 0;
	while (in_charset(s1[start], set))
		start++;
	while (in_charset(s1[len], set))
		len--;
	ret = ft_substr(s1, start, len - start + 1);
	return (ret);
}
