/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:57:24 by conobi            #+#    #+#             */
/*   Updated: 2021/11/03 15:36:29 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <libc.h>
#include "includes/libft.h"

int	main(int argc, char **argv)
{
	char	src[] = "Bonjour, comment ca va bg?";
	char	dest[] = "Trql et toi";
	char	src2[] = "Bonjour, comment ca va bg?";
	char	dest2[] = "Trql et toi";
	char	test1[] = "Je suis Miss Jirachi, coucou ^^! ";
	char	test2[] = "Heyyyy salut a tous";
	char	test1b[] = "Je suis Miss Jirachi, coucou ^^! ";
	char	test2b[] = "Heyyyy salut a tous";
	int		a;
	int		b;
	char	*s1;
	char	*s2;
	char	*x1;
	char	*x2;
	char	*j1;
	char	*j2;
	char	*str1;
	char	*str2;
	int		nb;
	int		ftnb;
	char	**strs;
	int		i;
	char	*strjoin;
	char	*itoa;

	s1 = "abcde";
	s2 = "ab ";
	x1 = "123";
	x2 = "123456";
	j1 = "abaa";
	j2 = "aaaaaaa";
	if (argc == 3)
	{
		printf("------------------------------------\n");
		printf("Taille du premier string : %zu\n", ft_strlen(argv[1]));
		printf("Taille du deuxième string : %zu\n", ft_strlen(argv[2]));
		printf("------------------------------------\n");
		printf("strlcpy : ");
		a = strlcpy(dest, src, 12);
		printf("%s\n%d", dest, a);
		printf("\nft_strlcpy : ");
		b = ft_strlcpy(dest2, src2, 12);
		printf("%s\n%d\n", dest2, b);
		printf("------------------------------------\n");
		printf("strlcat : ");
		a = strlcat(test1, test2, 34);
		printf("%s\n%d", test1, a);
		printf("\nft_strlcat : ");
		b = ft_strlcat(test1b, test2b, 34);
		printf("%s\n%d\n", test1b, b);
		printf("------------------------------------\n");
		printf("Sn = 3, Xn = 6, Jn = 4\n");
		printf("Résultats avec strncmp :\n");
		printf("s1: %s\ns2: %s\nValeur: %d\n", s1, s2, strncmp(s1, s2, 3));
		printf("s1: %s\ns2: %s\nValeur: %d\n", x1, x2, strncmp(x1, x2, 6));
		printf("s1: %s\ns2: %s\nValeur: %d\n", j1, j2, strncmp(j1, j2, 4));
		printf("\nRésultats avec ft_strncmp (ma belle fonction):\n");
		printf("s1: %s\ns2: %s\nValeur: %d\n", s1, s2, ft_strncmp(s1, s2, 3));
		printf("s1: %s\ns2: %s\nValeur: %d\n", x1, x2, ft_strncmp(x1, x2, 6));
		printf("s1: %s\ns2: %s\nValeur: %d\n", j1, j2, ft_strncmp(j1, j2, 4));
		printf("------------------------------------\n");
		str1 = strdup(argv[1]);
		str2 = ft_strdup(argv[1]);
		printf("strdup    : Adresse : %p\nVal. du pointeur : %s\n", &str1, str1);
		printf("ft_strdup : Adresse : %p\nVal. du pointeur : %s\n", &str2, str2);
		free(str1);
		free(str2);
		printf("------------------------------------\n");
		nb = atoi(argv[1]);
		ftnb = ft_atoi(argv[1]);
		printf("atoi: %d\n", nb);
		printf("ft_atoi: %d\n", ftnb);
		printf("------------------------------------\n");
		i = -1;
		printf("ft_split :\n");
		printf("string : %s, délimiteur : \"%c\"\nArray : ", argv[1], argv[2][0]);
		strs = ft_split(argv[1], argv[2][0]);
		while (strs[++i] != 0)
			printf("(%s) ", strs[i]);
		printf("\n------------------------------------\n");
		printf("Résultat attendu : ");
		printf("\n%s%s\n", argv[1], argv[2]);
		printf("\nft_strjoin : ");
		strjoin = ft_strjoin(argv[1], argv[2]);
		printf("\n%s\n", strjoin);
		free(strjoin);
		printf("------------------------------------\n");
		printf("Notre chiffre : %d\n", atoi(argv[1]));
		itoa = ft_itoa(atoi(argv[1]));
		printf("String d'itoa : %s\n", itoa);
		free(itoa);
		printf("------------------------------------\n");
	}
	else
		printf("File deux arguments chien\n");
	return (0);
}
/* 	Pour tester :
 *	gcc -Werror -Wall -Wextra -L . -lft main.c -o exec && ./exec salut bg
 */
/* printf("Comparaison arg1/arg2 : %d\n", ft_strcmp(argv[1], argv[2])); */
