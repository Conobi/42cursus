/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:10:41 by conobi            #+#    #+#             */
/*   Updated: 2022/06/30 18:09:33 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	in_charset(char to_find, char *str)
{
	while (*str)
		if (to_find == *str++)
			return (1);
	return (0);
}

static int	wordcount(t_ctx *c, char *str, char *charset)
{
	int	count;
	int	flag;

	count = 0;
	flag = 1;
	while (*str)
	{
		set_quote_bool(c, *str);
		if (in_charset(*str, charset) && !is_curr_quoted(c))
			flag = 1;
		if (
			!in_charset(*str, charset)
			|| (in_charset(*str, charset) && is_curr_quoted(c))
		)
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

static char	*create_word(t_ctx *c, const char *str, int i, int j)
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

typedef struct s_temp
{
	char	**arr;
	int		index;
	int		j;
	int		i;
	int		words;
}	t_temp;

static void	split_quote_builder(t_ctx *c, char *str, t_temp *t)
{
	while (
		in_charset(str[t->i], " \t\n\v\f\r")
		&& !is_curr_quoted(c)
		&& str[t->i]
	)
		set_quote_bool(c, str[t->i++]);
	t->j = t->i;
	while (
		str[t->j]
		&& (
			!in_charset(str[t->j], " \t\n\v\f\r")
			|| (in_charset(str[t->j], " \t\n\v\f\r") && is_curr_quoted(c))
		)
	)
		set_quote_bool(c, str[t->j++]);
	t->arr[t->index++] = create_word(c, str, t->i, t->j);
}

char	**split_quote(t_ctx *c, char *str)
{
	t_temp	t;

	t = (t_temp){0, 0, 0, 0, wordcount(c, str, " \t\n\v\f\r")};
	reset_quote_bool(c);
	if (t.words && str)
	{
		t.arr = gb_calloc(sizeof(char *), (t.words + 1), QUOTE_GB, &c->gbc);
		while (str[t.i] && t.index < t.words)
		{
			split_quote_builder(c, str, &t);
			if (!str[t.j])
				break ;
			t.i = t.j + 1;
		}
	}
	else
		t.arr = gb_calloc(sizeof(char *), 1, QUOTE_GB, &c->gbc);
	gb_delete(&c->gbc, ENTRY_GB);
	return (t.arr);
}
