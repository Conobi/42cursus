/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:50:27 by conobi            #+#    #+#             */
/*   Updated: 2021/12/21 18:47:57 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	stack_sort(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_a->size >= 500)
	{
		chunk_sort(stack_a, stack_b, stack_a->size / (stack_a->size * 0.075));
		movsel_sort(stack_a, stack_b);
	}
	else if (stack_a->size >= 100)
	{
		chunk_sort(stack_a, stack_b, stack_a->size / (stack_a->size * 0.15));
		movsel_sort(stack_a, stack_b);
	}
	else if (stack_a->size <= 5)
		minimal_sort(stack_a, stack_b);
	else
	{
		chunk_sort(stack_a, stack_b, stack_a->size);
		movsel_sort(stack_a, stack_b);
	}
}

int	main(int argc, char **argv)
{
	t_stack	stack_a;
	t_stack	stack_b;

	if (argc == 2)
		stack_a = split_parser(argv);
	else
		stack_a = parser(argc - 1, argv + 1);
	if (stack_a.size && is_arr_unique(stack_a.arr, stack_a.size))
	{
		stack_reducer(&stack_a);
		f_revintarr(stack_a.arr, stack_a.size);
		stack_b = stack_init(stack_a.size);
		stack_sort(&stack_a, &stack_b);
		free(stack_a.arr);
		free(stack_b.arr);
		return (0);
	}
	ft_putstr_fd("Error\n", 2);
	return (0);
}
