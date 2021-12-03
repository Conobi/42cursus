/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:51:22 by conobi            #+#    #+#             */
/*   Updated: 2021/12/03 16:12:03 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	remainds_getter(char **old, char **ret)
{
	int		i;
	char	*tmp;

	if ((*old) && f_strchr((*old), '\n'))
	{
		i = 0;
		while ((*old)[i] != '\n' && (*old)[i])
			i++;
		tmp = f_substr((*old), 0, i + 1);
		*ret = f_substr(tmp, 0, f_strlen(tmp));
		free(tmp);
		tmp = f_substr(*old, i + 1, f_strlen((*old)) - i - 1);
		// printf("B%pB\n", *old);
		free((*old));
		*old = f_substr(tmp, 0, f_strlen(tmp));
		// printf("A%pA\n", *old);
		free(tmp);
		return ;
	}
	else if ((*old) && (*old)[0])
		*ret = f_substr((*old), 0, f_strlen((*old)));
	// printf("B%pB\n", *old);
	free((*old));
	*old = 0;
}

void	remainds_adder(char **old, char **ret)
{
	int		i;
	char	*tmp;

	if ((*ret) && f_strchr((*ret), '\n'))
	{
		i = 0;
		/* Ici, on coupe la partie après le \n */
		while ((*ret)[i] != '\n' && (*ret)[i])
			i++;
		// if (i != 0)
		// 	tmp = f_substr((*ret), i + 1, f_strlen((*ret)) - i - 1);
		// else
		tmp = f_substr((*ret), i, f_strlen((*ret)) - i);
		// printf("B%pB\n", (*old));
		free((*old));
		*old = f_substr(tmp, 0, f_strlen(tmp));
		// printf("A%pA\n", *old);
		free(tmp);
		/* Ici en bas c'est pour couper ret */
		tmp = f_substr((*ret), 0, i);
		free((*ret));
		*ret = f_substr(tmp, 0, f_strlen(tmp));
		free(tmp);
	}
}

char	*get_next_line(int fd)
{
	static char	*old = 0;
	char		curr[BUFFER_SIZE + 1];
	char		*ret;
	int			nread;

	ret = 0;
	// printf("A%sA", old);
	remainds_getter(&old, &ret);
	// printf("<%s>", old);
	if (BUFFER_SIZE && fd >= 0 && !f_strchr(ret, '\n'))
	{
		nread = 0;
		*curr = 0;
		nread = read(fd, curr, BUFFER_SIZE);
		curr[nread] = 0;
		f_strjoin(&ret, ret, curr, nread);
		while (nread == BUFFER_SIZE && !f_strchr(curr, '\n'))
		{
			nread = read(fd, curr, BUFFER_SIZE);
			curr[BUFFER_SIZE] = 0;
			f_strjoin(&ret, ret, curr, nread);
		}
		remainds_adder(&old, &ret);
	}
	else if (BUFFER_SIZE && f_strchr(ret, '\n'))
		return (ret);
	return (ret);
}
