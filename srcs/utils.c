/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:42:21 by conobi            #+#    #+#             */
/*   Updated: 2022/02/02 19:59:19 by conobi           ###   ########lyon.fr   */
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

void	perr_cmdnotfound(char *file, int cmd)
{
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": command not found\n", 2);
	if (cmd)
		exit(127);
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
		perr_cmdnotfound(cmd1, 0);
	data->cmd2_args[0] = find_binary_path(data->cmd2_args[0], data);
	if (!data->cmd2_args[0])
		perr_cmdnotfound(cmd2, 1);
}

char	*find_binary_path(char *binary, t_data *data)
{
	int		i;
	char	**path;
	char	*bin_path;

	if (!access(binary, F_OK))
		return (binary);
	i = 0;
	while (data->env[i] && ft_strncmp(data->env[i], "PATH=", 5) != 0)
		i++;
	path = ft_split(data->env[i] + 5, ':');
	if (ft_strncmp(data->env[i], "PATH=", 5) != 0 || !path)
		return (0);
	i = -1;
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
