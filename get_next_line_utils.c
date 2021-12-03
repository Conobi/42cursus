/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:51:46 by conobi            #+#    #+#             */
/*   Updated: 2021/12/03 20:18:04 by conobi           ###   ########lyon.fr   */
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

void	f_strjoin(char **dest, char const *src, int max)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = -1;
	if (dest && *dest)
		tmp = malloc((f_strlen(*dest) + f_strlen(src) + 1) * sizeof(*dest));
	else if (src && *src)
		tmp = malloc((f_strlen(src) + 1) * sizeof(*dest));
	else
		return ;
	if (!tmp)
		return ;
	while (*dest && (*dest)[++j])
		tmp[++i] = (*dest)[j];
	j = -1;
	while (src && src[++j] && j < max)
		tmp[++i] = src[j];
	tmp[++i] = 0;
	free(*dest);
	*dest = f_strdup(tmp);
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

char	*f_strdup(const char *s)
{
	return (f_substr(s, 0, f_strlen(s)));
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
