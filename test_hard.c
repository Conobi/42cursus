/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_hard.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:06:41 by conobi            #+#    #+#             */
/*   Updated: 2021/11/03 19:50:44 by conobi           ###   ########lyon.fr   */
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
	}
	else
		printf("File deux arguments chien\n");
	return (0);
}
