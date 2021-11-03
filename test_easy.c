/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_easy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:57:24 by conobi            #+#    #+#             */
/*   Updated: 2021/11/03 17:07:58 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ctype.h>
#include "includes/libft.h"

int	main(int argc, char **argv)
{
	char	c;

	if (argc == 2)
	{
		c = argv[1][0];
		printf("------------------------------------\n");
		printf("ft_isalpha: %d\n", ft_isalpha(c));
		printf("ft_isdigit: %d\n", ft_isdigit(c));
		printf("ft_isalnum: %d\n", ft_isalnum(c));
		printf("ft_isascii: %d\n", ft_isascii(c));
		printf("ft_isprint: %d\n", ft_isprint(c));
		printf("ft_toupper: %c\n", ft_toupper(c));
		printf("ft_tolower: %c\n", ft_tolower(c));
		printf("------------------------------------\n");
		printf("isalpha: %d\n", isalpha(c));
		printf("isdigit: %d\n", isdigit(c));
		printf("isalnum: %d\n", isalnum(c));
		printf("isascii: %d\n", isascii(c));
		printf("isprint: %d\n", isprint(c));
		printf("toupper: %c\n", toupper(c));
		printf("tolower: %c\n", tolower(c));
		printf("------------------------------------\n");
	}
	else
		printf("File un argument chien\n");
	return (0);
}
/* 	Pour tester :
 *	gcc -Werror -Wall -Wextra -L . -lft main.c -o exec && ./exec salut bg
 */
