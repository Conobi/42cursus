/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:57:24 by conobi            #+#    #+#             */
/*   Updated: 2021/11/03 19:05:50 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <libc.h>
#include "includes/libft.h"

int	main(int argc, char **argv)
{
	char	*strchr_s;
	char	*ft_strchr_s;

	if (argc == 3)
	{
		printf("------------------------------------\n");
		printf("Botte de foin : %s, aiguille : \"%c\"\n", argv[1], argv[2][0]);
		strchr_s = strchr(argv[1], argv[2][0]);
		printf("Pointeur strchr    : (%p) %s\n", strchr_s, strchr_s);
		ft_strchr_s = ft_strchr(argv[1], argv[2][0]);
		printf("Pointeur ft_strchr : (%p) %s\n", ft_strchr_s, ft_strchr_s);
		printf("------------------------------------\n");
	}
	else
		printf("File deux arguments chien\n");
	return (0);
}
/* 	Pour tester :
 *	gcc -Werror -Wall -Wextra -L . -lft main.c -o exec && ./exec salut bg
 */
