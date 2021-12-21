/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 18:12:25 by conobi            #+#    #+#             */
/*   Updated: 2021/12/21 18:48:57 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	bubble_sort(int *tab, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size - 1)
	{
		j = -1;
		while (++j < size - i - 1)
			if (tab[j] > tab[j + 1])
				ft_swap(&tab[j], &tab[j + 1]);
		i++;
	}
}

void	stack_reducer(t_stack *src)
{
	t_stack	bubbled;
	t_stack	ret;
	int		i;
	int		j;

	bubbled = stack_cpy(*src);
	ret = stack_cpy(*src);
	bubble_sort(bubbled.arr, src->size);
	i = -1;
	while (++i < src->size)
	{
		j = -1;
		while (++j < src->size)
			if (bubbled.arr[i] == src->arr[j])
				ret.arr[j] = i;
	}
	free(bubbled.arr);
	free(src->arr);
	src->arr = ret.arr;
}
