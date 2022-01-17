/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:42:21 by conobi            #+#    #+#             */
/*   Updated: 2022/01/17 19:37:22 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	perr_print(char *str)
{
	perror(str);
	return (1);
}

char	*find_binary_path(char *binary, char **env)
{
	int		i;
	char	**path;
	char	*bin_path;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (ft_strncmp(env[i], "PATH=", 5) != 0)
		return (0);
	path = ft_split(env[i], ':');
	if (!path)
		return (0);
	i = 0;
	bin_path = 0;
	while (path[++i] && access(bin_path, F_OK) != 0)
	{
		free(bin_path);
		bin_path = ft_pathjoin(path[i], binary);
		if (!bin_path)
			return (0);
	}
	if (access(bin_path, F_OK) != 0)
		return (0);
	return (bin_path);
}
