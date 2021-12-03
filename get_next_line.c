/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:51:22 by conobi            #+#    #+#             */
/*   Updated: 2021/12/03 19:35:19 by conobi           ###   ########lyon.fr   */
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
		free((*old));
		*old = f_substr(tmp, 0, f_strlen(tmp));
		free(tmp);
		return ;
	}
	else if ((*old) && (*old)[0])
		*ret = f_substr((*old), 0, f_strlen((*old)));
	free((*old));
	*old = 0;
}

/***
 * remainds_adder :
 * Si (*ret)[0] == '\n', old vaut rien et on renvoie '\n'
 * Sinon, on renvoie jusqu'au '\n', et on balance le reste dans le old
*/
void	remainds_adder(char **old, char **ret)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*ret) && (*ret)[i] != '\n' && (*ret)[i])
		i++;
	if ((*ret) && (*ret)[i] && i == 0 && (*ret)[i] == '\n')
	{
		free((*old));
		*old = f_substr((*ret) + i, 1, f_strlen((*ret)));
		free((*ret));
		*ret = f_substr("\n", 0, 1);
	}
	else if ((*ret) && f_strchr((*ret), '\n'))
	{
		tmp = f_substr((*ret), i + 1, f_strlen((*ret)) - i - 1);
		free((*old));
		*old = f_substr(tmp, 0, f_strlen(tmp));
		free(tmp);
		tmp = f_substr((*ret), 0, i + 1);
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
	remainds_getter(&old, &ret);
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
