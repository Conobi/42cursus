/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:50:27 by conobi            #+#    #+#             */
/*   Updated: 2021/12/14 16:46:47 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_stack	parsed;
	t_stack	indexed;
	int		i;

	printf("Input: \n");
	if (argc == 2)
		parsed = split_parser(argv);
	else
		parsed = parser(argc - 1, argv + 1);
	printf("Size: %d\n", parsed.size);
	i = -1;
	if (parsed.size && is_arr_unique(parsed.stack, parsed.size))
	{
		indexed = stack_index(parsed);
		while (++i < indexed.size)
		{
			printf("(%d) %d\n", i, indexed.stack[i]);
		}
		return (0);
	}
	ft_putstr_fd("Error\n", 2);
	return (0);
}
