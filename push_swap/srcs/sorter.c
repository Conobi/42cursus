/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 16:01:00 by conobi            #+#    #+#             */
/*   Updated: 2021/12/21 18:31:28 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static short	top_or_bottom(t_stack stack, int max)
{
	int	mid;

	mid = (stack.size - 1) / 2;
	while (--stack.size >= 0)
		if (stack.arr[stack.size] == max && stack.size < mid)
			return (1);
	return (0);
}

static void	triple_sort(t_stack *stack)
{
	int	biggest;

	biggest = stack->size - 1;
	if (stack->arr[biggest] == biggest)
		stack_rotate(stack, stack, 'a');
	else if (biggest >= 2 && stack->arr[biggest - 1] == biggest)
		stack_revrotate(stack, stack, 'a');
	if (biggest >= 2 && stack->arr[biggest] == biggest - 1)
		stack_swap(stack, stack, 'a');
}

void	chunk_sort(t_stack *stack_a, t_stack *stack_b, int d)
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
				stack_push(stack_a, stack_b, 'b' + ++stop * 0);
			else if (stack_b->size > 2
				&& stack_b->arr[0] > stack_b->arr[stack_a->size - 1])
				stack_rotate(stack_a, stack_b, 'r');
			else
				stack_rotate(stack_a, stack_b, 'a');
		}
		r += n / d;
	}
	while (r && stack_a->size)
		stack_push(stack_a, stack_b, 'b');
}

void	movsel_sort(t_stack *stack_a, t_stack *stack_b)
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

void	minimal_sort(t_stack *stack_a, t_stack *stack_b)
{
	int	n;

	n = stack_a->size;
	if (n > 3)
	{
		while (stack_a->size > 3)
		{
			if (stack_a->arr[stack_a->size - 1] == stack_a->size - 1)
				stack_push(stack_a, stack_b, 'b');
			else if (top_or_bottom(*stack_a, stack_a->size - 1))
				while (stack_a->arr[stack_a->size - 1] != stack_a->size - 1)
					stack_revrotate(stack_a, stack_b, 'a');
			else
				while (stack_a->arr[stack_a->size - 1] != stack_a->size - 1)
					stack_rotate(stack_a, stack_b, 'a');
		}
		triple_sort(stack_a);
		while (stack_b->size)
		{
			stack_push(stack_a, stack_b, 'a');
			stack_rotate(stack_a, stack_b, 'a');
		}
	}
	else
		triple_sort(stack_a);
}
