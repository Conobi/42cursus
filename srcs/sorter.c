/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 16:01:00 by conobi            #+#    #+#             */
/*   Updated: 2021/12/17 19:56:08 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	chunk_sort(t_stack *stack_a, t_stack *stack_b, int d)
{
	int	n;
	int	r;
	int	stop;

	n = stack_a->size;
	r = n / d;
	stop = 0;
	while (r && r <= n && stack_a->size)
	{
		while (stop < r)
		{
			if (stack_a->arr[stack_a->size - 1] <= r)
			{
				stack_push(stack_a, stack_b, 'b');
				stop++;
			}
			else
				stack_rotate(stack_a, stack_b, 'a');
		}
		r += n / d;
	}
	while (r && stack_a->size)
		stack_push(stack_a, stack_b, 'b');
}

static short	top_or_bottom(t_stack stack, int max)
{
	int	mid;

	mid = (stack.size - 1) / 2;
	while (--stack.size >= 0)
		if (stack.arr[stack.size] == max && stack.size < mid)
			return (1);
	return (0);
}

static void	movsel_sort(t_stack *stack_a, t_stack *stack_b)
{
	int	n;

	n = stack_b->size;
	while (stack_a->size != n)
	{
		if (stack_b->arr[stack_b->size - 1] == stack_b->size - 1)
			stack_push(stack_a, stack_b, 'a');
		else if (top_or_bottom(*stack_b, stack_b->size - 1))
			while (stack_b->arr[stack_b->size - 1] != stack_b->size - 1)
				stack_revrotate(stack_a, stack_b, 'b');
		else
			while (stack_b->arr[stack_b->size - 1] != stack_b->size - 1)
				stack_rotate(stack_a, stack_b, 'b');
	}
}

void	stack_sort(t_stack *stack_a, t_stack *stack_b)
{
	chunk_sort(stack_a, stack_b, stack_a->size / (stack_a->size * 0.15));
	movsel_sort(stack_a, stack_b);
	// f_revintarr(stack_b->arr, stack_b->size);
	// if (top_or_bottom(*stack_b, stack_b->size - 1))
	// 	printf("Alors le gros tas est en haut\n");
	// else
	// 	printf("Alors le gros tas est en bas\n");
}
