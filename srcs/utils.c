/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:42:21 by conobi            #+#    #+#             */
/*   Updated: 2022/02/03 17:07:38 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	perr_cb(char *errstr, int ret, int ver)
{
	if (ret == ver)
		perror(errstr);
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
	data->cmd1_args = ft_split(cmd1, ' ');
	data->cmd2_args = ft_split(cmd2, ' ');
	if (!data->cmd1_args || !data->cmd2_args)
		return ((void)(perror("split")));
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
	bin_path = ft_calloc(1, 1);
	while (path[++i] && access(bin_path, F_OK) != 0)
	{
		free(bin_path);
		bin_path = ft_pathjoin(path[i], binary);
		if (!bin_path)
			return (0);
	}
	if (fbp_free(path, binary, bin_path))
		return (bin_path);
	return (0);
}
