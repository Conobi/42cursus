/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:50:27 by conobi            #+#    #+#             */
/*   Updated: 2021/12/15 16:20:48 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_stack	stack_a;
	t_stack	stack_b;
	int		i;

	printf("Input: \n");
	if (argc == 2)
		stack_a = split_parser(argv);
	else
		stack_a = parser(argc - 1, argv + 1);
	printf("Size: %d\n", stack_a.size);
	if (stack_a.size && is_arr_unique(stack_a.arr, stack_a.size))
	{
		stack_reducer(&stack_a);
		f_revintarr(stack_a.arr, stack_a.size);
		stack_b = stack_init(stack_a.size);
		printf("~~~~~~  AVANT  ~~~~~~\n");
		printf("------ stack_a ------\n");
		i = -1;
		while (++i < stack_a.size)
			printf("(%d) %d\n", i, stack_a.arr[i]);
		printf("------ stack_b ------\n");
		i = -1;
		while (++i < stack_b.size)
			printf("(%d) %d\n", i, stack_b.arr[i]);
		printf("~~~~~~ TRIAGE  ~~~~~~\n");
		stack_sort(&stack_a, &stack_b);
		printf("~~~~~~  APRÈS  ~~~~~~\n");
		printf("------ stack_a ------\n");
		i = -1;
		while (++i < stack_a.size)
			printf("(%d) %d\n", i, stack_a.arr[i]);
		printf("------ stack_b ------\n");
		i = -1;
		while (++i < stack_b.size)
			printf("(%d) %d\n", i, stack_b.arr[i]);
		free(stack_a.arr);
		free(stack_b.arr);
		return (0);
	}
	ft_putstr_fd("Error\n", 2);
	return (0);
}
