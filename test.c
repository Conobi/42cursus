/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:54:41 by conobi            #+#    #+#             */
/*   Updated: 2021/12/08 15:24:20 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fda;
	char	*gnl[2];
	int		fdb;

	fda = open("a", O_RDONLY);
	fdb = open("b", O_RDONLY);
	gnl[0] = get_next_line(fda);
	gnl[1] = get_next_line(fdb);
	while (gnl[0] && gnl[1])
	{
		printf("%s", gnl[0]);
		free(gnl[0]);
		printf("%s", gnl[1]);
		free(gnl[1]);
		gnl[0] = get_next_line(fda);
		gnl[1] = get_next_line(fdb);
	}
	return (0);
}
