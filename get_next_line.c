/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:51:22 by conobi            #+#    #+#             */
/*   Updated: 2021/11/29 12:50:13 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	remainds_getter(char **old, char **ret)
{
	int	i;

	if ((*old) && f_strchr((*old), '\n'))
	{
		i = 0;
		while ((*old)[i] != '\n' && (*old)[i])
			i++;
		*ret = f_substr((*old), 0, i + 1);
		*old = *old + i + 1;
	}
	else if ((*old))
		*ret = f_substr((*old), 0, f_strlen((*old)));
}

void	remainds_adder(char **old, char **ret)
{
	int	i;

	if (*ret && f_strchr((*ret), '\n'))
	{
		i = 0;
		while ((*ret)[i] != '\n' && (*ret)[i])
			i++;
		*old = f_substr((*ret), i + 1, f_strlen((*ret)) - i - 1);
		f_memcpy((*ret), (*ret), i);
	}
}

char	*get_next_line(int fd)
{
	static char	*old = 0;
	char		curr[BUFFER_SIZE + 1];
	char		*ret;
	size_t		nread;

	ret = "";
	remainds_getter(&old, &ret);
	if (BUFFER_SIZE && fd > 0 && !f_strchr(ret, '\n'))
	{
		nread = 0;
		nread = read(fd, curr, BUFFER_SIZE);
		curr[BUFFER_SIZE] = 0;
		ret = f_strjoin(ret, curr);
		while (nread == BUFFER_SIZE && !f_strchr(curr, '\n'))
		{
			nread = read(fd, curr, BUFFER_SIZE);
			curr[BUFFER_SIZE] = 0;
			ret = f_strjoin(ret, curr);
		}
		remainds_adder(&old, &ret);
		return (ret);
	}
	else if (BUFFER_SIZE && f_strchr(ret, '\n'))
		return (ret);
	else
		return (NULL);
}

// void	remainds_getter(char **old, char **ret)
// {
// 	char	*included;
// 	int		i;

// 	if (*old)
// 	{
// 		i = -1;
// 		// // printf("'");
// 		while ((*old)[++i] != '\n' && (*old)[i])
// 			;
// 		included = malloc(i + 1 * sizeof(char));
// 		if (!included)
// 			return ;
// 		f_memcpy(included, (*old), i + 1);
// 		// // printf("\n<%s>\n", *ret);
// 		*ret = f_substr(included, 0, i + 1);
// 		// // printf("\n<%s>\n", *ret);
// 		*old = (*old) + i + 1;
// 		// // printf("'\n'%s'", (*old));
// 		// // printf("\n---\n");
// 		free(included);
// 		// // printf("\n<%s>\n", *ret);
// 	}
// }
