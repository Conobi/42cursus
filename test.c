/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:57:24 by conobi            #+#    #+#             */
/*   Updated: 2021/11/12 15:46:48 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <libc.h>
#include "includes/libft.h"

char	f_tobob_mapi(unsigned int index, char c)
{
	if (index % 2)
	{
		if (c >= 'a' && c <= 'z')
			return (c - 32);
	}
	return (c);
}

int	main(void)
{
	char	*s;

	printf("------------------------------------\n");
	printf("A1\n");
	s = ft_strmapi("", f_tobob_mapi);
	printf("A2\n");
	printf("A8\n");
	free(s);
	printf("------------------------------------\n");
	return (0);
}
/* 	Pour tester :
 *	gcc -Werror -Wall -Wextra -L . -lft main.c -o exec && ./exec salut bg
 */
