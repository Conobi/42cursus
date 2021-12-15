/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 16:01:00 by conobi            #+#    #+#             */
/*   Updated: 2021/12/15 20:04:09 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"



void	stack_sort(t_stack *stack_a, t_stack *stack_b)
{
	stack_push(stack_a, stack_b, 'b');
	stack_push(stack_a, stack_b, 'b');
	stack_push(stack_a, stack_b, 'b');
	stack_swap(stack_a, stack_b, 's');
	// stack_push(stack_a, stack_b, 'a');
	// stack_push(stack_a, stack_b, 'a');
	// stack_push(stack_a, stack_b, 'a');
	// stack_revrotate(stack_a, stack_b, 'r');
	// stack_revrotate(stack_a, stack_b, 'r');
}
