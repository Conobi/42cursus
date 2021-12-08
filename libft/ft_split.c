/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 18:52:48 by conobi            #+#    #+#             */
/*   Updated: 2021/11/12 15:50:40 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	f_len_arr(char const *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			len++;
		while (s[i] != c && s[i])
			i++;
	}
	return (len);
}

static int	f_len_str(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s == c)
		s++;
	while (*s != c && *s)
	{
		len++;
		s++;
	}
	return (len);
}

static void	f_init_it(int *i, int *j, int *k)
{
	*i = 0;
	*j = -1;
	*k = -1;
}

static char	**f_freeloop(char ***splited, int j)
{
	while (--j || j == 0)
		free(*splited[j]);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**splited;
	int		i;
	int		j;
	int		k;

	f_init_it(&i, &j, &k);
	if (!s)
		return (NULL);
	splited = malloc(sizeof(*splited) * (f_len_arr(s, c) + 1));
	if (!splited)
		return (NULL);
	while (++j < f_len_arr(s, c))
	{
		splited[j] = malloc(sizeof(**splited) * (f_len_str(s + i, c) + 1));
		if (!splited[j])
			return (f_freeloop(&splited, c));
		while (s[i] && s[i] == c)
			i++;
		k = -1;
		while (s[i] && s[i] != c)
			splited[j][++k] = s[i++];
		splited[j][++k] = 0;
	}
	splited[j] = 0;
	return (splited);
}
