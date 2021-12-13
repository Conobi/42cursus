/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:50:27 by conobi            #+#    #+#             */
/*   Updated: 2021/12/13 18:07:12 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_stack	parsed;
	int		i;

	printf("Input: \n");
	if (argc == 2)
		parsed = split_parser(argv);
	else
		parsed = parser(argc - 1, argv + 1);
	printf("Size: %d\n", parsed.size);
	i = -1;
	if (parsed.size)
	{
		while (++i < parsed.size)
		{
			printf("%d\n", parsed.stack[i]);
		}
		return (0);
	}
	ft_putstr_fd("Error\n", 2);
	return (0);
}
