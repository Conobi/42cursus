/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:04:43 by conobi            #+#    #+#             */
/*   Updated: 2021/12/15 16:06:29 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef struct s_stack
{
	int	*arr;
	int	size;
}	t_stack;

/* push_swap_utils.c */
t_stack	stack_nulled(void);
t_stack	stack_cpy(t_stack src);
t_stack	stack_init(int size);
void	f_revintarr(int *arr, int size);

/* parser.c */
t_stack	parser(int cnt, char **arrstr);
t_stack	split_parser(char **argv);
short	is_arr_unique(int *arr, int size);

/* indexer.c */
void	bubble_sort(int *tab, int size);
void	stack_reducer(t_stack *src);

/* operations.c */
void	stack_swap(t_stack *stack_a, t_stack *stack_b, char oper);
void	stack_push(t_stack *stack_a, t_stack *stack_b, char oper);
void	stack_rotate(t_stack *stack_a, t_stack *stack_b, char oper);
void	stack_revrotate(t_stack *stack_a, t_stack *stack_b, char oper);

/* sorter.c */
void	stack_sort(t_stack *stack_a, t_stack *stack_b);

#endif
