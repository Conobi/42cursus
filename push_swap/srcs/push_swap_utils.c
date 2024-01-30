/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:50:25 by conobi            #+#    #+#             */
/*   Updated: 2021/12/15 16:42:53 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	stack_nulled(void)
{
	t_stack	ret;

	ret.arr = 0;
	ret.size = 0;
	return (ret);
}

t_stack	stack_cpy(t_stack src)
{
	t_stack	ret;
	int		i;

	ret.size = src.size;
	ret.arr = ft_calloc(ret.size, sizeof(*ret.arr));
	if (!ret.arr)
		return (stack_nulled());
	i = -1;
	while (++i < ret.size)
		ret.arr[i] = src.arr[i];
	return (ret);
}

t_stack	stack_init(int size)
{
	t_stack	ret;

	ret.size = 0;
	ret.arr = ft_calloc(size, sizeof(*ret.arr));
	if (!ret.arr)
		return (stack_nulled());
	return (ret);
}

void	f_revintarr(int *arr, int size)
{
	int	tmp;
	int	i;
	int	j;

	i = size - 1;
	j = 0;
	tmp = 0;
	while (i >= j)
	{
		tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;
		i--;
		j++;
	}
}
