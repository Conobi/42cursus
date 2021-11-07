/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_hard.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:06:41 by conobi            #+#    #+#             */
/*   Updated: 2021/11/07 12:42:18 by conobi           ###   ########lyon.fr   */
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
	char	*strnstr_s;
	char	*ft_strnstr_s;
	int		strnstr_i;
	char	*ft_substr_s;
	char	*ft_strtrim_s;

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
		printf("Botte de foin : %s, aiguille : \"%s\"\n", argv[1], argv[2]);
		strnstr_i = 5;
		strnstr_s = strnstr(argv[1], argv[2], strnstr_i);
		printf("Pointeur strnstr    (%p) : %s\n", strnstr_s, strnstr_s);
		ft_strnstr_s = ft_strnstr(argv[1], argv[2], strnstr_i);
		printf("Pointeur ft_strnstr (%p) : %s\n", ft_strnstr_s, ft_strnstr_s);
		printf("------------------------------------\n");
		printf("TEST MANQUANT POUR CALLOC !\n");
		printf("------------------------------------\n");
		printf("String: \"J'ai peur d'y etre franchement\", Start: %d, End: %d\n", ft_atoi(argv[1]), ft_atoi(argv[2]));
		ft_substr_s = ft_substr("J'ai peur d'y etre franchement", ft_atoi(argv[1]), ft_atoi(argv[2]));
		printf("Apres ft_substr: %s\n", ft_substr_s);
		free(ft_substr_s);
		printf("------------------------------------\n");
		printf("String: \"%s\", Charset: \"%s\"\n", argv[1], argv[2]);
		ft_strtrim_s = ft_strtrim(argv[1], argv[2]);
		printf("Apres ft_strtrim: \"%s\"\n", ft_strtrim_s);
		free(ft_strtrim_s);
		printf("------------------------------------\n");
	}
	else
		printf("File deux arguments chien\n");
	return (0);
}
