/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:10:41 by conobi            #+#    #+#             */
/*   Updated: 2022/05/19 20:31:09 by conobi           ###   ########lyon.fr   */
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

int		ft_is_space(char to_find, char *str)
{
	while (*str)
	{
		if (to_find == *str++)
			return (1);
	}
	return (0);
}

int		ft_wordcount(t_ctx *c, char *str, char *charset)
{
	int	count;
	int	flag;

	count = 0;
	flag = 1;
	while (*str)
	{
		set_quote_bool(c, *str);
		if (ft_is_space(*str, charset) && !is_curr_quoted(c))
			flag = 1;
		if (!ft_is_space(*str, charset) || (ft_is_space(*str, charset) && is_curr_quoted(c)))
		{
			if (flag)
				printf("<%c> -> %d\n", *str, ++count);
			flag = 0;
		}
		str++;
	}
	reset_quote_bool(c);
	return (count);
}

char	*create_word(char *str, int i, int j)
{
	char	*word;
	int		o;

	o = 0;
	if ((word = (char *)malloc(sizeof(char) * (j - i))) == ((void *)0))
		return ((void *)0);
	while (i < j)
	{
		word[o] = str[i];
		i++;
		o++;
	}
	word[o] = '\0';
	return (word);
}

char	**ft_charsplit(t_ctx *c, char *str, char *charset)
{
	char	**arr;
	int		index;
	int		j;
	int		i;
	int		words;

	i = 0;
	index = 0;
	words = ft_wordcount(c, str, charset);
	if (words)
	{
		arr = malloc(sizeof(char *) * (words + 1));
		if (!str || arr == ((void *)0))
			return ((void *)0);
		while (index < words)
		{
			while (ft_is_space(str[i], charset) && !is_curr_quoted(c) && str[i])
				set_quote_bool(c, str[++i]);
			j = i;
			while ((str[j]) && (!ft_is_space(str[j], charset) || (ft_is_space(*str, charset) && is_curr_quoted(c))))
				set_quote_bool(c, str[++j]);
			arr[index++] = create_word(str, i, j);
			i = j + 1;
		}
	}
	else
		arr = (char **)malloc(sizeof(char *));
	arr[index] = (void *)0;
	return (arr);
}

char **split_quote(t_ctx *c, char *str)
{
	reset_quote_bool(c);
	printf("-> %d <-\n", ft_wordcount(c, str, " \t\n\v\f\r"));
	split_viewer(ft_charsplit(c, str, " \t\n\v\f\r"));
	// c += 0;
	// printf("|>--- %s ---<|\n", str);
	return (0);
}
