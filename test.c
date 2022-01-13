/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:02:59 by conobi            #+#    #+#             */
/*   Updated: 2022/01/12 15:04:38 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <stdio.h>

int	main(void)
{
	long long int	clk;
	long int		ts;

	ts = 0;
	while (1)
	{
		clk = 0;
		while (clk <= CLOCKS_PER_SEC * 100000)
			clk++;
		ts++;
		printf("%ld secondes écoulées...\n", ts);
	}
	return (0);
}
