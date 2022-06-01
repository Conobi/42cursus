/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:10:41 by conobi            #+#    #+#             */
/*   Updated: 2022/06/01 20:02:00 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	split_viewer(char **arrstr)
{
	int	i;

	i = -1;
	printf("Liste des strings: \n");
	while (arrstr[++i])
		printf("{%d: %s}\n", i, arrstr[i]);
}

int	is_space(char to_find, char *str)
{
	while (*str)
		if (to_find == *str++)
			return (1);
	return (0);
}

int	wordcount(t_ctx *c, char *str, char *charset)
{
	int	count;
	int	flag;

	count = 0;
	flag = 1;
	while (*str)
	{
		set_quote_bool(c, *str);
		if (is_space(*str, charset) && !is_curr_quoted(c))
			flag = 1;
		if (!is_space(*str, charset)
			|| (is_space(*str, charset) && is_curr_quoted(c)))
		{
			if (flag)
				++count;
			flag = 0;
		}
		str++;
	}
	reset_quote_bool(c);
	return (count);
}

char	*create_word(const char *str, int i, int j)
{
	char	*word;
	int		o;

	o = 0;
	word = (char *)ft_calloc(sizeof(char), (j - i) + 1);
	if (word == ((void *)0))
		return ((void *)0);
	while (i < j)
	{
		word[o] = str[i];
		i++;
		o++;
	}
	return (word);
}

typedef struct s_split
{
	char	**arr;
	int		index;
	int		j;
	int		i;
	int		words;
}	t_split;

static char	**split_quote_2(t_ctx *c, char *str)
{
	t_split	s;

	s = (t_split){0, 0, 0, 0, wordcount(c, str, " \t\n\v\f\r")};
	reset_quote_bool(c);
	if (s.words && str)
	{
		s.arr = gb_calloc(sizeof(char *), (s.words + 1), QUOTE_GB, &c->gbc);
		while (str[s.i] && s.index < s.words)
		{
			while (is_space(str[s.i], " \t\n\v\f\r")
				&& !is_curr_quoted(c) && str[s.i])
				set_quote_bool(c, str[s.i++]);
			s.j = s.i;
			while (str[s.j] && (!is_space(str[s.j], " \t\n\v\f\r")
					|| (is_space(str[s.j], " \t\n\v\f\r") && is_curr_quoted(c))))
				set_quote_bool(c, str[s.j++]);
			s.arr[s.index++] = create_word(str, s.i, s.j);
			if (!str[s.j])
				break ;
			s.i = s.j + 1;
		}
	}
	else
		s.arr = ft_calloc(sizeof(char *), 1);
	return (s.arr);
}

char	**split_quote(t_ctx *c, char *str)
{
	char	**tamerelapute;

	reset_quote_bool(c);
	tamerelapute = split_quote_2(c, str);
	split_viewer(tamerelapute);
	return (tamerelapute);
}
