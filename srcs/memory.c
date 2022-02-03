/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:46:43 by conobi            #+#    #+#             */
/*   Updated: 2022/02/03 17:10:28 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

short	fbp_free(char **path, char *binary, char *bin_path)
{
	int	i;

	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
	free(binary);
	if (access(bin_path, F_OK) != 0)
		free(bin_path);
	else
		return (1);
	return (0);
}

void	pipex_free(t_data *data)
{
	int	i;

	i = -1;
	while (data->cmd1_args[++i])
		free(data->cmd1_args[i]);
	i = -1;
	while (data->cmd2_args[++i])
		free(data->cmd2_args[i]);
	free(data->cmd1_args);
	free(data->cmd2_args);
}
