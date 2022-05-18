/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gb_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 12:51:59 by abastos           #+#    #+#             */
/*   Updated: 2022/05/18 12:58:49 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	f_len_arr(char const *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!s)
		return (1);
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

char	**gb_split(t_ctx *ctx, char const *s, char c)
{
	char	**splited;
	int		i;
	int		j;
	int		k;

	f_init_it(&i, &j, &k);
	splited = gb_calloc(sizeof(*splited), f_len_arr(s, c) + 1,
			CMD_GB, &ctx->gbc);
	if (!splited || !s)
		return (NULL);
	while (++j < f_len_arr(s, c))
	{
		splited[j] = gb_calloc(sizeof(**splited), f_len_str(s + i, c) + 1,
				CMD_GB, &ctx->gbc);
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
