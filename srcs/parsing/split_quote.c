/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:10:41 by conobi            #+#    #+#             */
/*   Updated: 2022/06/16 19:57:09 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*create_word(t_ctx *c, const char *str, int i, int j)
{
	char	*word;
	int		o;

	o = 0;
	word = gb_calloc(sizeof(char), (j - i) + 1, QUOTE_GB, &c->gbc);
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

static void	split_quote_builder(t_ctx *c, char *str, t_split *s)
{
	while (is_space(str[s->i], " \t\n\v\f\r")
		&& !is_curr_quoted(c) && str[s->i])
		set_quote_bool(c, str[s->i++]);
	s->j = s->i;
	while (str[s->j] && (!is_space(str[s->j], " \t\n\v\f\r")
			|| (is_space(str[s->j], " \t\n\v\f\r") && is_curr_quoted(c))))
		set_quote_bool(c, str[s->j++]);
	s->arr[s->index++] = create_word(c, str, s->i, s->j);
}

char	**split_quote(t_ctx *c, char *str)
{
	t_split	s;

	s = (t_split){0, 0, 0, 0, wordcount(c, str, " \t\n\v\f\r")};
	reset_quote_bool(c);
	if (s.words && str)
	{
		s.arr = gb_calloc(sizeof(char *), (s.words + 1), QUOTE_GB, &c->gbc);
		while (str[s.i] && s.index < s.words)
		{
			split_quote_builder(c, str, &s);
			if (!str[s.j])
				break ;
			s.i = s.j + 1;
		}
	}
	else
		s.arr = gb_calloc(sizeof(char *), 1, QUOTE_GB, &c->gbc);
	gb_delete(&c->gbc, ENTRY_GB);
	return (s.arr);
}
