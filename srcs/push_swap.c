/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:50:27 by conobi            #+#    #+#             */
/*   Updated: 2021/12/17 18:30:49 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

// static void	print_stack(t_stack stack)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (++i < stack.size)
// 	{
// 		ft_putchar_fd('(', 1);
// 		if (i < 10)
// 			ft_putchar_fd('0', 1);
// 		ft_putnbr_fd(i, 1);
// 		ft_putstr_fd(") ", 1);
// 		if (stack.arr[i] < 10)
// 			ft_putchar_fd('0', 1);
// 		ft_putnbr_fd(stack.arr[i], 1);
// 		ft_putstr_fd(" \e[32m", 1);
// 		j = stack.arr[i] + 1;
// 		while (--j)
// 			ft_putchar_fd('#', 1);
// 		ft_putstr_fd("\e[39m\n", 1);
// 	}
// }

int	main(int argc, char **argv)
{
	t_stack	stack_a;
	t_stack	stack_b;

	// printf("Input: \n");
	if (argc == 2)
		stack_a = split_parser(argv);
	else
		stack_a = parser(argc - 1, argv + 1);
	// printf("Size: %d\n", stack_a.size);
	if (stack_a.size && is_arr_unique(stack_a.arr, stack_a.size))
	{
		stack_reducer(&stack_a);
		f_revintarr(stack_a.arr, stack_a.size);
		stack_b = stack_init(stack_a.size);
		// printf("~~~~~~  AVANT  ~~~~~~\n");
		// printf("------ stack_a ------\n");
		// print_stack(stack_a);
		// printf("------ stack_b ------\n");
		// print_stack(stack_b);
		// printf("~~~~~~ TRIAGE  ~~~~~~\n");
		stack_sort(&stack_a, &stack_b);
		// printf("~~~~~~  APRÈS  ~~~~~~\n");
		// printf("------ stack_a ------\n");
		// print_stack(stack_a);
		// printf("------ stack_b ------\n");
		// print_stack(stack_b);
		free(stack_a.arr);
		free(stack_b.arr);
		return (0);
	}
	ft_putstr_fd("Error\n", 2);
	return (0);
}
