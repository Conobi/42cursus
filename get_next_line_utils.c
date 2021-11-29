/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:51:46 by conobi            #+#    #+#             */
/*   Updated: 2021/11/19 18:54:17 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t	f_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*f_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = -1;
	if (!dst && !src)
		return (NULL);
	while (++i < n)
	{
		// printf("<%c>", ((unsigned char *)src)[i]);
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
	}
	((unsigned char *)dst)[++i] = 0;
	return (dst);
}

char	*f_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1 || !s2)
		return (NULL);
	ret = malloc((f_strlen(s1) + f_strlen(s2) + 1) * sizeof(*ret));
	if (!ret)
		return (NULL);
	while (s1[++j])
		ret[++i] = s1[j];
	j = -1;
	while (s2[++j])
		ret[++i] = s2[j];
	ret[++i] = 0;
	return (ret);
}

char	*f_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;

	i = -1;
	if (!s)
		return (NULL);
	ret = malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	s += start;
	while (++i < len && s[i])
	{
		ret[i] = s[i];
	}
	ret[i] = '\0';
	return (ret);
}

char	*f_strchr(const char *s, int c)
{
	int	len;
	int	i;

	i = -1;
	len = f_strlen(s);
	while (++i <= len)
		if ((char)c == s[i])
			return ((char *)s + i);
	return (NULL);
}
