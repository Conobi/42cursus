/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:54:41 by conobi            #+#    #+#             */
/*   Updated: 2021/12/03 17:13:52 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*gnl;

	fd = open("gnlTester/files/multiple_nlx5", O_RDONLY);
	while ((gnl = get_next_line(fd)))
	{
		if (gnl)
			printf("%s", gnl);
		free(gnl);
	}
	// gnl = get_next_line(fd);
	// printf("%s", gnl);
	// free(gnl);
	return (0);
}
