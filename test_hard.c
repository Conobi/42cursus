/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_hard.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:06:41 by conobi            #+#    #+#             */
/*   Updated: 2021/11/06 13:44:31 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <libc.h>
#include "includes/libft.h"

int	main(int argc, char **argv)
{
	char	*strchr_s;
	char	*ft_strchr_s;
	char	*strrchr_s;
	char	*ft_strrchr_s;
	char	*memchr_s;
	char	*ft_memchr_s;
	int		memchr_n;
	int		memcmp_n;
	int		memcmp_i;
	int		ft_memcmp_i;
	char	*memset_s;
	char	*ft_memset_s;
	int		memset_i;
	char	memcpy_s[] = "Salut ca va?";
	char	ft_memcpy_s[] = "Salut ca va?";
	char	memcpy_s2[] = "Salut ca va?";
	char	ft_memcpy_s2[] = "Salut ca va?";
	char	memmove_s[] = "Salut ca va?";
	char	ft_memmove_s[] = "Salut ca va?";
	char	memmove_s2[] = "Salut ca va?";
	char	ft_memmove_s2[] = "Salut ca va?";

	if (argc == 3)
	{
		printf("------------------------------------\n");
		printf("Botte de foin : %s, aiguille : \"%c\"\n", argv[1], argv[2][0]);
		strchr_s = strchr(argv[1], argv[2][0]);
		printf("Pointeur strchr    (%p) : %s\n", strchr_s, strchr_s);
		ft_strchr_s = ft_strchr(argv[1], argv[2][0]);
		printf("Pointeur ft_strchr (%p) : %s\n", ft_strchr_s, ft_strchr_s);
		printf("------------------------------------\n");
		printf("Botte de foin : %s, aiguille : \"%c\"\n", argv[1], argv[2][0]);
		strrchr_s = strrchr(argv[1], argv[2][0]);
		printf("Pointeur strrchr    (%p) : %s\n", strrchr_s, strrchr_s);
		ft_strrchr_s = ft_strrchr(argv[1], argv[2][0]);
		printf("Pointeur ft_strrchr (%p) : %s\n", ft_strrchr_s, ft_strrchr_s);
		printf("------------------------------------\n");
		printf("Botte de foin : %s, aiguille : \"%c\"\n", argv[1], argv[2][0]);
		memchr_n = ft_strlen(argv[1]) + 1;
		memchr_s = memchr(argv[1], argv[2][0], memchr_n);
		printf("Pointeur memchr    (%p) : %s\n", memchr_s, memchr_s);
		ft_memchr_s = ft_memchr(argv[1], argv[2][0], memchr_n);
		printf("Pointeur ft_memchr (%p) : %s\n", ft_memchr_s, ft_memchr_s);
		printf("------------------------------------\n");
		memcmp_n = ft_strlen(argv[1]);
		printf("s1: \"%s\"\ns2: \"%s\"\nn : %d\n", argv[1], argv[2], memcmp_n);
		memcmp_i = memcmp(argv[1], argv[2], memcmp_n);
		printf("Valeur memcmp    : %d\n", memcmp_i);
		ft_memcmp_i = ft_memcmp(argv[1], argv[2], memcmp_n);
		printf("Valeur ft_memcmp : %d\n", ft_memcmp_i);
		printf("------------------------------------\n");
		memset_i = 42;
		ft_memset_s = malloc(sizeof(*ft_memset_s) * memset_i);
		memset_s = malloc(sizeof(*memset_s) * memset_i);
		if (!memset_s || !ft_memset_s)
			return (0);
		memset_s[memset_i - 1] = 0;
		ft_memset_s[memset_i - 1] = 0;
		printf("Av memset   : \"%s\"\nAv ft_memset: \"%s\"\n", memset_s, ft_memset_s);
		printf("Ret memset   : \"%s\"\n", memset(memset_s, 'a', memset_i - 1));
		printf("Ret ft_memset: \"%s\"\n",
			ft_memset(ft_memset_s, 'a', memset_i - 1));
		printf("Ap memset    : \"%s\"\nAp ft_memset : \"%s\"\n",
			memset_s, ft_memset_s);
		printf("------------------------------------\n");
		printf("Av bzero   : \"%s\"\nAv ft_bzero: \"%s\"\n", memset_s, ft_memset_s);
		bzero(memset_s, memset_i);
		ft_bzero(ft_memset_s, memset_i);
		printf("Ap bzero   : \"%s\"\nAp ft_bzero: \"%s\"\n", memset_s, ft_memset_s);
		free(memset_s);
		free(ft_memset_s);
		printf("------------------------------------\n");
		printf("Av memcpy    : \"%s\"\nAv ft_memcpy : \"%s\"\n", memcpy_s, ft_memcpy_s);
		printf("Ret memcpy    : \"%s\"\n", memcpy(memcpy_s, "Salut a tous c'est Fanta", 6));
		printf("Ret ft_memcpy: \"%s\"\n", ft_memcpy(ft_memcpy_s, "Salut a tous c'est Fanta", 6));
		printf("Ap memcpy    : \"%s\"\nAp ft_memcpy : \"%s\"\n", memcpy_s, ft_memcpy_s);
		printf("-------------\n");
		printf("On tente d'overlap :\n");
		printf("Av memcpy    : \"%s\"\nAv ft_memcpy : \"%s\"\n", memcpy_s2, ft_memcpy_s2);
		printf("Ret memcpy   : \"%s\"\n", memcpy(memcpy_s2 + 2, memcpy_s2, 8));
		printf("Ret ft_memcpy: \"%s\"\n", ft_memcpy(ft_memcpy_s2 + 2, ft_memcpy_s2, 8));
		printf("Ap memcpy    : \"%s\"\nAp ft_memcpy : \"%s\"\n", memcpy_s2, ft_memcpy_s2);
		printf("------------------------------------\n");
		printf("Av memmove    : \"%s\"\nAv ft_memmove : \"%s\"\n", memmove_s, ft_memmove_s);
		printf("Ret memmove   : \"%s\"\n", memmove(memmove_s, "Salut a tous c'est Fanta", 12));
		printf("Ret ft_memmove: \"%s\"\n", ft_memmove(ft_memmove_s, "Salut a tous c'est Fanta", 12));
		printf("Ap memmove    : \"%s\"\nAp ft_memmove : \"%s\"\n", memmove_s, ft_memmove_s);
		printf("-------------\n");
		printf("On tente d'overlap :\n");
		printf("Av memmove    : \"%s\"\nAv ft_memmove : \"%s\"\n", memmove_s2, ft_memmove_s2);
		printf("Ret memmove   : \"%s\"\n", memmove(memmove_s2 + 5, memmove_s2, 5));
		printf("Ret ft_memmove: \"%s\"\n", ft_memmove(ft_memmove_s2 + 5, ft_memmove_s2, 5));
		printf("Ap memmove    : \"%s\"\nAp ft_memmove : \"%s\"\n", memmove_s2, ft_memmove_s2);
		printf("------------------------------------\n");
	}
	else
		printf("File deux arguments chien\n");
	return (0);
}
