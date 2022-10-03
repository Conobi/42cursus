/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 01:14:24 by conobi            #+#    #+#             */
/*   Updated: 2022/09/29 11:56:20 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	is_space(char to_find, char *str)
{
	while (*str)
	{
		if (to_find == *str++)
			return (1);
	}
	return (0);
}

static int	wordcount(char *str, char *charset)
{
	int	count;
	int	flag;

	count = 0;
	flag = 1;
	while (*str)
	{
		if (is_space(*str, charset))
			flag = 1;
		if (!is_space(*str, charset))
		{
			if (flag)
				count++;
			flag = 0;
		}
		str++;
	}
	return (count);
}

static char	*create_word(char *str, int i, int j)
{
	char	*word;
	int		o;

	o = 0;
	word = (char *)malloc(sizeof(char) * (j - i));
	if (!word)
		return (NULL);
	while (i < j)
	{
		word[o] = str[i];
		i++;
		o++;
	}
	word[o] = '\0';
	return (word);
}

static void	split_iterate(char *str, char *charset, int *i, int *j)
{
	while (is_space(str[*i], charset) && (str[*i]))
		*i += 1;
	*j = *i;
	while (!(is_space(str[*j], charset)) && (str[*j]))
		*j += 1;
}

char	**char_split(char *str, char *charset)
{
	char	**arr;
	int		index;
	int		j;
	int		i;
	int		words;

	words = wordcount(str, charset);
	index = 0;
	if (words)
	{
		arr = (char **)malloc(sizeof(char *) * (words + 1));
		if (!str || !arr)
			return (NULL);
		i = 0;
		while (index < words)
		{
			split_iterate(str, charset, &i, &j);
			arr[index++] = create_word(str, i, j);
			i = j + 1;
		}
	}
	else
		arr = malloc(sizeof(char *));
	arr[index] = NULL;
	return (arr);
}
