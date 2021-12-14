/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:04:43 by conobi            #+#    #+#             */
/*   Updated: 2021/12/14 16:27:10 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef struct s_stack
{
	int	*stack;
	int	size;
}	t_stack;

/* push_swap_utils.c */
t_stack	stack_nulled(void);
t_stack	stack_cpy(t_stack src);

/* parser.c */
t_stack	parser(int cnt, char **arrstr);
t_stack	split_parser(char **argv);
short	is_arr_unique(int *arr, int size);

/* indexer.c */
void	bubble_sort(int *tab, int size);
t_stack	stack_index(t_stack src);

#endif
