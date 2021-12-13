/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:04:43 by conobi            #+#    #+#             */
/*   Updated: 2021/12/13 18:11:25 by conobi           ###   ########lyon.fr   */
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
t_stack	nulled_stack(void);

/* parser.c */
t_stack	parser(int cnt, char **arrstr);
t_stack	split_parser(char **argv);

#endif
