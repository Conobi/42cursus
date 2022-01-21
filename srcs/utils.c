/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:42:21 by conobi            #+#    #+#             */
/*   Updated: 2022/01/21 18:52:36 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	perr_print(char *str)
{
	perror(str);
	return (1);
}

int	perr_cb(char *errstr, int ret, int ver)
{
	if (ret == ver)
		perr_print(errstr);
	return (ret);
}

void	slice_binary_args(char *cmd1, char *cmd2, t_data *data)
{
	char	**cmd1_split;
	char	**cmd2_split;

	cmd1_split = ft_split(cmd1, ' ');
	cmd2_split = ft_split(cmd2, ' ');
	if (!cmd1_split || !cmd2_split)
		return ((void)(perr_print("split")));
	data->cmd1_args = cmd1_split;
	data->cmd2_args = cmd2_split;
	data->cmd1_args[0] = find_binary_path(data->cmd1_args[0], data);
	if (!data->cmd1_args[0])
		perr_print(cmd1);
	data->cmd2_args[0] = find_binary_path(data->cmd2_args[0], data);
	if (!data->cmd2_args[0])
		perr_print(cmd2);
}

char	*find_binary_path(char *binary, t_data *data)
{
	int		i;
	char	**path;
	char	*bin_path;

	i = 0;
	while (data->env[i] && ft_strncmp(data->env[i], "PATH=", 5) != 0)
		i++;
	if (ft_strncmp(data->env[i], "PATH=", 5) != 0)
		return (0);
	path = ft_split(data->env[i], ':');
	i = -1;
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
