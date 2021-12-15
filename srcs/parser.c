/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:50:40 by conobi            #+#    #+#             */
/*   Updated: 2021/12/15 17:22:31 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static short	is_strdigitsign(char *str)
{
	int	i;

	i = -1;
	if (str[i + 1] == '-')
		i++;
	while (ft_isdigit(str[++i]))
	{
		if (str[i + 1] && !ft_isdigit(str[i + 1]))
			return (0);
	}
	if (i == 0)
		return (0);
	return (1);
}

t_stack	parser(int cnt, char **arrstr)
{
	t_stack	ret;

	ret.arr = ft_calloc(cnt, sizeof(int));
	if (!ret.arr)
		return (stack_nulled());
	ret.size = cnt;
	while (--cnt >= 0)
	{
		ret.arr[cnt] = ft_atoi(arrstr[cnt]);
		if (((ret.arr[cnt] == 0 || ret.arr[cnt] == -1)
				&& ft_strlen(arrstr[cnt]) > 2)
			|| !is_strdigitsign(arrstr[cnt]))
		{
			free(ret.arr);
			return (stack_nulled());
		}
	}
	return (ret);
}

t_stack	split_parser(char **argv)
{
	t_stack	ret;
	char	**splitted;
	int		cnt;

	cnt = 0;
	splitted = ft_split(argv[1], ' ');
	while (splitted[cnt])
		cnt++;
	ret = parser(cnt, splitted);
	while (--cnt >= 0)
		free(splitted[cnt]);
	free(splitted);
	return (ret);
}

short	is_arr_unique(int *arr, int size)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size)
	{
		j = i;
		while (++j < size)
			if (arr[i] == arr[j])
				return (0);
	}
	return (1);
}
