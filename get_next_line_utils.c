/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:51:46 by conobi            #+#    #+#             */
/*   Updated: 2021/12/02 20:13:17 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t	f_strlen(const char *s)
{
	int	i;

	i = 0;
	if (s)
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
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
	((unsigned char *)dst)[++i] = 0;
	return (dst);
}

void	f_strjoin(char **ret, char const *s1, char const *s2, int max)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = -1;
	if (s1 && *s1)
		tmp = malloc((f_strlen(s1) + f_strlen(s2) + 1) * sizeof(*ret));
	else if (s2 && *s2)
		tmp = malloc((f_strlen(s2) + 1) * sizeof(*ret));
	else
		return ;
	if (!tmp)
		return ;
	while (s1 && s1[++j])
		tmp[++i] = s1[j];
	j = -1;
	while (s2 && s2[++j] && j < max)
		tmp[++i] = s2[j];
	tmp[++i] = 0;
	if (s1 && s1[0])
		free((*ret));
	*ret = f_substr(tmp, 0, f_strlen(tmp));
	free(tmp);
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
		ret[i] = s[i];
	ret[i] = '\0';
	return (ret);
}

char	*f_strchr(const char *s, int c)
{
	int	len;
	int	i;

	i = -1;
	len = f_strlen(s);
	while (++i <= len && len != 0)
		if ((char)c == s[i])
			return ((char *)s + i);
	return (NULL);
}
