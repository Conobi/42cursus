/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:50:25 by conobi            #+#    #+#             */
/*   Updated: 2021/12/14 16:42:25 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	stack_nulled(void)
{
	t_stack	ret;

	ret.stack = 0;
	ret.size = 0;
	return (ret);
}

t_stack	stack_cpy(t_stack src)
{
	t_stack	ret;
	int		i;

	ret.size = src.size;
	ret.stack = ft_calloc(ret.size, sizeof(*ret.stack));
	if (!ret.stack)
		return (stack_nulled());
	i = -1;
	while (++i < ret.size)
		ret.stack[i] = src.stack[i];
	return (ret);
}
