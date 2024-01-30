/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:51:22 by conobi            #+#    #+#             */
/*   Updated: 2022/05/23 14:05:28 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gnl.h"

void	remainds_getter(char **old, char **ret)
{
	int		i;
	char	*tmp;

	if (*old && f_strchr(*old, '\n'))
	{
		i = 0;
		while ((*old)[i] != '\n' && (*old)[i])
			i++;
		tmp = f_substr(*old, 0, i + 1);
		*ret = f_strdup(tmp);
		free(tmp);
		tmp = f_substr(*old, i + 1, f_strlen(*old) - i - 1);
		free(*old);
		*old = f_strdup(tmp);
		free(tmp);
		return ;
	}
	else if (*old && (*old)[0])
		*ret = f_substr(*old, 0, f_strlen(*old));
	free(*old);
	*old = 0;
}

void	remainds_adder(char **old, char **ret)
{
	int		i;
	char	*tmp;

	i = 0;
	while (*ret && (*ret)[i] != '\n' && (*ret)[i])
		i++;
	if (*ret && (*ret)[i] && i == 0 && (*ret)[i] == '\n')
	{
		free(*old);
		*old = f_substr(*ret + i, 1, f_strlen(*ret));
		free(*ret);
		*ret = f_substr("\n", 0, 1);
	}
	else if (*ret && f_strchr(*ret, '\n'))
	{
		tmp = f_substr(*ret, i + 1, f_strlen(*ret) - i - 1);
		free(*old);
		*old = f_strdup(tmp);
		free(tmp);
		tmp = f_substr(*ret, 0, i + 1);
		free(*ret);
		*ret = f_strdup(tmp);
		free(tmp);
	}
}

char	*ft_gnl(int fd)
{
	static char	*old[OPEN_MAX] = {0};
	char		curr[BUFFER_SIZE + 1];
	char		*ret;
	int			nread;

	ret = 0;
	remainds_getter(&old[fd], &ret);
	if (BUFFER_SIZE && fd >= 0 && !f_strchr(ret, '\n'))
	{
		nread = 0;
		*curr = 0;
		nread = read(fd, curr, BUFFER_SIZE);
		curr[nread] = 0;
		f_strjoin(&ret, curr, nread);
		while (nread == BUFFER_SIZE && !f_strchr(curr, '\n'))
		{
			nread = read(fd, curr, BUFFER_SIZE);
			curr[BUFFER_SIZE] = 0;
			f_strjoin(&ret, curr, nread);
		}
		remainds_adder(&old[fd], &ret);
	}
	else if (BUFFER_SIZE && f_strchr(ret, '\n'))
		return (ret);
	return (ret);
}
