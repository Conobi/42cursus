/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bipbop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:07:28 by conobi            #+#    #+#             */
/*   Updated: 2021/12/02 18:57:54 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void fuck(char **ntm)
{
	free((*ntm));
}

int	main(void)
{
	char	*wow;

	wow = NULL;
	fuck(&wow);
	fuck(&wow);
	fuck(&wow);
	fuck(&wow);
	fuck(&wow);

	// free(wow);
	// free(wow);
	// free(wow);
	// free(wow);
	printf("caca\n");
	return (0);
}
