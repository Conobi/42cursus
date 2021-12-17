/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:50:10 by conobi            #+#    #+#             */
/*   Updated: 2021/12/17 17:42:41 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	stack_swap(t_stack *stack_a, t_stack *stack_b, char oper)
{
	if (oper == 'a')
		ft_swap(&stack_a->arr[stack_a->size - 1],
			&stack_a->arr[stack_a->size - 2]);
	else if (oper == 'b')
		ft_swap(&stack_b->arr[stack_b->size - 1],
			&stack_b->arr[stack_b->size - 2]);
	else if (oper == 's')
	{
		ft_swap(&stack_a->arr[stack_a->size - 1],
			&stack_a->arr[stack_a->size - 2]);
		ft_swap(&stack_b->arr[stack_b->size - 1],
			&stack_b->arr[stack_b->size - 2]);
	}
	if (oper == 'a' || oper == 'b' || oper == 's')
	{
		ft_putchar_fd('s', 1);
		ft_putchar_fd(oper, 1);
		ft_putchar_fd('\n', 1);
	}
}

void	stack_push(t_stack *stack_a, t_stack *stack_b, char oper)
{
	if (oper == 'a' && stack_b->size)
	{
		stack_a->size += 1;
		stack_a->arr[stack_a->size - 1] = stack_b->arr[stack_b->size - 1];
		stack_b->size -= 1;
		ft_putstr_fd("pa\n", 1);
	}
	else if (oper == 'b' && stack_a->size)
	{
		stack_b->size += 1;
		stack_b->arr[stack_b->size - 1] = stack_a->arr[stack_a->size - 1];
		stack_a->size -= 1;
		ft_putstr_fd("pb\n", 1);
	}
}

void	stack_rotate(t_stack *stack_a, t_stack *stack_b, char oper)
{
	t_stack	stack;
	int		i;

	if (!(oper == 'a' || oper == 'b' || oper == 'r'))
		return ;
	if (oper == 'a' || oper == 'r')
		stack = *stack_a;
	else if (oper == 'b')
		stack = *stack_b;
	i = stack.size;
	while (--i > 0)
		ft_swap(&stack.arr[i], &stack.arr[i - 1]);
	if (oper == 'r')
	{
		i = stack_b->size;
		while (--i > 0)
			ft_swap(&stack_b->arr[i], &stack_b->arr[i - 1]);
	}
	ft_putchar_fd('r', 1);
	ft_putchar_fd(oper, 1);
	ft_putchar_fd('\n', 1);
}

void	stack_revrotate(t_stack *stack_a, t_stack *stack_b, char oper)
{
	t_stack	stack;
	int		i;

	if (oper == 'a')
		stack = *stack_a;
	else if (oper == 'b')
		stack = *stack_b;
	i = -1;
	while (++i < stack.size - 1)
		ft_swap(&stack.arr[i], &stack.arr[i + 1]);
	if (oper == 'r')
	{
		i = -1;
		while (++i < stack_b->size - 1)
			ft_swap(&stack_b->arr[i], &stack_b->arr[i + 1]);
	}
	ft_putstr_fd("rr", 1);
	ft_putchar_fd(oper, 1);
	ft_putchar_fd('\n', 1);
}
