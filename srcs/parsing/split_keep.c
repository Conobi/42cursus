/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_keep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:29:33 by conobi            #+#    #+#             */
/*   Updated: 2022/10/05 19:14:43 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// static	int	len_until(char *str, char c)
// {
// 	int	i;

// 	i = -1;
// 	while (str[++i])
// 		if (str[i] == c)
// 			break ;
// 	return (i);
// }

// static char	**free_loop(char **splited, int j)
// {
// 	while (--j || j == 0)
// 		free(splited[j]);
// 	free(splited);
// 	return (NULL);
// }

// char	**split_keep(char *str, char c)
// {
// 	char	**ret;
// 	int		len;
// 	int		i;
// 	int		j;

// 	i = -1;
// 	len = 1;
// 	while (str[++i])
// 		if (str[i] == c)
// 			len++;
// 	printf("Ici len: %d\n", len);
// 	ret = ft_calloc(len + 1, sizeof(char *));
// 	if (!ret)
// 		return (NULL);
// 	i = -1;
// 	j = -1;
// 	while (str[++i])
// 	{
// 		len = len_until(str + i, c);
// 		ret[++j] = ft_calloc(len + 1, sizeof(char));
// 		if (!ret[j])
// 			return (free_loop(ret, j));
// 		str[i + len] = '\0';
// 		ft_strlcpy(ret[j], str + i, len);
// 		str[i + len] = c;
// 		i += len;
// 	}
// 	return (ret);
// }

// int	main(int argc, char **argv)
// {
// 	int		i;
// 	char	**test;

// 	if (argc == 3)
// 	{
// 		test = split_keep(argv[1], argv[2][0]);
// 		i = -1;
// 		while (test[++i][0])
// 		{
// 			if (test[i])
// 				printf("%s\n", test[i]);
// 			else
// 				printf("---\n");
// 		}
// 	}
// 	return (0);
// }
